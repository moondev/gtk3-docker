#!/usr/bin/env bash

nohup broadwayd :5 &

mkdir -p /root/Desktop
mkdir -p /root/.config/nautilus
sleep 2

#xfce4-terminal
nautilus