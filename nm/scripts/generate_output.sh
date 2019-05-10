#!/bin/bash

DEF="\033[0m"
YELLOW='\033[0;33m'
GREEN='\033[0;32m'
RED='\033[0;31m'

DIR="../tests/input"
PROG="nm"

OK=0
TOTAL=0

# generate_cor "file"
function generate_cor () {

	$PROG $1 1> $1.output 2> /dev/null
	if [[ "$?" == "0" ]]; then
		OK=$((OK+1))
		printf "${GREEN}OK${DEF}\n"
	else
		echo $1 >> failed_list.txt
		printf "${RED}KO${DEF}\n"
	fi
}

# run_tests "path"
function run_tests () {

	for entry in `find $1 -type f`
	do	
		TOTAL=$((TOTAL+1))
		echo -n "compiling" $entry ": "
		generate_cor $entry
	done

}

function main() {

	run_tests $DIR

	echo "files generated: " $OK
	echo "---------------"
	echo "TOTAL:" $TOTAL

}
main "$@"
