#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const int AMOUNT_OF_STRINGS = 15;
const int LENGTH_OF_STRINGS = 120;

enum All_Exit_Codes
{
    EXIT_CODE_ERROR = -1,
    PROGRAMM_IS_IN_PROGRESS = 0,
    SUCCESFUL_EXIT = 1,
};

void Reader(char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS]);

void Sorting_Of_Strings(char Input_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS]);

void Swapping_Places(char *String_1, char *String_2);



int main()
{
    char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS] = {};
    Reader(Output_Text);


    for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        printf("%s", Output_Text[i]);

    printf("\n");

    Sorting_Of_Strings(Output_Text);


    for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        printf("%s", Output_Text[i]);
}



void Reader(char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS])
{
    char *Origin = 0;
    FILE *Opened_File = fopen("Text_Of_Onegin.txt", "r");

    if (Opened_File != NULL)
    {
        char Input_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS] = {};

        for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        {
            fgets(Input_Text[i], LENGTH_OF_STRINGS, Opened_File);

            //Output_Text[i] = Input_Text[i];

            int j = 0;

            for (j = 0; j < LENGTH_OF_STRINGS && Input_Text[i][j] != '\n'; j++)
                Output_Text[i][j] = Input_Text[i][j];
            Output_Text[i][j] = '\n';

        }

    }
    fclose(Opened_File);

}



void Sorting_Of_Strings(char Input_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS])
{
    int j = 0;

    for (int Start_Of_Sorting = 0; Start_Of_Sorting < AMOUNT_OF_STRINGS; Start_Of_Sorting++)
    {
        for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        //ВЫЧИТАТЬ Start_Of_Sorting
        {
            j = 0;
            while (j < LENGTH_OF_STRINGS && Input_Text[i][j] != 0)
            {
                // Разбить J  на две разных переменных, чтобы скипать не буквы
                if (tolower(Input_Text[i][j]) - tolower(Input_Text[i + 1][j]) > 0)
                {
                    Swapping_Places(Input_Text[i], Input_Text[i + 1]);
                    break;
                }

                else if (Input_Text[i][j] - Input_Text[i + 1][j] == 0)
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



void Swapping_Places(char *String_1, char *String_2)
{
    for (int i = 0; i < LENGTH_OF_STRINGS; i++)
    {
        char Temp_Symbol = String_1[i];

        String_1[i] = String_2[i];
        String_2[i] = Temp_Symbol;
    }
}
