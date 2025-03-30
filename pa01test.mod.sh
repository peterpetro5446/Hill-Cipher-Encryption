#!/bin/bash

# Check the file name passed as argument
case $1 in
    pa01.c)
        echo "Compiling pa01.c..."
        rm -f -- pa01
        gcc -o pa01 pa01.c
        if [ $? -ne 0 ]; then 
            echo "Compile of pa01.c failed"
            echo "Good bye!"
            exit 1 
        fi
        EXE="./pa01"
        ;;
    *)
        echo "Invalid source file name"
        echo "-> should be pa01.c"
        exit 1
esac

echo "Compile of pa01.c succeeded."

# Test cases loop
for i in {1..5}; do
    echo "Case #$i"
    KEY="testfiles/k${i}.txt"
    PLAINTEXT="testfiles/p${i}.txt"
    BASE="testfiles/base${i}.txt"
    OUTPUT="testfiles/output/stu${i}Output.txt"

    if [[ -f "$KEY" && -f "$PLAINTEXT" && -f "$BASE" ]]; then
        $EXE "$KEY" "$PLAINTEXT" > "$OUTPUT"
        diff -w "$OUTPUT" "$BASE"
        echo "Case #$i - complete"
    else
        echo "Case #$i - missing one or more files (k${i}.txt, p${i}.txt, base${i}.txt)"
    fi
done