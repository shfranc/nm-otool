#!/usr/bin/bash

GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
DEF="\033[0m"

nm_bin=$PATH_FT_NM

if [ -z $PATH_FT_NM ] ; then
    echo "usage: sh test_nm.sh dir [...]"
    echo "  Export PATH_FT_NM with path of your binary."
    exit 1
fi

printf "\n%.-78s $YELLOW%s   %s$DEF\n" "" "OUTPUT" "RETURN"

for arg in "$@"
do

    echo ""
    if [[ -d "$arg" ]]; then
        # echo "FOLDER : $arg"
        loop=$arg/*
    elif [[ -f "$arg" ]]; then
        loop=$arg
    fi
    for file in $loop; do

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
