/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spider.go                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:09:09 by haapycoding       #+#    #+#             */
/*   Updated: 2025/11/20 10:12:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

package main

import (
	"fmt"

	"flag"
	"log"
	"os"

	"net/url"

	"github.com/gocolly/colly"
)

type Industry struct {
	Url,
	Image,
	Name string
}

func main() {

	/* ************************************************************************** */
	/*                                FLAG PARSING                                */
	/* ************************************************************************** */

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
		fmt.Printf("YOU NEED TO GIVE A URL !\n\nUsage of spider : \n\t /spider [-rlp] URL\n You can use the -h flag to see the help page.\n")
		return
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

	/* ************************************************************************** */
	/*                              DECLARING FUNCTIONS                           */
	/* ************************************************************************** */

	indexOf := func(s, sub string) int {
		if len(sub) == 0 || len(s) < len(sub) {
			return -1
		}
		for i := 0; i <= len(s)-len(sub); i++ {
			match := true
			for j := 0; j < len(sub); j++ {
				if s[i+j] != sub[j] {
					match = false
					break
				}
			}
			if match {
				return i
			}
		}
		return -1
	}

	hasSuffix := func(s, suf string) bool {
		if len(s) < len(suf) {
			return false
		}
		offset := len(s) - len(suf)
		for i := 0; i < len(suf); i++ {
			if s[offset+i] != suf[i] {
				return false
			}
		}
		return true
	}

	baseName := func(p string) string {
		i := len(p) - 1
		for i >= 0 && p[i] == '/' {
			i--
		}
		if i < 0 {
			return "index"
		}
		j := i
		for j >= 0 && p[j] != '/' {
			j--
		}
		name := p[j+1 : i+1]
		if name == "" {
			return "index"
		}
		return name
	}

	/* ************************************************************************** */
	/*                               SCRAPING LOGIC                               */
	/* ************************************************************************** */

	c := colly.NewCollector()
	c.UserAgent = "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/111.0.0.0 Safari/537.36"
	fmt.Printf("maxdepth is [%d]", maxDepth)
	c.Limit(&colly.LimitRule{
		DomainGlob:  "*",
		Parallelism: 10,
	})

	if err := os.MkdirAll(working_dir, 0755); err != nil {
		log.Fatal(err)
	}

	c.OnRequest(func(r *colly.Request) {
		depth := r.Ctx.GetAny("depth")
		if depth == nil {
			depth = 0
		}
		fmt.Printf("Visiting (depth %v): %s\n", depth, r.URL.String())
	})

	// log errors
	c.OnError(func(r *colly.Response, err error) {
		if r != nil && r.Request != nil {
			log.Printf("Request URL: %s failed with status: %d, error: %v\n", r.Request.URL, r.StatusCode, err)
		} else {
			log.Printf("Request failed: %v\n", err)
		}
	})

	// follow links recursively (only links that contain the site domain)
	my_url, err := url.Parse(args[0])
	if err != nil {

	}

	hostname := my_url.Hostname()
	c.OnHTML("a[href]", func(e *colly.HTMLElement) {
		href := e.Attr("href")
		if href == "" {
			return
		}
		link := e.Request.AbsoluteURL(href)
		if link == "" {
			return
		}
		if indexOf(link, hostname) == -1 {
			return
		}
		// check depth limit
		depth := e.Request.Ctx.GetAny("depth")
		currentDepth := 0
		if depth != nil {
			if d, ok := depth.(int); ok {
				currentDepth = d
			}
		}
		if currentDepth > maxDepth {
			return
		}

		// visit with incremented depth
		ctx := colly.NewContext()
		ctx.Put("depth", currentDepth+1)
		_ = c.Request("GET", link, nil, ctx, nil)
	})

	c.OnHTML("img[src]", func(e *colly.HTMLElement) {
		src := e.Attr("src")
		if src == "" {
			return
		}
		imgURL := e.Request.AbsoluteURL(src)
		if imgURL == "" {
			return
		}
		// use e.Request.Visit to keep same context; ignore revisit errors
		_ = e.Request.Visit(imgURL)
	})

	// save image responses
	c.OnResponse(func(r *colly.Response) {
		ct := r.Headers.Get("Content-Type")
		if len(ct) >= 6 && ct[:6] == "image/" {
			// Skip SVG files explicitly
			if ct == "image/svg+xml" {
				// fmt.Printf("Skipping SVG file: %s\n", r.Request.URL.String())
				return
			}

			name := baseName(r.Request.URL.Path)
			allowedExts := []string{".jpg", ".jpeg", ".png", ".gif", ".bmp"}
			isAllowed := false

			for _, e := range allowedExts {
				if hasSuffix(name, e) {
					isAllowed = true
					break
				}
				// also check uppercase variants
				up := ""
				for i := 0; i < len(e); i++ {
					ch := e[i]
					if ch >= 'a' && ch <= 'z' {
						up += string(ch - 32)
					} else {
						up += string(ch)
					}
				}
				if hasSuffix(name, up) {
					isAllowed = true
					break
				}
			}

			if !isAllowed {
				switch ct {
				case "image/jpeg":
					name += ".jpg"
					isAllowed = true
				case "image/png":
					name += ".png"
					isAllowed = true
				case "image/gif":
					name += ".gif"
					isAllowed = true
				case "image/bmp":
					name += ".bmp"
					isAllowed = true
				default:
					fmt.Printf("Skipping unsupported image type %s: %s\n", ct, r.Request.URL.String())
					return
				}
			}

			/* ************************************************************************** */
			/*                                SAVING FILES                                */
			/* ************************************************************************** */

			if working_dir[len(working_dir)-1] != '/' {
				working_dir += "/"
			}

			fp := working_dir + name
			f, err := os.Create(fp)
			if err != nil {
				log.Println("failed creating file:", err)
				return
			}
			_, err = f.Write(r.Body)
			if err != nil {
				log.Println("failed saving file:", err)
			} else {
				fmt.Println("Saved:", fp)
			}
			f.Close()
		}
	})

	// start crawl again with handlers attached
	_ = c.Visit(args[0])
}
