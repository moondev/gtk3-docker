#!/usr/bin/env bash

docker kill moonbox

docker rmi moonbox

docker run -d -p 8085:8085 moonbox

google-chrome http://localhost:8085