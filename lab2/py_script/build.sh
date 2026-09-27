#!/bin/bash
set -e

# Очистка предыдущих сборок
rm -f lab2_O*

echo "Начинается компиляция..."

gcc -Wall -Wextra -Werror -O0 lab2.c -o lab2_O0
gcc -Wall -Wextra -Werror -O1 lab2.c -o lab2_O1
gcc -Wall -Wextra -Werror -O2 lab2.c -o lab2_O2
gcc -Wall -Wextra -Werror -O3 lab2.c -o lab2_O3
gcc -Wall -Wextra -Werror -Os lab2.c -o lab2_Os
gcc -Wall -Wextra -Werror -Ofast lab2.c -o lab2_Ofast
gcc -Wall -Wextra -Werror -Og lab2.c -o lab2_Og

echo "Компиляция успешно завершена. Создано 7 исполняемых файлов."