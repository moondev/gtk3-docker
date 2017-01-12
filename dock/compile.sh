#!/usr/bin/env bash

gcc `pkg-config --cflags gtk+-3.0` -o dock example-0.c `pkg-config --libs gtk+-3.0`
./dock