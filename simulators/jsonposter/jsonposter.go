package main

import (
	"bytes"
	"encoding/json"
	"flag"
	"fmt"
	"io/ioutil"
	"net/http"
)

const (
	BackTestRequestRoute    = "/backtest/tasksend"
	TaskStatusSearchRoute   = "/backtest/statussearch"
	RunningTasksSearchRoute = "/backtest/running"
	ConfigFetchRoute        = "/configserver/configs"
)

type OneBackTestRes struct {
	IsFind         bool    `json:"IsFind"`
	Status         string  `json:"Status"`
	Date           string  `json:"Date"`
	Model          string  `json:"Model"`
	TraderName     string  `json:"TraderName"`
	PositionName   string  `json:"PositionName"`
	CurStep        int32   `json:"CurStep"`
	TotalStep      int32   `json:"TotalStep"`
	LastFinishTime string  `json:"LastFinishTime"`
	AllEarnings    float64 `json:"AllEarnings"`
	EarningRatio   float64 `json:"EarningRatio"`
	HandoffRatio   float64 `json:"HandoffRatio"`
}

type AllBackTestRes struct {
	Results []OneBackTestRes `json:"Results"`
}

type TaskScheduleResult struct {
	Success bool   `json:"Success"`
	Message string `json:"Message"`
}

type ToFrontEndMsg struct {
	MarketInfos   []string `json:"MarketInfos"`
	ModelNames    []string `json:"ModelNames"`
	IsInitialized bool     `json:"IsInitialized"`
}

const (
	TaskScheduleMechineAddr = "localhost"
	ConfigServerAddr        = "192.168.2.129"
	BacktestRequestJsonPath = "./files/backtest_tasks_request.json"
	StatusSearchJsonPath    = "./files/status_search.json"
)

//a front end simulator function
func DoBaskTestTasksSending() {
	jsondat, err := ioutil.ReadFile(BacktestRequestJsonPath)
	if err != nil {
		panic(err)
	}

	url := "http://" + TaskScheduleMechineAddr + ":8080" + BackTestRequestRoute
	req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsondat))
	req.Header.Set("X-Custom-Header", "myvalue")
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	var taskresult TaskScheduleResult = TaskScheduleResult{}
	buf := new(bytes.Buffer)
	buf.ReadFrom(resp.Body)

	err = json.Unmarshal(buf.Bytes(), &taskresult)
	if err != nil {
		panic(err)
	}

	fmt.Println(taskresult)
}

//search status for some specific tasks
func DoTaskStatusSearch() {
	jsondat, err := ioutil.ReadFile(StatusSearchJsonPath)
	if err != nil {
		panic(err)
	}

	url := "http://" + TaskScheduleMechineAddr + ":8080" + TaskStatusSearchRoute
	req, err := http.NewRequest("POST", url, bytes.NewBuffer(jsondat))
	req.Header.Set("X-Custom-Header", "myvalue")
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	var backtestres AllBackTestRes = AllBackTestRes{}
	buf := new(bytes.Buffer)
	buf.ReadFrom(resp.Body)

	err = json.Unmarshal(buf.Bytes(), &backtestres)
	if err != nil {
		panic(err)
	}

	fmt.Println(backtestres)
}

//search all running task's status
func DoAllRunningTasksSearch() {
	url := "http://" + TaskScheduleMechineAddr + ":8080" + RunningTasksSearchRoute
	req, err := http.NewRequest("POST", url, bytes.NewBuffer([]byte{}))
	req.Header.Set("X-Custom-Header", "myvalue")
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	var backtestres AllBackTestRes = AllBackTestRes{}
	buf := new(bytes.Buffer)
	buf.ReadFrom(resp.Body)

	err = json.Unmarshal(buf.Bytes(), &backtestres)
	if err != nil {
		panic(err)
	}

	fmt.Println(backtestres)
}

func DoConfigsFetch() {
	url := "http://" + ConfigServerAddr + ":8081" + ConfigFetchRoute
	req, err := http.NewRequest("GET", url, bytes.NewBuffer([]byte{}))
	if err != nil {
		panic(err)
	}
	req.Header.Set("X-Custom-Header", "myvalue")
	req.Header.Set("Content-Type", "application/json")

	client := &http.Client{}
	resp, err := client.Do(req)
	if err != nil {
		panic(err)
	}
	defer resp.Body.Close()

	var configs ToFrontEndMsg = ToFrontEndMsg{}
	buf := new(bytes.Buffer)
	buf.ReadFrom(resp.Body)

	err = json.Unmarshal(buf.Bytes(), &configs)
	if err != nil {
		panic(err)
	}

	fmt.Println(configs)
}

func main() {
	var isTaskSend, isStatusSearch, isRunningSearch, isConfigFetch bool
	flag.BoolVar(&isTaskSend, "tasksend", false, "send basktest task(s) to backend")
	flag.BoolVar(&isStatusSearch, "statussearch", false, "search backend task status")
	flag.BoolVar(&isRunningSearch, "runningsearch", false, "search backend running task status")
	flag.BoolVar(&isConfigFetch, "configfetch", false, "fetch config")
	flag.Parse()

	if isTaskSend {
		DoBaskTestTasksSending()
	}

	if isStatusSearch {
		DoTaskStatusSearch()
	}

	if isRunningSearch {
		DoAllRunningTasksSearch()
	}

	if isConfigFetch {
		DoConfigsFetch()
	}
}
