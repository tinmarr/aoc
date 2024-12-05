package main

import (
	"fmt"
	"os"
	"strings"
)

// Loads the file determined by the first argument
func LoadFile() string {
	dat, err := os.ReadFile(os.Args[1])
	if err != nil {
		fmt.Println("read file error")
		os.Exit(1)
	}
	return strings.TrimRight(string(dat), "\n")

}
