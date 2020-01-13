#!/bin/bash
#Author:    Duc Ngo
#Course:    CS2750-001
#Name:      info.sh
#Purpose:   Write a Bash shell script named info.sh. The command for execution must include two
#           command-line parameters. The output of this script must contain the following information.
#           (see Project #1 part A for details)

#Turn on tracing
#set -x
#Turn off tracing
#set +x

#Function [line]: displaying a line
function line()
{
    for i in $(seq 0 $2)
    do
        echo -n "$1"
    done
    echo
}

#Define usage message
USAGE="Usage: $0 [file_name] [directory_name]"

#-----START-----
line ">" 75

#Check for correct number of agruments
if [ $# -lt 2 ]
then
    echo "$0: missing argument. Need to pass exactly two arguments"
    echo "$USAGE"
    echo "Exiting..."
    line "<" 75
    echo
    exit 1
fi

#Check for valid file
if [ ! -f "$1" ]
then
    echo "$1 is not a file. Exiting..."
    line "<" 75
    echo
    exit 1
fi

#Check for valid directory
if [ ! -d "$2" ]
then
   echo "$2 is not a directory. Exiting..."
   line "<" 75
   echo
   exit 1
fi

#- - - - - Display Information - - - - -
#The name of the script
echo "Script Name: $0"

#Display usage message
echo "$USAGE"

#Current date and time
echo -n "Date & Time: " ; date

#The name of the user
echo -n "Current User: " ; id -nu

#The name of current working directory
echo -n "Current Directory: " ; pwd

#The name of UNIX machine
echo -n "UNIX machine information: " ; hostname

#The name of login shell
echo "Current login shell: ${SHELL##*/}"

#Contents of the required file
echo "Contents of the selected file: "
line "-" 75 ; cat $1 ; line "-" 75

#Number of text line in the file
echo -n "Number of text lines in the file: " ; wc -l $1 ; echo

#Listing of the required directory
echo "Contents of the selected directory: "
line "-" 75 ; ls -al $2 ; line "-" 75 ; echo

#Total number of parameters of the script
echo "Total number of paramaters: $#"

#Calendar for October of the current year
cal 10 $(date +%Y)

#Disk usage
echo "Current disk usage: " ; du -ah

#Current member of users in the system
echo -n "Current number of users in the system: " ; who -u | wc -l

#Current time
echo -n "Current time: " ; date +%T

line "<" 75 ; echo
#-----END-----
