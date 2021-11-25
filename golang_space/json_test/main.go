package main

import (
	"encoding/json"
	"fmt"
)

type User struct {
	MarketInfosMap map[string][]string
	ModelNames     []string
	IsInitialized  bool
}

type OneBackTestRes struct {
	IsFind       bool    `json:"IsFind"`
	Status       string  `json:"Status"`
	AllEarnings  float64 `json:"AllEarnings"`
	EarningRatio float64 `json:"EarningRatio"`
	HandoffRatio float64 `json:"HandoffRatio"`
}

type AllBackTestRes struct {
	Results []OneBackTestRes `json:"Results"`
}

type SearchRequests struct {
	Requests []SearchRequest `json:"Requests"`
}

type SearchRequest struct {
	Date         string `json:"Date"`
	Model        string `json:"Model"`
	TraderName   string `json:"TraderName"`
	PositionName string `json:"PositionName"`
}

func main() {
	var sqs SearchRequests = SearchRequests{}
	sqs.Requests = append(sqs.Requests,
		SearchRequest{
			Date:         "2020-01-01",
			Model:        "test",
			TraderName:   "hjiang",
			PositionName: "zhang",
		})

	b, err := json.Marshal(sqs)
	if err != nil {
		fmt.Println(err)
		return
	}

	fmt.Println(string(b))

	/*
		marks := make(map[string][]string)
		marks["market1"] = []string{"2020-01-01", "2021-02-21"}
		marks["market2"] = []string{"2020-01-01", "2021-02-21"}

		models := []string{"model1", "model2"}

		user := &User{
			MarketInfosMap: marks,
			ModelNames:     models,
			IsInitialized:  true,
		}

		b, err := json.Marshal(user)
		if err != nil {
			fmt.Println(err)
			return
		}

		fmt.Println(string(b))

		allRes := &AllBackTestRes{
			Results: []OneBackTestRes{
				OneBackTestRes{
					IsFind: false,
				},
				OneBackTestRes{
					IsFind: true,
					Status: "Running",
				},
				OneBackTestRes{
					IsFind:       true,
					Status:       "Finished",
					AllEarnings:  1000.23,
					EarningRatio: 0.22,
					HandoffRatio: 1.22,
				},
			},
		}

		c, err := json.Marshal(allRes)
		if err != nil {
			fmt.Println(err)
			return
		}

		fmt.Println(string(c))
	*/
}
