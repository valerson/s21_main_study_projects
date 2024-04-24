/*
1. бахай make
2. используй имя исп файла s21_cat с флагом (-b -e -E -n -s -t -T)и именем файла. файл тест 1 больше для строк, файл 2 - вся аскии табл символов.
3. в рокете овечаю более-менее, если что - телега @ValeriySomov
*/

#include "cat.h"

int main(int argc, char *argv[])
{
    // args_print(argc, argv);
    if (args_check_and_parsing(argc, argv))
    {
        char *file_name = argv[2];
        char flag = argv[1][1];
        cat_function(flag, file_name);
    }
    return 0;
}
