FROM gcc:latest
LABEL MAINTAINER="Daniel N. Gisolfi"

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    build-essential \
    git

ENV WORKDIR /mercury/

WORKDIR ${WORKDIR}
