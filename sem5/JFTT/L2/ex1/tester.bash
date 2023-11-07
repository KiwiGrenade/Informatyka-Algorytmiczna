#!/bin/bash
INPUT_DIR="test/input"
OUTPUT_DIR="test/output"
REF_DIR="test/ref"
TEST_NAME1="l2z1a"
TEST_NAME2="l2z1b"

# create the output files 
(./ex1 < $INPUT_DIR/$TEST_NAME1.txt) > $OUTPUT_DIR/output_$TEST_NAME1.txt
(./ex1 < $INPUT_DIR/$TEST_NAME2.txt) > $OUTPUT_DIR/output_$TEST_NAME2.txt

# compare ref file for test1
if cmp -l $REF_DIR/$TEST_NAME1.r1.txt $OUTPUT_DIR/output_$TEST_NAME1.txt || cmp -l $REF_DIR/$TEST_NAME1.r2.txt $OUTPUT_DIR/output_$TEST_NAME1.txt
then
	TEST_RESULT1="PASSED"
else
	TEST_RESULT1="FAILED"
fi
# compare ref file for test2
if cmp -l $REF_DIR/$TEST_NAME2.r1.txt $OUTPUT_DIR/output_$TEST_NAME2.txt || cmp -l $REF_DIR/$TEST_NAME2.r2.txt $OUTPUT_DIR/output_$TEST_NAME2.txt
then
	TEST_RESULT2="PASSED"
else
	TEST_RESULT2="FAILED"
fi

echo "Test $TEST_NAME1 $TEST_RESULT1"
echo "Test $TEST_NAME2 $TEST_RESULT2"
