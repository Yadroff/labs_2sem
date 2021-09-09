#!/bin/bash
for var; do
  case $var in
  '?')
    echo "Скрипт интерпретирует МТ в 4"
    echo "Использование: ./f1.sh [ФАЙЛ1] [ФАЙЛ2]"
    echo -e "В первой строке ФАЙЛа1 должна быть записана начальная ситуация ленты.\nКонец исходных данных должен заканчиваться пробелом не должен быть загрязнен прочими символами"
    echo "В ФАЙЛе2 должна быть записана программа без комментариев"
    exit
    ;;
  esac
done
ARGS=2
if [ $# -lt $ARGS ]; then
  if [ $# -eq 0 ]; then
    echo "Введите 1-й параметра"
    read test
    echo "Введите 2-й параметр"
    read prog
  else
    echo "Введите параметр"
    read prog
  fi
elif [ $# -gt $ARGS ]; then
  echo "Количество параметров превышает норму"
  exit
else
  test=$1
  prog=$2
fi
if [ -r $test ] && [ -r $prog ]; then
  echo "Параметры введены верно"
else
  echo "Параметры введены неверно"
  exit
fi
turing=()
str=$(head -n 1 $test)
for ((i = 0; i < ${#str}; i++)); do
  turing[i]=$(echo "${str:$i:1}")
done
pos=${#turing[*]}
pos=$(( pos - 1))
a=' '
q=0
last_a=' '
last_q=0
while (true); do
  n=$(grep -o "^$q,$a," $prog | wc -l)
  if [ $n -gt 1 ]; then
    echo "Для конфигурации q = $q, a = $a найдено больше 1 совпадения"
    exit
  elif [ 1 -gt $n ]; then
    echo "Для конфигурации q = $q, a = ${turing[$pos]} не определена команда"
    exit
  else
    str=$(grep "^$q,$a," $prog)
    echo $str
    last_a=$a
    last_q=$q
    a=$(echo "$str" | cut -d ',' -f 3)
    q=$(echo "$str" | cut -d ',' -f 4)
    if [[ "$a" = "l" ]]; then
      pos=$(($pos - 1))
      if [ 0 -gt $pos ]; then
        echo "Программа вышла за левую границу ленты"
        exit
      fi
      a=${turing[$pos]}
    elif [[ "$a" = "r" ]]; then
      pos=$(( $pos+1 ))
      if [ $pos -gt ${#turing[*]} ]; then
        turing[pos]=' '
      fi
      a=${turing[$pos]}
    else
      turing[pos]=$a
    fi
    echo -n -e "\t\t"
    for ((i = 0; i <= $pos; i++)); do
        echo -n ${turing[$i]}
      done
      echo ''
    if [[ "$last_q" = "$q" ]] && [[ "$last_a" = "$a" ]]; then
      echo "Программа успешно завершилась"
      for ((i = 0; i <= $pos; i++)); do
        echo -n ${turing[$i]}
      done
      echo ''
      exit
    fi
  fi
done

