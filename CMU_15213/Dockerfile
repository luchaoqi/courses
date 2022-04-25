FROM ubuntu:20.04

ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

WORKDIR /cmu

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
    && rm -rf /var/lib/apt/lists/*

# https://apt.llvm.org/
# RUN bash -c "$(wget -O - https://apt.llvm.org/llvm.sh)"
RUN wget https://apt.llvm.org/llvm.sh
RUN chmod +x llvm.sh && ./llvm.sh all
# RUN chmod +x llvm.sh
# RUN ./llvm.sh all

RUN apt-get install clang clang-format -y
