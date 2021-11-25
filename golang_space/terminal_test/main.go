package main

import "time"

func main() {
	for i := 0; i < 100; i++ {
		time.Sleep(5 * time.Second)
	}
}
