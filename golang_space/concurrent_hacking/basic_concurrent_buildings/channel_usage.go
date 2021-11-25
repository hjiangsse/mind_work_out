package main

import (
	"bytes"
	"fmt"
	"os"
	"sync"
)

func test_buffed() {
	var stdoutBuffer bytes.Buffer
	defer stdoutBuffer.WriteTo(os.Stdout)

	intStream := make(chan int, 4)
	go func() {
		defer close(intStream)
		defer fmt.Fprintln(&stdoutBuffer, "Producer Done.")
		for i := 0; i < 5; i++ {
			fmt.Fprintf(&stdoutBuffer, "Sending: %d\n", i)
			intStream <- i
		}
	}()

	for i := range intStream {
		fmt.Fprintf(&stdoutBuffer, "Received %v.\n", i)
	}
}

func test_channel_ownership() {
	intchannel := make(chan int)
	var wg sync.WaitGroup
	wg.Add(2)
	go func(ch chan<- int) {
		defer wg.Done()
		fmt.Println("I will wirte a number to the channel.")
		ch <- 10
	}(intchannel)

	go func(ch <-chan int) {
		defer wg.Done()
		fmt.Println("I can only read a number from the channel.")
		fmt.Println(<-ch)
	}(intchannel)

	wg.Wait()
}

func test_chan_owner() {
	chanOwner := func() <-chan int {
		resultStream := make(chan int, 6)
		go func() {
			defer close(resultStream)
			for i := 0; i <= 5; i++ {
				resultStream <- i
			}
		}()

		return resultStream
	}

	resultStream := chanOwner()
	for result := range resultStream {
		fmt.Printf("Received: %d\n", result)
	}
	fmt.Println("Done!")
}

func main() {
	//test_buffed()
	//test_channel_ownership()
	test_chan_owner()
}
