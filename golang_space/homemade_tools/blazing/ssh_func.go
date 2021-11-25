package main

import (
	"fmt"
	"time"

	"golang.org/x/crypto/ssh"
)

//ssh session
type SshSessionInfo struct {
	client  *ssh.Client
	session *ssh.Session
}

func (info *SshSessionInfo) Client() *ssh.Client {
	return info.client
}

func (info *SshSessionInfo) Session() *ssh.Session {
	return info.session
}

func (info *SshSessionInfo) RefreshSession() error {
	newSession, err := info.client.NewSession()
	if err != nil {
		return err
	}

	info.session = newSession
	return nil
}

func (info *SshSessionInfo) CloseSession() error {
	return info.session.Close()
}

func (info *SshSessionInfo) Close() error {
	err := info.client.Close()
	if err != nil {
		return err
	}

	err = info.session.Close()
	if err != nil {
		return err
	}

	return nil
}

/*
 * use user_name, host_ip and passwd to create a
 * ssh session(client + session)
 */
func GenSshSession(user, host, passwd string) (*SshSessionInfo, error) {
	auth := make([]ssh.AuthMethod, 0)
	auth = append(auth, ssh.Password(passwd))

	clientConfig := &ssh.ClientConfig{
		User:            user,
		Auth:            auth,
		Timeout:         6 * time.Second,
		HostKeyCallback: ssh.InsecureIgnoreHostKey(),
	}

	addr := fmt.Sprintf("%s:%d", host, 22)
	client, err := ssh.Dial("tcp", addr, clientConfig)
	if err != nil {
		return nil, err
	}

	session, err := client.NewSession()
	if err != nil {
		return nil, err
	}

	return &SshSessionInfo{
		client:  client,
		session: session,
	}, nil
}
