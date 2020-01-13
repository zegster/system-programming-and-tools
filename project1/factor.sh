#!/bin/bash
#Author:    Duc Ngo
#Course:    CS2750-001
#Name:      factor.sh
#Purpose:   Write a Bash shell script factor.sh that find the smallest factor for an input number.
#           (see Project #1 part B for details)

#Define usage message
USAGE="Usage: $0"

#Prompt user to enter an interger from 10 to 100
echo -n "Please enter an integer n from 10 to 100: "
read nValue

#Check for the input range
if [[ $nValue -lt 10 ]]
then
    echo "Warning: Integer must be greater 10..."
    echo "Exiting..."
    exit 1
elif [[ $nValue -gt 100 ]] 
then
    echo "Warning: Integer must be less than 100..."
    echo "Exiting..."
    exit 1
fi

#Finding the smallest factor
for (( i=2;i<$nValue;i++ ))
do
    result=$(( $nValue%$i ))
    if [[ $result -eq 0 ]]
    then
        echo "The smallest factor is: $i"
        exit 0
    fi
done

echo "$nValue is already the smallest the factor."

#-----END-----
