#!/bin/bash
clear;clear;
pmccabe *cpp *h | egrep  "(^[789]\b|^1[0-9]\b)"
EXE=Lab3
make -j6
if (( $? )) ;
then
	echo Compilation Failed;
	read -p "Press enter to exit";
else
	chmod 755 $EXE;
	#valgrind --tool=memcheck --leak-check=yes --track-origins=yes ./$EXE $1 $2
	./$EXE $1 $2
	diff $2 $3
	#read -p "Press enter to exit..."
fi;
