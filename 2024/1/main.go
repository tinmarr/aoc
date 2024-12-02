package main

import (
	"fmt"
	"math"
	"os"
	"slices"
	"strconv"
	"strings"
)

func part1(leftList, rightList []int) int {
	slices.Sort(leftList)
	slices.Sort(rightList)

	sum := 0
	for i := 0; i < len(leftList); i++ {
		sum += int(math.Abs(float64(leftList[i] - rightList[i])))
	}

	return sum
}

func part2(leftList, rightList []int) int {
	sum := 0

	for _, left := range leftList {
		count := 0
		for _, right := range rightList {
			if left == right {
				count++
			}
		}
		sum += left * count
	}

	return sum
}

func main() {
	fmt.Println("reading file", os.Args[1])
	dat, err := os.ReadFile(os.Args[1])
	if err != nil {
		fmt.Println("read file error")
		return
	}
	file := strings.Split(string(dat), "\n")
	file = file[:len(file)-1]

	leftList := make([]int, len(file))
	rightList := make([]int, len(file))

	for i, line := range file {
		nums := strings.Split(line, "   ")
		left, err := strconv.ParseInt(nums[0], 10, 0)
		if err != nil {
			fmt.Println("err parsing int")
		}
		right, err := strconv.ParseInt(nums[1], 10, 0)
		if err != nil {
			fmt.Println("err parsing int")
		}
		leftList[i] = int(left)
		rightList[i] = int(right)
	}

	// sum := part1(leftList, rightList)
	sum := part2(leftList, rightList)

	fmt.Println(sum)
}
