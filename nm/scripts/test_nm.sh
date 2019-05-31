#!/usr/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
DEF="\033[0m"

nm_bin="/Users/sfranc/Documents/42/nm-otool/nm/ft_nm"


for folder in "$@"
do
    printf "\n%.-78s $YELLOW%s   %s$DEF\n" "" "OUTPUT" "RETURN"

    echo "FOLDER : $folder"
    for file in $folder/*; do

        # CHECK SEGFAULT
        $("$nm_bin" $file > /dev/null 2>&1)
        if [[ "$?" -eq "139" ]]; then
            printf "%-80s $RED%s$DEF\n" "$file" "SEGFAULT"
            continue
        fi

        # CHECK OUTPUT
        my_nm="$("$nm_bin" $file 2>&1)"
        real_nm="$(nm $file 2>&1)"
        if [[ "$real_nm" == "$my_nm" ]]; then
            printf "%-80s $GREEN%s$DEF" "$file" "OK"
        else
            printf "%-80s $RED%s$DEF" "$file" "KO"
        fi

        # CHECK RETURN CODE
        $("$nm_bin" $file > /dev/null 2>&1)
        ret_my_nm="$?"
        $(nm $file > /dev/null 2>&1)
        ret_real_nm="$?"
        if [[ "$ret_my_nm" == "$ret_real_nm" ]]; then
            printf "       $GREEN%s$DEF\n" "OK"
        else
            printf "       $RED%s$DEF\n" "KO"
        fi

    done
done
