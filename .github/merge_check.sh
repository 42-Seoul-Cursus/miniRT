#!/bin/bash

# Check if there are any norminette errors
if grep -q "Error:" norm_output.txt; then
    echo "Norminette errors found. Merging is not allowed."
    exit 1
fi
