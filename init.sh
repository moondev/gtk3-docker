#!/usr/bin/env bash

nohup broadwayd :5 &

mkdir -p /root/Desktop
mkdir -p /root/.config/nautilus
sleep 5

#xfce4-terminal
#remmina
#nautilus
#gnome-terminal
#/tilix/tilix
#midori
gsettings set org.gnome.desktop.interface gtk-theme Arc-Darker

git clone https://github.com/optimisme/gjs-examples.git
cd /gjs-examples
gjs egHeader.js
# cd /gjs
# gjs window.js