# Pull base image.
FROM ubuntu:14.04

# Install.
RUN \
  sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
  apt-get update && \
  apt-get -y upgrade && \
  apt-get install -y build-essential && \
  apt-get install -y software-properties-common && \
  apt-get install -y byobu curl git htop man unzip vim wget

RUN \
  apt-get install -y cmake git g++ protobuf-compiler python-dev \
          libprotobuf-dev libssl-dev liblz4-dev zlib1g-dev \
          libmysqlclient-dev libsqlite3-dev libbz2-dev \
          libsnappy-dev zlib1g-dev && \
  rm -rf /var/lib/apt/lists/*

RUN mkdir -p /opt/truechain
WORKDIR	/opt/truechain

RUN git clone https://github.com/truechain/truechain-testnet-core.git && cd truechain-testnet-core && mkdir libs/ build/

ENV TC_HOME=/opt/truechain/truechain-testnet-core
WORKDIR	$TC_HOME/libs

# clone library dependencies
RUN  wget https://excellmedia.dl.sourceforge.net/project/soci/soci/soci-3.2.3/soci-3.2.3.zip && \
    unzip soci-3.2.3.zip && mv soci-3.2.3 soci && mkdir soci/build
RUN git clone https://github.com/zaphoyd/websocketpp && mkdir websocketpp/build
RUN git clone https://github.com/facebook/rocksdb && mkdir rocksdb/build

# download and extract C++ Boost 1.58 Library
RUN cd /opt/truechain && \
    wget http://sourceforge.net/projects/boost/files/boost/1.58.0/boost_1_58_0.tar.bz2 -O boost_1_58.zip && \
    tar xvf boost_1_58.zip

# compile boost
RUN cd /opt/truechain/boost_1_58_0 && ./bootstrap.sh && ./b2 && ./b2 install

# setup libs/soci
RUN cd $TC_HOME/libs/soci/build && cmake .. && make -j4 && make install
RUN sed -i s#"soci-backend.h"#"../soci-backend.h"#g /usr/local/include/soci/mysql/soci-mysql.h && \
    sed -i s#"soci-backend.h"#"../soci-backend.h"#g /usr/local/include/soci/sqlite3/soci-sqlite3.h

# setup libs/rocksdb
RUN cd $TC_HOME/libs/rocksdb/build && cmake .. && make -j4 && make install

# setup libs/websocketpp
RUN cd $TC_HOME/libs/websocketpp/build && cmake .. && make -j4 && make install

ENV BOOST_ROOT=/usr/local/lib/

# finally, compile truechain
RUN cd $TC_HOME/build && cmake .. && make -j4

COPY docs/truechaind.cfg.sample $TC_HOME/build/truechaind.cfg

COPY docker-entrypoint.sh /
ENTRYPOINT ["/docker-entrypoint.sh"]

CMD ["truechaind"]
