FROM debian:buster-20201012

RUN apt-get update \
    && apt-get install -y \
        curl \
        unzip \
        g++ \
        make \
        cmake \
        pkg-config

# install io-buffer library
RUN mkdir -p /tmp/io-buffer \
    && cd /tmp/io-buffer \
    && curl -LO "https://github.com/Alexander1000/io-buffer/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd io-buffer-master \
    && cmake . \
    && make \
    && make install \
    && rm -rf /tmp/io-buffer

# install cpp-unit-test library
RUN mkdir -p /tmp/cpp-utils \
    && cd /tmp/cpp-utils \
    && curl -LO "https://github.com/Alexander1000/cpp-unit-test/archive/master.zip" \
    && unzip -a master.zip \
    && rm -f master.zip \
    && cd cpp-unit-test-master \
    && cmake . \
    && make \
    && make install \
    && rm -rf /tmp/cpp-utils

COPY . /app

RUN cd /app && cmake . && make && make install \
    && cd tests && cmake . && make

WORKDIR /app/tests

ENTRYPOINT ["./json-analyzer-tests"]
