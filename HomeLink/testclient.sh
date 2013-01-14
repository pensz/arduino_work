#!/bin/bash

if [ -z "$1" ]
then
    echo "Usage : $0 devicefile "
    exit 1
fi

ARDUINO_PORT=$1
ARDUINO_SPEED=9600

# Set speed for usb
uname=$(uname)
if [ "$uname" == 'Linux' ]
then
    stty -F $ARDUINO_PORT ispeed $ARDUINO_SPEED ospeed $ARDUINO_SPEED
elif [ "$uname" == 'Darwin' ]
then
    stty -a -f $ARDUINO_PORT speed $ARDUINO_SPEED
fi
echo "Set speed OK"

# Redirect Arduino port to file descriptor 6 for reading later
exec 6<$ARDUINO_PORT
echo "Redirect OK"

sleep 3 # Wait for Arduino is ok


function rw {
    echo -ne $1'\0' > $ARDUINO_PORT

    while true  # Wait for Arduino reply
    do
        read -u 6 f
        if [ -z "$f" ]
        then
            continue
        else
            break
        fi
    done

    # Remove trailing carriage return character
    f=${f:0:${#f}-1}

    echo "Reply: $f"

}

#rw "T FDB04F"
#sleep 8
rw "T FD40BF"
rw "T FD906F"
#rw "hello"
#rw "auth"
#rw "username:pensz"
#rw "password:pensz"
