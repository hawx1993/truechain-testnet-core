# depend libs

## basic requirement

Only for Ubuntu 14.04 now

# step 1, change ubuntu source to ali
```
deb http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ trusty-backports main restricted universe multiverse
```

# step 2, install necessary tools
```
sudo apt-get install -y cmake git g++ protobuf-compiler python-dev
```

install lib dependcies
```
sudo apt-get install -y libprotobuf-dev libssl-dev liblz4-dev zlib1g-dev
```

get boost 1.58

```
sudo apt-get install libboost1.58
```

build install and
```
export BOOST_ROOT=root dir of boost
# export BOOST_ROOT=/usr/lib/x86_64-linux-gnu/
```

# step 3, install soci library

Download and extract (rename soci-x.y.z) to libs/soci https://sourceforge.net/projects/soci/files/

```
sudo apt-get install -y libmysqlclient-dev libsqlite3-dev
cd libs/soci
mkdir build && cd build
cmake ../
make [-j8] && sudo make install
```

You might have to change `/usr/local/include/soci/mysql/soci-mysql.h`

```
#include "soci-backend.h"

to

#include "../soci-backend.h"
```

..and in

```
#include "soci-backend.h"

to

#include "../soci-backend.h"
```

# step 4 install rocksdb library

Download and extract to libs/rocksdb https://github.com/facebook/rocksdb

```
sudo apt-get install libsnappy-dev zlib1g-dev libbz2-dev
cd libs/rocksdb
mkdir build && cd build
cmake ..
make [-j8] && sudo make install
```

# step 5, install websocketpp library

Download and extract to libs/websocketpp https://github.com/zaphoyd/websocketpp

use branch `develop` on github src code of websocketpp (master is not stable)
```
cd libs/websocketpp
mkdir build && cd build
cmake ..
make [-j8] && sudo make install
```

# step6, build truechain
```
mkdir build && cd build
cmake .. && make [-j8]
```
