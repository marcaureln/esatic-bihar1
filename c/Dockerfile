FROM ubuntu:latest

WORKDIR /app

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    cmake \
    gdb \
    wget \
    python-pip \
    libmysqlclient-dev

COPY app .

RUN gcc -c *.c && gcc *.o -o app

CMD ["./app"]