#!/bin/sh
files=`ls *.h *.cpp`
for file in $files
do
    sed "s/HW1/HW2/g" < $file > 'new'.$file
done

files=`ls new.*`
for file in $files
do
    name=`echo $file | sed s/new.//`
    echo $name
    mv $file $name
done


