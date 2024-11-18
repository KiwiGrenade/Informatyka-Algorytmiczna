#!/bin/bash

find $1 -type f -exec cat {} \; | tr -s " " | tr " " "\n" | sort | uniq -c

