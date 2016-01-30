#!/bin/bash
clear;clear;
EXE=Compiled_Code
pmccabe *cpp *h | egrep  "(^[789]\b|^1[0-9]\b)"
g++ -std=c++11 -g -o $EXE *.h *cpp -Wall
if (( $? )) ;
then
	echo Compilation Failed;
	read -p "Press enter to exit";
else
	chmod 755 $EXE;
	#valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$EXE $1 $2
	./$EXE $1 $2

	read -p "Press enter to exit..."
fi;
