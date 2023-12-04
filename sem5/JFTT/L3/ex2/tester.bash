#!/bin/bash
(python3 zad2.py < test/testInput.txt) > test/testOutput.txt;
diff test/testOutput.txt test/testRef.txt
