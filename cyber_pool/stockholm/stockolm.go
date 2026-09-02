package main

import (
	"flag"
	"fmt"
)

func main() {
	fmt.Println("Hello, World!")
}

func setFlags() (string, int, []string, error) {
	helpFlag := flag.Bool("help", false, "")
	helpFlagSmall := flag.Bool("h", false, "")
	versionFlag := flag.Bool("version", false, "")
	versionFlagSmall := flag.Bool("v", false, "")
	reverseFlag := flag.Bool("reverse", false, "")
	reverseFlagSmall := flag.Bool("r", false, "")
	silentFlag := flag.Bool("silent", false, "")
	silentFlagSmall := flag.Bool("s", false, "")

	flag.Parse()

	return working_dir, maxDepth, args, nil
}
