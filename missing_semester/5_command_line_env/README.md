# Takeaways

```
# job control

$ sleep 1000
^Z
[1]  + 18653 suspended  sleep 1000

$ nohup sleep 2000 &
[2] 18745
appending output to nohup.out

$ jobs
[1]  + suspended  sleep 1000
[2]  - running    nohup sleep 2000

$ bg %1
[1]  - 18653 continued  sleep 1000

$ jobs
[1]  - running    sleep 1000
[2]  + running    nohup sleep 2000

$ kill -STOP %1
[1]  + 18653 suspended (signal)  sleep 1000

$ jobs
[1]  + suspended (signal)  sleep 1000
[2]  - running    nohup sleep 2000

$ kill -SIGHUP %1
[1]  + 18653 hangup     sleep 1000

$ jobs
[2]  + running    nohup sleep 2000

$ kill -SIGHUP %2

$ jobs
[2]  + running    nohup sleep 2000

$ kill %2
[2]  + 18745 terminated  nohup sleep 2000

$ jobs
```

```
# ssh

ssh-keygen -t ed25519 -C "your_email@example.com"
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
# add the public key to remote
cat ~/.ssh/id_ed25519.pub | ssh <user>@<remote> 'cat >> ~/.ssh/authorized_keys'
# OR
ssh-copy-id -i ~/.ssh/id_ed25519.pub <user>@<remote>
```

[ssh port forwarding](https://unix.stackexchange.com/a/115906/482117)

[Tmux Cheat Sheet & Quick Reference](https://tmuxcheatsheet.com/)

```
# ~/.ssh/config
Host vm
    User foobar
    HostName 172.16.174.141
    Port 2222
    IdentityFile ~/.ssh/id_ed25519
    LocalForward 9999 localhost:8888

# Configs can also take wildcards
Host *.mit.edu
    User foobaz

# In most cases, after copying the public key to remote_server/authorized_keys
# Only thing needed to configure is the following settings in config file
Host vs
    HostName <ip address: 0.0.0.0>
    User <username: lqi>
```



# Exercises

```
sleep 60 &
pgrep -f "sleep 60" | wait && ls
```

```
sleep 600 &
# open a new session
# jobs: Display status of jobs in the current session.
jobs -l # show nothing because it's in a new session
# ps aux: Display status of all sessions
# start a new shell session and run the following command
ps aux | pgrep -f "sleep 600"
. pidwait.sh $(ps aux | pgrep -f "sleep 600")
```
