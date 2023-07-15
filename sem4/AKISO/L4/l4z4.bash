#!/bin/bash

cd $1

find . -type f -print0 | xargs -0 -I "{}" sh -c 'echo -n $(md5sum "{}") " " ; echo $(du -h "{}") | cut -f1 -d " " ' | sort -h -k2 | uniq -w32 --all-repeated=separate | awk '{print $2 "|" $3}' | column -t -s "|"
