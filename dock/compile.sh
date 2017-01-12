#!/usr/bin/env bash

gcc `pkg-config --cflags gtk+-3.0` -o dock dock.c `pkg-config --libs gtk+-3.0`
