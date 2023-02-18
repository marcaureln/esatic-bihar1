FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    cmake \
    gdb \
    wget \
    python-pip \
    libmysqlclient-dev

COPY . .

CMD ["make", "build"]