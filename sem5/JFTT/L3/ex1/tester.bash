#!/bin/bash
(./zad1 < test/testInput.txt) > test/testOutput.txt;
diff test/testOutput.txt test/testRef.txt
