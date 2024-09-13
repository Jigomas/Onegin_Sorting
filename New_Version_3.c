#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

enum All_Exit_Codes
{
    EXIT_CODE_ERROR = -1,
    PROGRAMM_IS_IN_PROGRESS = 0,
    SUCCESFUL_EXIT = 1,
};



struct All_Needed_For_Onegin
{
    char *Text;
    char **Addresses;
    int Amount_Of_Strings;
    int *Lengths_Of_Strings;
};



void Reader(char **Output_Text, int Size_Of_File, int *Amount_Of_Strings, char **Addresses);

void Bubble_Sort_Of_Strings(char **Starting_Addresses, int Amount_Of_Strings);

void Swapping_Places_Old(char *String_1, char *String_2);

void Swapping_Places(char **Starting_Addresses, int Address_Of_Sting_1, int Address_Of_Sting_2);


off_t Fsize(const char *filename);

int main()
{
    struct stat Stat_Buffer = {};
    stat("Text_Of_Onegin.txt", &Stat_Buffer);
    printf ("\nBad_Method:\n\v%ld\n\v", Stat_Buffer.st_size);

    int Size_Of_File = Fsize("Text_Of_Onegin.txt");
    printf ("Good method:\n\v%d\n\v", Size_Of_File);



    struct All_Needed_For_Onegin Onegin = {0, 0, 0, 0};

    Onegin.Text = (char *)calloc(Size_Of_File, sizeof(char*));

    Onegin.Amount_Of_Strings = 0;


    Onegin.Addresses = (char **)calloc(Size_Of_File, sizeof(char*));
    Onegin.Addresses[0] = &(Onegin.Text[0]);


    Reader(&Onegin.Text, Size_Of_File, &Onegin.Amount_Of_Strings, Onegin.Addresses);

    printf("\n          The text was:\n\v");

    for (int i = 0; i < Size_Of_File - Onegin.Amount_Of_Strings; i++)
        printf("%c", Onegin.Text[i]);




    printf("\nAmount Of Strings: %d\n", Onegin.Amount_Of_Strings);


    Bubble_Sort_Of_Strings(Onegin.Addresses, Onegin.Amount_Of_Strings);

    printf("\n          The text became:\n\v");



    for (int i = 0; i < Onegin.Amount_Of_Strings; i++)
    {
        int j = 0;
        while (Onegin.Addresses[i][j] != '\n')
        {
            printf("%c", Onegin.Addresses[i][j]);
            j++;
        }
        printf("\n");
    }

    free (Onegin.Text);
    free (Onegin.Addresses);
}



void Reader(char **Output_Text, int Size_Of_File, int *Amount_Of_Strings, char ** Addresses)
{
    char Temp_Char = 0;
    FILE *Opened_File = fopen("Text_Of_Onegin.txt","r");

    int Amount_Of_Words_In_Last_String = 0;
    if (Opened_File != NULL)
        for (int i = 0; i < (Size_Of_File - *Amount_Of_Strings)  && Temp_Char != EOF; i++)
        {
            Amount_Of_Words_In_Last_String ++;
            Temp_Char = getc(Opened_File);
            (*Output_Text)[i] = Temp_Char;
            if (Temp_Char == '\n')
            {
                *Amount_Of_Strings += 1;
                Addresses[*Amount_Of_Strings] = Addresses[*Amount_Of_Strings - 1] + Amount_Of_Words_In_Last_String;
                printf("Length_Of_String_%d = %d\n", *Amount_Of_Strings, Amount_Of_Words_In_Last_String);
                Amount_Of_Words_In_Last_String = 0;
            }
        }

    fclose(Opened_File);
}



void Bubble_Sort_Of_Strings(char **Starting_Addresses, int Amount_Of_strings)
{
    for (int Start_Of_Sorting = 0; Start_Of_Sorting < Amount_Of_strings; Start_Of_Sorting++)
    {
        for (int i = 0; i < Amount_Of_strings - 1; i++)     //ВЫЧИТАТЬ Start_Of_Sorting
        {
            int j = 0;
            while (j < (Starting_Addresses[i + 1] - Starting_Addresses[i]) &&
                 Starting_Addresses[i][j] != 0)  // Разбить J  на две разных переменных, чтобы скипать не буквы
            {
                if  (
                    tolower(Starting_Addresses[i][j]) - tolower(Starting_Addresses[i + 1][j]) > 0
                    )
                {
                    Swapping_Places(Starting_Addresses, i, i + 1);

                    break;
                }

                else if (
                    tolower(Starting_Addresses[i][j]) -
                    tolower(Starting_Addresses[i + 1][j]) == 0
                        )
                {
                    j += 1;
                }

                else
                {
                    break;
                }

            }
        }
    }
}



void Swapping_Places(char **Starting_Addresses, int Address_Of_Sting_1, int Address_Of_Sting_2)
{
    char *Temp = Starting_Addresses[Address_Of_Sting_1];

    Starting_Addresses[Address_Of_Sting_1] = Starting_Addresses[Address_Of_Sting_2];
    Starting_Addresses[Address_Of_Sting_2] = Temp;
}



off_t Fsize(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_size;
    return -1;
}


