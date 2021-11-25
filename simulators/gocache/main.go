package main

import (
	"encoding/gob"
	"fmt"

	"github.com/patrickmn/go-cache"
)

type BacktestStatus int

const (
	Created BacktestStatus = iota
	Running
	Finish
)

type Result struct {
	Age int
}

type Package struct {
	Status BacktestStatus
	Res    Result
}

func main() {
	mycache := cache.New(cache.NoExpiration, cache.NoExpiration)
	/*
		mycache.LoadFile("./backtest_res.txt")
		fmt.Println(mycache.Items())
	*/

	/*
		mycache.Set("foo", "bar", cache.NoExpiration)
		mycache.SaveFile("./test.txt")
	*/

	/*
		key := "field1" //+ "$" + "field2" + "$" + "field3" + "$" + "field4"
		value := "bar"
		mycache.Set(key, value, cache.NoExpiration)
		mycache.SaveFile("./test.txt")
	*/

	/*
		mycache.Set("foo", Result{Age: 10}, cache.NoExpiration)
		if err := mycache.SaveFile("./test.txt"); err != nil {
			fmt.Println("Save cache to file error!")
		}
	*/
	gob.Register(Result{})

	if err := mycache.LoadFile("./test.txt"); err != nil {
		fmt.Println("loadfile error")
		fmt.Println(err)
	} else {
		fmt.Println(mycache.Items())
	}
}
