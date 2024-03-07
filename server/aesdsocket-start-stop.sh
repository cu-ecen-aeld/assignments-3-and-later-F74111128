#!/bin/sh

if [ "$1" = "start" ]; then
    echo "Starting aesdsocket"
    start-stop-daemon -S -n aesdsocket -a /usr/bin/aesdsocket -- -d
elif [ "$1" = "stop" ]; then
    echo "Stopping aesdsocket"
    start-stop-daemon -K -n aesdsocket
fi
