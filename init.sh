#!/bin/bash

# Check if there are exactly 2 command line arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 year day"
    exit 1
fi


# Borrowed from https://github.com/sergiolepore/ChristBASHTree/blob/master/tree-EN.sh
printChristmasTree() {

    trap "tput reset; tput cnorm; exit" 2
    clear
    tput civis
    lin=2
    col=$(($(tput cols) / 2))
    c=$((col-1))
    est=$((c-2))
    color=0
    tput setaf 2; tput bold

    # Tree
    for ((i=1; i<20; i+=2))
    {
        tput cup $lin $col
        for ((j=1; j<=i; j++))
        {
            printf "\n"
        }
        let lin++
        let col--
    }

    tput sgr0; tput setaf 3

    # Trunk
    for ((i=1; i<=2; i++))
    {
        tput cup $((lin++)) $c
        echo 'mWm'
    }
    new_year=$(date +'%Y')
    let new_year++
    tput setaf 1; tput bold
    tput cup $lin $((c - 6)); echo MERRY CHRISTMAS
    tput cup $((lin + 1)) $((c - 10)); echo And lots of CODE in $new_year
    let c++
    k=1

    cnt=0

    # Lights and decorations
    while true; do
        cnt=$((cnt+1))
        if [ $cnt -ge 10 ] ; then
            return 1
        fi
        for ((i=1; i<=35; i++)) {
            # Turn off the lights
            [ $k -gt 1 ] && {
                tput setaf 2; tput bold
                tput cup ${line[$[k-1]$i]} ${column[$[k-1]$i]}; echo \*
                unset line[$[k-1]$i]; unset column[$[k-1]$i]  # Array cleanup
            }

            li=$((RANDOM % 9 + 3))
            start=$((c-li+2))
            co=$((RANDOM % (li-2) * 2 + 1 + start))
            tput setaf $color; tput bold   # Switch colors
            tput cup $li $co
            echo o
            line[$k$i]=$li
            column[$k$i]=$co
            color=$(((color+1)%8))
            # Flashing text
            sh=1
            for l in C O D E
            do
                tput cup $((lin+1)) $((c+sh))
                echo $l
                let sh++
                sleep 0.01
            done
        }
        k=$((k % 2 + 1))
    done
}

# Extract the folder names from command line arguments
parent_folder="$1"
child_folder="day-$2"

if ! [[ "$parent_folder" =~ ^[0-9]+$ && "$parent_folder" -ge 2015 && "$parent_folder" -le $(date +%Y) ]]; then
    echo "Error: $parent_folder must be a number between 2015 and $(date +%Y)"
    exit 1
fi

# Check if folder2 is a number between 1 and 25
if ! [[ "$2" =~ ^[0-9]+$ && "$2" -ge 1 && "$2" -le 25 ]]; then
    echo "Error: $2 must be a number between 1 and 25"
    exit 1
fi

# Check if the parent folder exists
if [ ! -d "$parent_folder" ]; then
    # If it doesn't exist, create it along with the child folder
    mkdir -p "$parent_folder/$child_folder"
    echo "Created folders: $parent_folder/$child_folder"
else
    # If the parent folder exists, check if the child folder exists
    if [ ! -d "$parent_folder/$child_folder" ]; then
        # If the child folder doesn't exist, create it
        mkdir "$parent_folder/$child_folder"
        echo "Created folder: $parent_folder/$child_folder"
    else
        echo "Child folder already exists: $parent_folder/$child_folder"
    fi
fi

touch "$parent_folder/$child_folder/solution.cpp"
touch "$parent_folder/$child_folder/test1.txt"
touch "$parent_folder/$child_folder/test2.txt"
curl --cookie "session=$AOC_COOKIE" https://adventofcode.com/$1/day/$2/input > "$parent_folder/$child_folder/input.txt"

# Check if folder2 is 25 and print Merry Christmas with animation
if [ "$2" -eq 25 ]; then
    printChristmasTree
fi