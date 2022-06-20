FROM ubuntu:20.04

ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update -y && apt-get install -y \
    python3-venv python3-pip \
    build-essential \
    binutils \
    gdb \
    gcc-multilib \
    valgrind \
    python \
    vim \
    lsb-release wget software-properties-common \
    git \
    && rm -rf /var/lib/apt/lists/*

# https://apt.llvm.org/
RUN bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"

RUN apt-get install clang clang-format -y

# install zsh and oh-my-zsh

RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.2/zsh-in-docker.sh)" -- \
-t 'jtriley' \
-p git \
-p https://github.com/zsh-users/zsh-completions \
-p https://github.com/zsh-users/zsh-autosuggestions \
-p https://github.com/zsh-users/zsh-syntax-highlighting \
-p https://github.com/zsh-users/zsh-history-substring-search

# install radare2
RUN git clone https://github.com/radareorg/radare2
RUN bash -c radare2/sys/install.sh

WORKDIR /cmu
