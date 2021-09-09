#!/bin/bash
for var; do
  case $var in
  '?')
    echo "Скрипт удлиняет файлы с указанным суффиксом до указанной длины путем присоеденения к ним необходимого числа копий некоторого файла"
    echo "Использование: ./Bash_ebash.sh [СУФФ] [ДЛИН] [ФАЙЛ]"
    exit
    ;;
  esac
done
suf=()
len=()
file=()
if [ $# -eq 0 ]; then
  echo "Введите суффикс"
  read suf
  echo "Введите длину"
  read len
  echo "Введите файл"
  read file
elif [ $# -eq 1 ]; then
  suf=$1
  echo "Введите длину"
  read len
  echo "Введите файл"
  read file
elif [ $# -eq 2 ]; then
  suf=$1
  len=$2
  echo "Введите файл"
  read file
elif [ $# -eq 3 ]; then
  suf=$1
  len=$2
  file=$3
else
  echo "Количество параметров превышает норму"
fi
for i in *.$suf;
do
  n=$(stat -c%s "$i")
  while [ $n -lt $len ]; do
    cat $file >> $i
    n=$(stat -c%s "$i")
  done
done