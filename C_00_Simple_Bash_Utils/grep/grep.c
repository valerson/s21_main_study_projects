#include <stdio.h>
#include <string.h>

void args_parsing(int argc, char *argv[], char *flag[], char *options[], char *file_name[]);
void function_flag_e(char *file_name[], char *options[]);

int main(int argc, char *argv[])
{
    char *flag[255];
    char *options[255];
    char *file_name[1000]; // сделал не более 1000 файлов, можно замолочить и реализовать любое кол-во. но не стал,

    args_parsing(argc, argv, flag, options, file_name);
    function_flag_e(file_name, options);
    return 0;
}

void args_parsing(int argc, char *argv[], char *flag[], char *options[], char *file_name[])
{
    int t = 0, f = 0;
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            flag[0] = argv[i];
            options[t] = argv[i + 1];
            i++;
            t++;
        }
        else
        {
            file_name[f] = argv[i];
            f++;
            // printf("%s \n", argv[i]);
        }
    }

    // printf("FLAGS: \n");
    // for (int i = 0; i < t; i++)
    // {
    //     printf("%s\n", flag[i]);
    // }

    // printf("THEME: \n");
    // for (int i = 0; i < t; i++)
    // {
    //     printf("%s\n", theme[i]);
    // }

    // printf("FILE_NAMES: \n");
    // for (int i = 0; i < f; i++)
    // {
    //     printf("%s\n", file_name[i]);
    // }
}

void function_flag_e(char *file_name[], char *options[])
{
    printf("%s\n", file_name[0]);
    printf("%s\n", options[0]);
    FILE *file = fopen(file_name[0], "r");
    if (file == NULL)
    {
        perror("ERROR. File not found.");
        return;
    }
    char c;
    char temp[2048]; // максимальная длина строки 2048 байт

    while ((c = getc(file)) != EOF)
    {
        int i = 0;
        while (c != '\n' && c != '\0') // весь абзац бахаем в масссив темп
        {
            temp[i] = c;
            c = getc(file);
            // printf("%c-%d ", c, c);
            if (c == 10) // перенос строки LF в ASCII
            {
                temp[i + 1] = '\0';
            }
            else
            {
                i++;
            }

            if (c == EOF)
            {
                temp[i] = '\0'; //-1 потому что и уже увеличенное в елсе
                break;
            }
        }
        if (c != EOF)
        {

            printf("%s%c", temp, c);
        }
        else
        {
            printf("%s", temp);
        }
        i = 0;
        memset(temp, 0, sizeof(temp)); // чистим массив temp
    }

    fclose(file);
}