CMU 213 Introduction to Computer Systems

[15-213/14-513/15-513: Introduction to Computer Systems (cmu.edu)](https://www.cs.cmu.edu/~213/index.html)

Labs:

[CS:APP3e, Bryant and O'Hallaron (cmu.edu)](http://csapp.cs.cmu.edu/3e/labs.html)

Videos:

[2015 Fall: 15-213 Introduction to Computer Systems : Panopto](https://scs.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx#folderID="b96d90ae-9871-4fae-91e2-b1627b43e25e"&sortColumn=0&sortAscending=true&maxResults=50)

Text books:

[CSAPP-Labs/Computer Systems A Programmers Perspective (3rd).pdf at master · Sorosliu1029/CSAPP-Labs (github.com)](https://github.com/Sorosliu1029/CSAPP-Labs/blob/master/Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)

[ebook - The C Programming Language Ritchie & kernighan -.doc (archive.org)](https://ia802802.us.archive.org/15/items/The_C_Programming_Language/The_C_Programming_Language.pdf)

Pre-requisite:

<mark> The best course I have ever seen to bootstrap C: </mark> [CSE 251 Programming in C (msu.edu)](https://www.cse.msu.edu/~cse251/)

To run docker:

https://hub.docker.com/repository/docker/luchaoqi/cmu-15213

docker-compose.yml
```
version: "3"

services:
  cmu: # name of the service
    build: .
    image: luchaoqi/cmu-15213
    container_name: cmu-15213
    volumes:
      - .:/cmu
    restart: "no"
    stdin_open: true  # --interactive Keep STDIN open even if not attached (docker exec -i)
    tty: true         # --tty Allocate a pseudo-TTY (docker exec -t)
    security_opt:
      - seccomp:unconfined
    cap_add:
      - SYS_PTRACE
```

```
docker-compose run --rm cmu
```
