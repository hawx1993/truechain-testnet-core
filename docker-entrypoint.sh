#!/bin/bash

log(){
    echo -e "[$(date +'%D %H:%M:%S %Z')] - $*"
}

# Add as command if needed
if [ "${1:0:1}" = '-' ]; then
    set -- truechaind "$@"
fi

if [ "$1" = 'truechaind' ]; then    
    cd $TC_HOME

    groupadd truechaind
    useradd truechaind -g truechaind

    # TODO: handle secrets like mysql pass differently
    MYSQL_PASS=truechainpass

    while ! mysql -u root --host=mysqldb --port=3306 -p$MYSQL_PASS  -e ";" ; do
	echo "Can't connect to mysqldb, retrying after 5 seconds.."
	sleep 5
    done

    sed -i s#host=localhost#host=mysqldb#g $TC_HOME/build/truechaind.cfg
    mysql -u root --host=mysqldb --port=3306 --password=$MYSQL_PASS -e 'create database transaction;'
    mysql -u root --host=mysqldb --port=3306 --password=$MYSQL_PASS -e 'create database ledger;'
    mysql -u root --host=mysqldb --port=3306 --password=$MYSQL_PASS -e 'create database wallet;'

    set -e
    # ./bin/truechainConsole start
    cd $TC_HOME/build/
    ./bin/truechain --conf ./truechaind.cfg
fi

exec "$@"
