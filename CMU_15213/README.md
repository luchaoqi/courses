[15-213/14-513/15-513: Introduction to Computer Systems (cmu.edu)](https://www.cs.cmu.edu/~213/index.html)

## Labs

[CS:APP3e, Bryant and O'Hallaron (cmu.edu)](http://csapp.cs.cmu.edu/3e/labs.html)

[15-213/15-513 Intro to Computer Systems: Resources](https://www.cs.cmu.edu/~213/resources.html)
> pick an available term and select `Schedule` on left

## Videos

[2015 Fall: 15-213 Introduction to Computer Systems : Panopto](https://scs.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx#folderID="b96d90ae-9871-4fae-91e2-b1627b43e25e"&sortColumn=0&sortAscending=true&maxResults=50)

## Text books / Resources

<mark> Reading the text book three times makes everything easy </mark>

[CSAPP-Labs/Computer Systems A Programmers Perspective (3rd).pdf at master · Sorosliu1029/CSAPP-Labs (github.com)](https://github.com/Sorosliu1029/CSAPP-Labs/blob/master/Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)

[Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)](https://csapp.cs.cmu.edu/3e/students.html)

## Pre-requisite

C bootcamp:
[CSE 251 Programming in C (msu.edu)](https://www.cse.msu.edu/~cse251/)


To run with docker (zsh included): https://hub.docker.com/repository/docker/luchaoqi/cmu-15213

```
docker run --rm -it -v "$PWD":/cmu luchaoqi/cmu-15213 --cap-add=SYS_PTRACE --security-opt seccomp=unconfined zsh
```
<del>docker-compose run --rm cmu<del>
