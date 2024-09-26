FROM ubuntu

RUN apt-get update -y \
    && apt install curl -y \
    && apt-get install g++ -y \
    && apt-get install -y libboost-all-dev \
    && apt-get install -y libcurl4-openssl-dev \
    && apt-get install -y cmake

RUN apt install unzip -y

RUN mkdir xerces-c \
    && cd xerces-c \
    && curl -o xerces-c.zip https://dlcdn.apache.org//xerces/c/3/sources/xerces-c-3.2.5.zip \
    && unzip xerces-c.zip -d . && mv xerces-c-*/* .

RUN cd xerces-c \
    && ./configure --disable-shared --enable-xmlch-uint16_t --prefix=$(pwd)/_build \
    && make -j \
    && make install
