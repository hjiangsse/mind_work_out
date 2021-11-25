package main

import (
	"bytes"
	"flag"
	"fmt"
	"log"
	"os/exec"
	"strings"

	"github.com/manifoldco/promptui"
)

var hostinfos = map[string][]string{
	"129": []string{"jingle", "192.168.2.129", "Life123", "~"},
	"200": []string{"jingle", "192.168.2.200", "Life123", "~"},
	"221": []string{"jingle", "192.168.222.221", "Life123", "~"},
	"220": []string{"jingle", "192.168.222.220", "Life123", "~"},
}

/*
 * return user input
 */
func GetUserInput() (string, string, string) {
	directionPtr := flag.String("d", "download", "files transfer direction, download or upload")
	hostPtr := flag.String("h", "220", "the host name of remote mechine!")
	fileListPtr := flag.String("f", "test.txt", "the file lists")

	flag.Parse()

	return *directionPtr, *hostPtr, *fileListPtr
}

/*
 * split filelist string by commas
 */
func GetFileSlice(filelist string) []string {
	return strings.Split(filelist, ",")
}

func yesNo(pro string) bool {
	prompt := promptui.Select{
		Label: pro,
		Items: []string{"Yes", "No"},
	}
	_, result, err := prompt.Run()
	if err != nil {
		log.Fatalf("Prompt failed %v\n", err)
	}
	return result == "Yes"
}

func main() {
	direction, host, filelist := GetUserInput()
	files := GetFileSlice(filelist)

	if val, ok := hostinfos[host]; ok {
		sshInfo, err := GenSshSession(val[0], val[1], val[2])
		if err != nil {
			panic(err)
		}

		if direction == "download" {
			session := sshInfo.Session()
			var buf bytes.Buffer
			session.Stdout = &buf

			findCmd := ""
			for _, file := range files {
				findCmd += "find " + val[3] + " -type f -name " + file + ";"
			}

			session.Run(findCmd)

			paths := strings.Fields(buf.String())
			for _, path := range paths {
				prom := "Copy " + path + " to current directory?[Yes/No]"
				if yesNo(prom) {
					_, err := exec.Command("scp", val[0]+"@"+val[1]+":"+path, ".").Output()
					if err != nil {
						log.Fatal(err)
					}
					fmt.Println("Download " + path + " Finished!")
				}
			}
		}

		if direction == "upload" {
			for _, file := range files {
				out, err := exec.Command("find", ".", "-type", "f", "-name", file).Output()
				if err != nil {
					log.Fatal(err)
				}

				paths := strings.Fields(string(out))
				for _, path := range paths {
					prom := "Copy " + path + " to remote mechine?[Yes/No]"
					if yesNo(prom) {
						_, err := exec.Command("scp", path, val[0]+"@"+val[1]+":").Output()
						if err != nil {
							log.Fatal(err)
						}
						fmt.Println("Upload " + path + " Finished!")
					}
				}
			}
		}
	}
}
