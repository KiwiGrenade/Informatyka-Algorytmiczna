#!/bin/bash
INPUT_DIR="test/input"
OUTPUT_DIR="test/output"
REF_DIR="test/ref"

TEST_NAME_LIST=("test1.xml")
TEST_RESULT_LIST=()

OUTPUT_PREFIX="output_"
REF_PREFIX="ref_"

for TEST_NAME in "${TEST_NAME_LIST[@]}"
do
	# create the output files 
	OUTPUT_NAME="$OUTPUT_PREFIX$TEST_NAME"
	REF_NAME="$REF_PREFIX$TEST_NAME"
	
	if [[ $TEST_NAME == *D* ]]
	then
		(./ex2 -d < $INPUT_DIR/$TEST_NAME) > $OUTPUT_DIR/$OUTPUT_NAME
	else
		(./ex2 < $INPUT_DIR/$TEST_NAME) > $OUTPUT_DIR/$OUTPUT_NAME
	fi
	
	if cmp -l $REF_DIR/$REF_NAME $OUTPUT_DIR/$OUTPUT_NAME
	then
		TEST_RESULT_LIST+=("PASSED")
	else
		TEST_RESULT_LIST+=("FAILED")
	fi
done

for i in "${!TEST_NAME_LIST[@]}"
do
	echo "${TEST_NAME_LIST[$i]} ..... ${TEST_RESULT_LIST[$i]}"
done