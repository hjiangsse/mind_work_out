package main

import (
	"fmt"
	"time"

	"golang.org/x/crypto/ssh"
)

type MechineInfo struct {
	Ip     string `json:"ip"`
	User   string `json:"user"`
	Passwd string `json:"passwd"`
}

//connect to remote mechine, return a "ssh session"
func genSshClient(mInfo *MechineInfo, port int) (*ssh.Client, error) {
	var (
		auth         []ssh.AuthMethod
		addr         string
		clientConfig *ssh.ClientConfig
		client       *ssh.Client
		err          error
	)

	auth = make([]ssh.AuthMethod, 0)
	auth = append(auth, ssh.Password(mInfo.Passwd))

	clientConfig = &ssh.ClientConfig{
		User:            mInfo.User,
		Auth:            auth,
		Timeout:         5 * time.Second,
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	addr = fmt.Sprintf("%s:%d", mInfo.Ip, port)
	if client, err = ssh.Dial("tcp", addr, clientConfig); err != nil {
		return nil, err
	}

	return client, nil
}

func genNewSession(client *ssh.Client) (*ssh.Session, error) {
	ss, err := client.NewSession()
	if err != nil {
		return nil, err
	}

	return ss, nil
}

func main() {
	mInfo := MechineInfo{
		Ip:     "192.168.2.104",
		User:   "jingle",
		Passwd: "Life123",
	}

	go func() {
		sshClient, err := genSshClient(&mInfo, 22)
		if err != nil {
			panic(err)
		}

		for {
			ss, err := genNewSession(sshClient)
			if err != nil {
				panic(err)
			}

			time.Sleep(5 * time.Second)
			ss.Close()
		}
	}()

	time.Sleep(100 * time.Second)
}
