#!/usr/bin/env bash

docker kill moonbox

docker build -t chadmoon/moonbox .

docker run -d -p 8085:8085 --name moonbox chadmoon/moonbox

google-chrome http://localhost:8085