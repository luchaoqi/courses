[15-213/14-513/15-513: Introduction to Computer Systems (cmu.edu)](https://www.cs.cmu.edu/~213/index.html)

## Labs

[CS:APP3e, Bryant and O'Hallaron (cmu.edu)](http://csapp.cs.cmu.edu/3e/labs.html)

[15-213/15-513 Intro to Computer Systems: Resources](https://www.cs.cmu.edu/~213/resources.html)
> pick an available term and select `Schedule` on left


## Lab environment

To run with docker (zsh included): https://hub.docker.com/repository/docker/luchaoqi/cmu-15213

```
docker-compose run --rm cmu
```

<del>docker run --rm -it -v "$PWD":/cmu luchaoqi/cmu-15213 --cap-add=SYS_PTRACE --security-opt seccomp=unconfined zsh<del>

[Computer Systems: A Programmer's Perspective, 3/E (CS:APP3e)](https://csapp.cs.cmu.edu/3e/students.html)
[Interactive shell using Docker Compose - Stack Overflow](https://stackoverflow.com/questions/36249744/interactive-shell-using-docker-compose) <del>docker-compose up<del>

> You can set stdin_open: true, tty: true, however that won't actually give you a proper shell with up, because logs are being streamed from all the containers.

## Resources

C bootcamp:
[CSE 251 Programming in C (msu.edu)](https://www.cse.msu.edu/~cse251/)

Checkout the `Handouts` session on the top; it gives lots of concise information:
[CS107 Computer Organization & Systems (stanford.edu)](https://user-images.githubusercontent.com/46330265/172753677-b4bac483-43b1-4aab-832e-22039cb072f1.png)


## Videos

[2015 Fall: 15-213 Introduction to Computer Systems : Panopto](https://scs.hosted.panopto.com/Panopto/Pages/Sessions/List.aspx#folderID="b96d90ae-9871-4fae-91e2-b1627b43e25e"&sortColumn=0&sortAscending=true&maxResults=50)

## Text books

<mark> Reading the text book three times makes everything easy </mark>

[CSAPP-Labs/Computer Systems A Programmers Perspective (3rd).pdf at master · Sorosliu1029/CSAPP-Labs (github.com)](https://github.com/Sorosliu1029/CSAPP-Labs/blob/master/Computer%20Systems%20A%20Programmers%20Perspective%20(3rd).pdf)

[ebook - The C Programming Language Ritchie & kernighan -.doc (archive.org)](https://ia802802.us.archive.org/15/items/The_C_Programming_Language/The_C_Programming_Language.pdf)
