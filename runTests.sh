#!/bin/bash
# Script used to automate the running of test cases
# Test input should be in .in files, output in .out files

EXECUTABLE="./main"  # Name of the compiled c program
TEST_DIR="./tests"   # Directory containing the tests

totalTests=0
passedTests=0
failedTests=""

# Run tests (assumes files names from [1..n].in / .out)
for infile in "$TEST_DIR"/*.in; do
    totalTests=$((totalTests + 1))

    expected="${infile%.in}.out"
    actual=$($EXECUTABLE < "$infile")

    if [ "$actual" = "$(cat $expected)" ]; then
        passedTests=$((passedTests + 1))   
    else 
        failedTests+="\n\nIn test $infile:\nexpected: $(cat $expected)\nactual  : $actual"
    fi
done

# Show test results
if [ "$totalTests" -eq "$passedTests" ]; then
    echo "Passed all $totalTests/$totalTests tests!"
else
    echo -e "There were test failures, passed $passedTests/$totalTests tests:$failedTests"
fi
