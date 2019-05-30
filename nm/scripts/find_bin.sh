#!/bin/bash

FT_NM="../ft_nm"

for file in $(ls -1 $1)
do
	printf "$1/$file : "
	$FT_NM $1/$file 2> /dev/null | head -n 1
done
