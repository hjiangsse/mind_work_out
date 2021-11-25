package main

import (
	"fmt"
	"strconv"
)

func main() {
	fmt.Println("This is the start of a new world")
	i, err := strconv.Atoi("123")
	if err != nil {
		fmt.Println("strconv error!")
	}
	fmt.Println(i)
}
