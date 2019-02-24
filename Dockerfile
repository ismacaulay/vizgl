FROM debian:stretch

RUN apt-get update && \
    apt-get install -y curl python && \
    mkdir -p /usr/src/app && \
    echo "source /emsdk-portable/emsdk_env.sh" >> /etc/bash.bashrc && \
    curl https://s3.amazonaws.com/mozilla-games/emscripten/releases/emsdk-portable.tar.gz | tar -xvzf -

ENV CC emcc
ENV CXX em++
COPY ./tools/waf /usr/local/bin/waf

WORKDIR /emsdk-portable
RUN ./emsdk update && \
    ./emsdk install latest && \
    ./emsdk activate latest

WORKDIR /usr/src/app
