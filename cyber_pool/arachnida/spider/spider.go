/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.go                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykeciri <ykeciri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:09:09 by haapycoding       #+#    #+#             */
/*   Updated: 2026/09/07 12:47:32 by ykeciri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

package main

import (
	"fmt"
	"log"
	"path/filepath"
	"strings"
	"sync"

	"flag"
	// "log"
	"os"

	"net/url"

	"github.com/gocolly/colly"
	"github.com/k0kubun/go-ansi"
	"github.com/schollz/progressbar/v3"
)

type Industry struct {
	Url, Image string
}

func setFlags() (string, int, []string, error) {
	recursiveFlag := flag.Bool("r", false, "Recursively downloads the images in a URL received as a parameter")
	lenghtFlag := flag.Int("l", 5, "Indicates the maximum depth level of the recursive download. (Needs the -r flags)")
	pathFlag := flag.String("p", "./data/", " Indicates the path where the downloaded files will be saved.")

	lenghtSet := false
	recursiveSet := false
	flag.Parse()

	fmt.Printf("path flag is %s \n", *pathFlag)
	fmt.Printf("lenght flag is %d \n", *lenghtFlag)
	fmt.Printf("recursice flag is %t \n", *recursiveFlag)

	flag.Visit(func(f *flag.Flag) {
		switch f.Name {
		case "l":
			lenghtSet = true
		case "r":
			recursiveSet = true
		}
	})

	if lenghtSet && !recursiveSet {
		fmt.Println("You need to use the [-l] flag with [-r].")
	}

	args := flag.Args()

	if len(args) != 1 || args[0] == "" {
		// fmt.Printf("YOU NEED TO GIVE A URL !\n\nUsage of spider : \n\t /spider [-rlp] URL\n You can use the -h flag to see the help page.\n")
		return "", 0, nil, fmt.Errorf("YOU NEED TO GIVE A URL !\n\nUsage of spider : \n\t /spider [-rlp] URL\n You can use the -h flag to see the help page.\n")
	}

	maxDepth := 1
	if *recursiveFlag {
		if lenghtSet {
			maxDepth = *lenghtFlag
		} else {
			maxDepth = 5
		}
	}
	working_dir := *pathFlag

	return working_dir, maxDepth, args, nil
}

func siteScanning(currentSites []string, images *map[string]bool) ([]string, error) {
	var sites []string
	var mutex sync.Mutex
	c := colly.NewCollector(
		colly.Async(true),
	)
	c.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36"

	c.OnHTML("a[href]", func(e *colly.HTMLElement) {
		link := e.Attr("href")
		// fmt.Printf("Link found: %q -> %s\n", e.Text, link)
		mutex.Lock()
		sites = append(sites, e.Request.AbsoluteURL(link))
		mutex.Unlock()
	})

	c.OnHTML("img[src]", func(e *colly.HTMLElement) {
		src := e.Request.AbsoluteURL(e.Attr("src"))
		if src != "" {
			mutex.Lock()
			(*images)[src] = true
			mutex.Unlock()
		}
	})

	for _, site := range currentSites {
		c.Visit(site)
	}
	c.Wait()
	return sites, nil
}

func isImageContentType(ct string) bool {
	ct = strings.ToLower(ct)
	switch {
	case strings.Contains(ct, "image/jpeg"):
		return true
	case strings.Contains(ct, "image/gif"):
		return true
	case strings.Contains(ct, "image/png"):
		return true
	case strings.Contains(ct, "image/bmp"):
		return true
	}
	return false
}

func downloadSite(working_dir string, images map[string]bool) {
	os.Mkdir(working_dir, 0755)
	urls := make([]string, 0, len(images))
	for u := range images {
		urls = append(urls, u)
	}
	bar := progressbar.NewOptions(len(urls),
		progressbar.OptionSetWriter(ansi.NewAnsiStdout()),
		progressbar.OptionEnableColorCodes(true),
		progressbar.OptionShowBytes(true),
		progressbar.OptionSetWidth(15),
		progressbar.OptionSetDescription("[cyan] Downloading images"),
		progressbar.OptionSetTheme(progressbar.Theme{
			Saucer:        "[green]=[reset]",
			SaucerHead:    "[green]>[reset]",
			SaucerPadding: " ",
			BarStart:      "[",
			BarEnd:        "]",
		}))
	var mu sync.Mutex

	dc := colly.NewCollector(
		colly.Async(true),
	)
	dc.Limit(&colly.LimitRule{Parallelism: 8})
	dc.OnResponse(func(r *colly.Response) {
		ct := r.Headers.Get("Content-Type")
		if !isImageContentType(ct) {
			mu.Lock()
			bar.Add(1)
			mu.Unlock()
			return
		}

		idx := r.Ctx.Get("index")
		u, _ := url.Parse(r.Request.URL.String())
		ext := filepath.Ext(u.Path)
		if ext == "" {
			ext = ".jpg"
		}
		filename := fmt.Sprintf("%s_%s", idx, filepath.Base(strings.TrimSuffix(u.Path, ext)))
		filename = fmt.Sprintf("%s%s", filename, ext)
		filename = fmt.Sprintf("%s%s", idx, ext)

		err := r.Save(filepath.Join(working_dir, filename))
		mu.Lock()
		bar.Add(1)
		mu.Unlock()
		if err != nil {
			fmt.Println("Erreur sauvegarde:", err)
			return
		}

	})

	dc.OnError(func(r *colly.Response, err error) {
		mu.Lock()
		bar.Add(1)
		mu.Unlock()
	})

	for i, imgURL := range urls {
		ctx := colly.NewContext()
		ctx.Put("index", fmt.Sprintf("%d", i+1))
		if err := dc.Request("GET", imgURL, nil, ctx, nil); err != nil {
			log.Println("erreur request:", imgURL, err)
			mu.Lock()
			bar.Add(1)
			mu.Unlock()
		}
	}
	dc.Wait()
	fmt.Println("\nDownload finished.")
}

func main() {

	working_dir, maxDepth, args, err := setFlags()
	if err != nil {
		return
	}

	var sites []string
	images := make(map[string]bool)

	sites = append(sites, args[0])
	for i := 0; i < maxDepth; i++ {
		sites, _ = siteScanning(sites, &images)
	}

	downloadSite(working_dir, images)
}
