package main

import (
	"fmt"
	"time"
)

func main() {
	var or func(chans ...<-chan interface{}) <-chan interface{}
	or = func(chans ...<-chan interface{}) <-chan interface{} {
		switch len(chans) {
		case 0:
			return nil
		case 1:
			return chans[0]
		}

		orDone := make(chan interface{})
		go func() {
			defer close(orDone)

			switch len(chans) {
			case 2:
				select {
				case <-chans[0]:
				case <-chans[1]:
				}
			default:
				select {
				case <-chans[0]:
				case <-chans[1]:
				case <-chans[2]:
				case <-or(append(chans[3:], orDone)...):
				}
			}
		}()
		return orDone
	}

	sig := func(after time.Duration) <-chan interface{} {
		c := make(chan interface{})
		go func() {
			defer close(c)
			time.Sleep(after)
		}()
		return c
	}

	start := time.Now()
	<-or(
		sig(time.Hour*2),
		sig(time.Minute*5),
		sig(time.Second*1),
	)
	fmt.Printf("down after %v\n", time.Since(start))
}
