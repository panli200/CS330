#!/bin/bash


FILES="$@"
for i in  $FILES ; do
	if [ ${i##*.} != c ] ; then
		echo "$i is not a .c program"
		continue
	else
		echo "$i is a .c program"
	fi

	echo "... checking if file ~/backup/$i is in backup"

	if ! [ -r ~/backup/${i##*/} ] ; then
		echo "... ${i##*/} not in backup. Skipping."
		continue
	fi

	cmp -s $i ~/backup/${i##*/}
	if [ $? -ne 0 ] ; then
		echo "... making new backup of $i"
		cp $i ~/backup/${i##*/}
	else
		echo "... local copy identical to backup. Not cp\'ed"
	fi
	echo 
done