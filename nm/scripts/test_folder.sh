#!/bin/bash

FT_NM="../ft_nm"

for file in $(ls -1 $1)
do
	$FT_NM $1/$file > tmp1 2> /dev/null
	res1=$(echo $?)
	nm $1/$file > tmp2 2> /dev/null
	res2=$(echo $?)
	if [ $res1 -eq 0 ] && [ $res2 -eq 0 ] ; then
		DIFF=$(diff tmp1 tmp2)
		if [ -z "$DIFF" ] ; then
			echo $file "OK"
		else
			echo $file "KO"
		fi
	rm -rf tmp1 tmp2
	else
		echo $file "err"
	fi
done
