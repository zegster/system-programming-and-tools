#!/bin/bash
##Author:    Duc Ngo
##Course:    CS2750-001
##Name:      listEmptyDIr.sh
##Purpose:   If a file is a directory to the file EmptyDir.txt in your current
##           directory. (see Project #2 part A for details)
##---------------------------------------------------------------------------

##Function [line]: displaying a line
function line()
{
    for i in $(seq 0 $2)
    do
        echo -n "$1"
    done
    echo
}

##Define usage message
USAGE="Usage: $0 directory_name"

##- - - - - Start - - - - -
line ">" 75

##Check number of parameter
if [[ $# -eq 0 ]]
then
    echo "$0: Missing parameter. Exiting..."
    echo "$USAGE"
    line "<" 75
    echo
    exit 1
elif [[ $# -gt 1 ]]
then
    echo "$0: Too many parameters. Exiting..."
    echo "$USAGE"
    line "<" 75
    echo
    exit 1
fi

##Check to see if parameter one is a directory
if [[ ! -d $1 ]]
then
    echo "$1 is not a directory or it doesn't exists. Exiting..."
    echo "$USAGE"
    line "<" 75
    echo
    exit 1
fi

##Check if directory empty. If so, output to a txt file
dir=($(ls $1))
if [[ -z $dir ]]
then
    echo "$1" >> EmptyDir.txt
    echo "$1 is empty. Exiting..."
    line "<" 75
    echo
    exit 1
fi

##Display all file in this directory
echo "Item(s) in $1:"
for file in ${dir[@]}
do
    echo "$file"
done

line "<" 75
echo "Done"
echo

##- - - - - END - - - - -
