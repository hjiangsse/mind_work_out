#!/bin/sh

help_info() {
    echo "This tool will help you automate the ssh password less process"
    echo "Usage:"
    echo "  ./ssh_hero.sh -u username -m hostname"
    echo "  username: the user your want to ssh to"
    echo "  hostname: the remote mechine you want to ssh to"
}

while getopts hu:m: flag
do
    case "${flag}" in
        u) username=${OPTARG};;
        m) hostname=${OPTARG};;
        h) help_info;;
    esac
done

#gen rsa keys
if [ ! -f ~/.ssh/id_rsa ]; then
    ssh-keygen -t rsa
fi

#create .ssh directory on remote host
ssh ${username}@${hostname} mkdir -p .ssh

#send pub key to remote know hosts
cat ~/.ssh/id_rsa.pub | ssh ${username}@${hostname} 'cat >> .ssh/authorized_keys'

#test if you can login to remote host password less
ssh ${username}@${hostname}
