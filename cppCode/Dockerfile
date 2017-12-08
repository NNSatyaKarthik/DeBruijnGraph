# Steps to run the docker file
# use sudo based on your host machine (for linux)
# docker build -t ub:latest .

FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y --no-install-recommends apt-utils build-essential sudo git wget
RUN wget https://cmake.org/files/v3.10/cmake-3.10.0-Linux-x86_64.sh && chmod +x cmake-3.10.0-Linux-x86_64.sh && sudo ./cmake-3.10.0-Linux-x86_64.sh && sudo ln -s `pwd`/cmake-3.10.0-Linux-x86_64/bin/* /usr/local/bin && cmake --version