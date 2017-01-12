#!/usr/bin/env bash

nohup broadwayd :5 &

export GDK_BACKEND=broadway
export BROADWAY_DISPLAY=:5

sleep 2

/dock