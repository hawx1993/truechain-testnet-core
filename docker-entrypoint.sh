#!/bin/bash

set -e

log(){
    echo -e "[$(date +'%D %H:%M:%S %Z')] - $*"
}

# Add as command if needed
if [ "${1:0:1}" = '-' ]; then
    set -- truechaind "$@"
fi

if [ "$1" = 'truechaind' ]; then    
    cd $TC_HOME
    ./bin/truechainConsole start
fi

exec "$@"
