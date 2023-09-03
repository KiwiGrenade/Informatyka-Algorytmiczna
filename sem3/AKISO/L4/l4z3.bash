#!/bin/bash

IMAGE_URL=$(curl --silent https://api.thecatapi.com/v1/images/search | jq -r '.[]|.url')
curl --silent $IMAGE_URL > catimage.jpg

catimg -r 2 -H 75 catimage.jpg
echo $(curl --silent https://api.chucknorris.io/jokes/random | jq -r '.value')
rm catimage.jpg
