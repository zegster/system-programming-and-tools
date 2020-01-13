#!/bin/bash
#Author:    Duc Ngo
#Course:    CS2750-001
#Name:      testaverager.sh
#Purpose:   Write a bash script named testaverager.sh that will determine if a person has passed a class.
#           (see Project #1 part C for details)

#Define usage message
USAGE="Usage: $0 [first_name] [last_name] [score_1] score_2 ..."

#Check for correct number of arguments
if [[ $# -lt 3 ]]
then
    echo "$0: missing argument. Need to pass at least 3 arguments"
    echo $USAGE
    exit 1
fi

#Calculating the average score
totalNum=$(( $# - 2 ))
counter=3
pattern="[0-9]"
average=0

for args in ${@:3}
do
    #Check for invalid non-digit from argument 3 and beyond
    args=${args%%.*}
    if [[ $args =~ $pattern ]]
    then
        average=$(( average+$args ))
        counter=$(( counter+1 ))
    else
        echo "Invalid parameter at argument #$counter"
        echo "Exiting..."
        exit 1
    fi 
done
average=$(( average/totalNum ))

#Display appropriate message base on the score
if [[ $average -lt 70 ]]
then
    echo "Sorry $1 $2, but you will have to retake the class! Your average: $average"
else
    echo "Congratulations $1 $2, you passed with an average of $average!"
fi
