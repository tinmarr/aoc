package main

import (
	"fmt"
	"os"
	"strings"
)

func part1(file string) {
}

func part2(file string) {
}

func main() {
	dat, err := os.ReadFile(os.Args[1])
	if err != nil {
		fmt.Println("read file error")
		return
	}
	file := strings.TrimRight(string(dat), "\n")

	part1(file)
	// part2(file)
}
