#!/usr/bin/env bash

cd dock; ./compile.sh; cd ../

docker kill moonbox

docker rm moonbox

docker build -t chadmoon/moonbox .

docker run -d -p 8085:8085 --name moonbox chadmoon/moonbox

