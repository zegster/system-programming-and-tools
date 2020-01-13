#!/bin/bash
##Author:    Duc Ngo
##Course:    CS2750-001
##Name:      contact_one.sh
##Purpose:   Use a HERE document and read a pattern from a user. If a
##           name is not in HERE document, display a message saying that
##-----------------------------------------------------------------

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
USAGE="Usage: $0"

##- - - - - Start - - - - -
line ">" 75

##Check number of parameter
if [[ $# -gt 0 ]]
then
    echo "$0: Too many parameters. Exiting..."
    echo "$USAGE"
    line "<" 75
    echo
    exit 1
fi

##Read input for infinite amount of time, until user exit it with control+c
while :
do
echo "Please enter a pattern (control + c to exit out):"
pattern=""
read pattern

output=""
{ output=$(grep -i "$pattern"); } << HERE  
Agamemnon Uther auther1234@gmail.com 314-111-1111
Arif Nagib anagib3267@gmail.com 636-2980-1000
Chika Cateline ccateline5940@gmail.com 998-327-6297
Good Dog findmeahome404@gmail.com 777-777-7777
Kagan Iona kiona9999@gmail.com 756-461-2471
Kefilwe Saulia ksaulia1111@gmail.com 710-756-2654
Khalida Perseus kperseus2323@gmail.com 483-484-4818
Naoise Vsevolod nvsevolod8989@gmail.com 704-570-7505
Natalija Aditya naditya7777@gmail.com 420-578-0270
Rodrigo Olle rolle1996@gmail.com 263-963-5040
Shonda Peronel speronel1987@gmail.com 445-389-0866
HERE

##Display output if match found. If not, display a message
if [[ -z $output ]]
then
    echo "No match found..."
else
    echo "$output"
fi
echo
done

line "<" 75
echo
##- - - - - End - - - - -
