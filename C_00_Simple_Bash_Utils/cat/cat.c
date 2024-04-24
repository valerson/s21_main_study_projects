#include "cat.h"

// void args_print(int argc, char *argv[])
// {
//     // печать аргументов, переданных в мейн.
//     // 0 - название исполняемого файла, далее аргументы с разделителем пробелом
//     for (int i = 0; i < argc; i++)
//     {
//         printf("%s \n", argv[i]);
//     }
// }

int args_check_and_parsing(int argc, char *argv[])
{
    int flag = 1; // 1-все в порядке
    if (argc != 3 || argv[1][0] != '-' || !strchr("beEnstT", argv[1][1]))
    {
        flag = 0;
    }
    if (!flag)
    {
        if (argc != 3)
            printf("ERROR. Incorrect input of the number of arguments.\n");
        if (argv[1][0] != '-')
            printf("ERROR entering the flag.\n");
        if (!strchr("beEnstT", argv[1][1]))
            printf("ERROR. Unknown flag.\n");
    }
    return flag;
}

void function_flag_b(char *filename)
/*
    flag -b
    нумерация не пустых строк
*/
{
    char c;
    int number_line = 1, i = 0;
    char line[2048] = ""; // максимальная длина строки 2048 байт
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == '\n' || c == EOF)
        {
            line[i] = '\0';
            if (strlen(line))
            {
                // не пустая строка нумеруем и печатаем
                printf("%6.d\t%s\n", number_line, line); // отступ и табуляцию сделал как в фнукци cat
                number_line++;
            }
            else
            {
                // пустая строка только печатаем
                printf("%s\n", line);
            }
            i = 0;
            if (c == EOF)
            {
                break;
            }
        }
        else
        {
            line[i] = c;
            i++;
        }
    }
    fclose(file);
}

void function_flag_E(char *filename)
/*
    flag -E
    аналог cat -e
    печатает перед символом конца строки доллар
*/
{
    char c;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == EOF)
        {
            break;
        }
        if (c == '\n')
        {
            printf("$%c", c);
        }
        else
        {
            printf("%c", c);
        }
    }
    fclose(file);
}

void function_flag_e(char *filename)
/*
    flag -e работает в паре с -v
    аналог cat -ev
    печатает перед символом конца строки доллар
    печатает невидимые символы (по аскии это от 0 до 31)
*/
{
    char c;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == EOF)
        {
            break;
        }

        if (c >= 0 && c <= 31)
        {
            if (c == '\n')
            {
                printf("$%c", c);
            }
            else if (c == '\t' || c == '\0') // так с стандартной cat -ev
            {
                printf("%c", c);
            }
            else if (c == 127) // символ del
            {
                printf("^?");
            }
            else
            {
                printf("^%c", c + 64); // сдвиг на 64
            }
        }
        else
        {
            printf("%c", c);
        }
    }
    fclose(file);
}

void function_flag_n(char *filename)
/*
    flag -n
    нумерация всех строк
*/
{
    char c;
    int number_line = 1, i = 0;
    char line[2048] = ""; // максимальная длина строки 2048 байт
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == '\n' || c == EOF)
        {
            line[i] = '\0';
            printf("%6.d\t%s\n", number_line, line);
            number_line++;
            i = 0;
            if (c == EOF)
            {
                break;
            }
        }
        else
        {
            line[i] = c;
            i++;
        }
    }
    fclose(file);
}

void function_flag_s(char *filename)
/*
    flag -s
    если пустых строк несколько подряд - печатаем только одну
*/
{
    char c;
    int i = 0;
    char line[2048] = ""; // максимальная длина строки 2048 байт
    char temp[2048] = "";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == '\n' || c == EOF)
        {
            line[i] = '\0';

            if (strcmp(line, temp) || strlen(line) != 0)
            {
                // printf("%lu\n", strlen(line));
                printf("%s\n", line);
                strcpy(temp, line);
            }
            i = 0;
            if (c == EOF)
            {
                break;
            }
        }
        else
        {
            line[i] = c;
            i++;
        }
    }
    fclose(file);
}

void function_flag_T(char *filename)
/*
    flag -t
    печатает невидимые табуляции
    аналог cat -t
*/
{
    char c;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == EOF)
        {
            break;
        }

        if (c > 0 && c <= 31)
        {
            if (c == '\0' || c == '\n')
            {
                printf("%c", c);
            }
            else if (c == '\t') // символ del
            {
                printf("^%c", c + 64); // отдельно отразил табуляцию
            }
            else
            {
                printf("^%c", c + 64); // сдвиг на 64
            }
        }
        if (c == 127) // символ del
        {
            printf("^?");
        }
        else if (c == 0) // символ NULL
        {
            printf("^%c", c + 64); // отдельно отразил табуляцию
        }
        else
        {
            printf("%c", c);
        }
    }
    fclose(file);
}

void function_flag_t(char *filename)
/*
    flag -tv
    печатает невидимые символы с табуляцией (по аскии это от 0 до 31)
    аналог cat -tv
*/
{
    char c;
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("ERROR. File not found.");
        return;
    }
    while (1)
    {
        c = getc(file);
        if (c == EOF)
        {
            break;
        }

        if (c > 0 && c <= 31)
        {
            if (c == '\0' || c == '\n')
            {
                printf("%c", c);
            }
            else
            {
                printf("^%c", c + 64); // сдвиг на 64
            }
        }
        else
        {
            if (c == 127) // символ del
            {
                printf("^?");
            }
            else if (c == 0) // символ NULL
            {
                printf("^%c", c + 64); // отдельно отразил табуляцию
            }
            else
            {
                printf("%c", c);
            }
        }
    }
    fclose(file);
}

void cat_function(char flag, char *filename)
{
    switch (flag)
    {
    case 'b':
    {
        function_flag_b(filename);
        break;
    }
    case 'E':
    {
        function_flag_E(filename);
        break;
    }
    case 'e':
    {
        function_flag_e(filename);
        break;
    }
    case 'n':
    {
        function_flag_n(filename);
        break;
    }
    case 's':
    {
        function_flag_s(filename);
        break;
    }
    case 'T':
    {
        function_flag_T(filename);
        break;
    }
    case 't':
    {
        function_flag_t(filename);
        break;
    }
    default:
    {
        printf("ERROR. Unknown flag.\n");
        break;
    }
    }
}
