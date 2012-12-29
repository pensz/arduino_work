#!/bin/bash

ARDUINO_PORT=/dev/ttyACM0
ARDUINO_SPEED=9600

# Set speed for usb
stty -F $ARDUINO_PORT ispeed $ARDUINO_SPEED ospeed $ARDUINO_SPEED

# Redirect Arduino port to file descriptor 6 for reading later
exec 6<$ARDUINO_PORT

# Read data from Arduino via file descriptor 6

while true #
do
    sleep 2

    echo -ne "a\nbc_" > $ARDUINO_PORT 

    while true
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
    f=${f:0:${#f} - 1}

    echo "Received:  $f"
done
