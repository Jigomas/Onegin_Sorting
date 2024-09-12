#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

const int AMOUNT_OF_STRINGS = 14;
const int LENGTH_OF_STRINGS = 120;

enum All_Exit_Codes
{
    EXIT_CODE_ERROR = -1,
    PROGRAMM_IS_IN_PROGRESS = 0,
    SUCCESFUL_EXIT = 1,
};

void Reader(char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS]);

void Bubble_Sort_Of_Strings(char **Starting_Adresses);

void Swapping_Places_Old(char *String_1, char *String_2);

void Filling_Each_Adress(char **Starting_Adresses, int *Lengths_Of_Strings, int Amount_Of_Strings, char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS]);

void Swapping_Places(char **Starting_Adresses, int Adress_Of_Sting_1, int Adress_Of_Sting_2);



int main()
{
    char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS] = {};
    Reader(Output_Text);

    printf("The text was:\n");
    for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        printf("%s", Output_Text[i]);
    printf("\n");



    int Amount_Of_Strings = AMOUNT_OF_STRINGS;
    int Lengths_Of_Strings[AMOUNT_OF_STRINGS] = {};

    for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        Lengths_Of_Strings[i] = LENGTH_OF_STRINGS;

    char **Starting_Adresses = 0;
    Starting_Adresses = (char **)calloc(Amount_Of_Strings, sizeof(char*));

    Starting_Adresses[0] = &(Output_Text[0][0]);

    Filling_Each_Adress(Starting_Adresses, Lengths_Of_Strings, Amount_Of_Strings, Output_Text);



    char Char_Lengths_Of_Strings = LENGTH_OF_STRINGS;
    //int t = -1;

    for (char i = 0; i < AMOUNT_OF_STRINGS; i++)
    {
        //t += 1;
        for (char j = 0; j < LENGTH_OF_STRINGS; j++)

        printf("%c", *(*(Starting_Adresses) + i * Char_Lengths_Of_Strings + j)); // + t
    }



    Bubble_Sort_Of_Strings(Starting_Adresses);

    printf("\nThe text became:\n");



    for (char i = 0; i < AMOUNT_OF_STRINGS; i++)
    {
        //t += 1;
        for (char j = 0; j < LENGTH_OF_STRINGS; j++)
            printf("%c",Starting_Adresses[i][j]); // + t
    }
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



void Bubble_Sort_Of_Strings(char **Starting_Adresses)
{
    char Char_Lengths_Of_Strings = LENGTH_OF_STRINGS;   //it will be a length of string

    for (int Start_Of_Sorting = 0; Start_Of_Sorting < AMOUNT_OF_STRINGS; Start_Of_Sorting++)
    {
        for (int i = 0; i < AMOUNT_OF_STRINGS - 1; i++)     //ВЫЧИТАТЬ Start_Of_Sorting
        {
            int j = 0;
            while (j < LENGTH_OF_STRINGS &&
                 Starting_Adresses[i][j] != 0)  // Разбить J  на две разных переменных, чтобы скипать не буквы
            {
                if  (
                    tolower(Starting_Adresses[i][j]) -
                    tolower(Starting_Adresses[i + 1][j]) > 0
                    )
                {
                    printf("%d\n", Starting_Adresses[i]);
                    printf("%d\n", Starting_Adresses[i + 1]);

                    Swapping_Places(Starting_Adresses, i, i + 1);

                    printf("%d\n", Starting_Adresses[i]);
                    printf("%d\n", Starting_Adresses[i + 1]);
                    break;
                }

                else if (
                    tolower(Starting_Adresses[i][j]) -
                    tolower(Starting_Adresses[i + 1][j]) == 0
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

//1380

void Swapping_Places(char **Starting_Adresses, int Adress_Of_Sting_1, int Adress_Of_Sting_2)
{
    char *Temp = Starting_Adresses[Adress_Of_Sting_1];

    Starting_Adresses[Adress_Of_Sting_1] = Starting_Adresses[Adress_Of_Sting_2];
    Starting_Adresses[Adress_Of_Sting_2] = Temp;
}



void Filling_Each_Adress(char **Starting_Adresses, int *Lengths_Of_Strings, int Amount_Of_Strings, char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS])
{
    for (int i = 0; i < Amount_Of_Strings; i++)
        Starting_Adresses[i] = Output_Text[i];
}

