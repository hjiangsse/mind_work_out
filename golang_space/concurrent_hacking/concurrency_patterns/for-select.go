package main

import (
	"fmt"
	"time"
)

func main() {
	done := make(chan interface{})

	go func() {
		for {
			select {
			case <-done:
				return
			default:
				fmt.Println("for-select running!")
				time.Sleep(1 * time.Second)
			}
		}
	}()

	time.Sleep(time.Second * 5)
	close(done)
	time.Sleep(time.Second * 1)
}
