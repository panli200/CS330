#!/usr/local/bin/bash
#author:Li Pan
#file: lab11.sh 
#Backup all the C program files in current directory


#check the backup 
if [ -d "./backup" ]; then
        echo "Backup exists"
else
        read -p "Backup not exists. Enter your command: " var1
        case $var1 in
        [Yy]|[Yy][Ee][Ss])
                echo "Create a backup "
                mkdir backup;;
        [Nn]|[Nn][Oo])
                echo "Backup will not create";;
        *)
                echo "Invalid response";;
        esac
fi

#if backup exists, check all .c files wether 
if [ -d "./backup" ]; then
    for i in  `ls *.c` ; do        
        if ! [ -e ./backup/$i ] ; then
            echo "$i is not in backup. Backup the file."
            cp $i ./backup/
        fi

#check .c files under backup is updating
        cmp -s $i ./backup/${i##*/}
        if [ $? -ne 0 ] ; then
            echo "Update $i under backup."
            cp $i ./backup/
        else
            echo "$i is updated in backup."
        fi
    done
fi