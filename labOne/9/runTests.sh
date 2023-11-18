#!/bin/bash

EXECUTABLE="./main"
TEST_DIR="./tests"

totalTests=0
passedTests=0
failedTests=""

# Run tests
for infile in "$TEST_DIR"/*.in; do
    totalTests=$((totalTests + 1))

    expected="${infile%.in}.out"
    actual=$($EXECUTABLE < "$infile")

    if [ "$actual" = "$(cat $expected)" ]; then
        passedTests=$((passedTests + 1))   
    else 
        failedTests+="\nIn test $infile:\nexpected: $(cat $expected)\nactual  : $actual"
    fi
done

# Print test results
if [ "$totalTests" -eq "$passedTests" ]; then
    echo "Passed all $totalTests/$totalTests tests!"
else
    echo -e "There were test failures, passed $passedTests/$totalTests tests:$failedTests"
fi
