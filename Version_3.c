#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

const int AMOUNT_OF_STRINGS = 14;
const int LENGTH_OF_STRINGS = 120;

enum All_Exit_Codes
{
    EXIT_CODE_ERROR = -1,
    PROGRAMM_IS_IN_PROGRESS = 0,
    SUCCESFUL_EXIT = 1,
};



struct All_Needed_For_Onegin
{
    char Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS];
    char **Adresses;
    int Amount_Of_Strings;
    int Lengths_Of_Strings[AMOUNT_OF_STRINGS];
};



void Reader(char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS]);

void Bubble_Sort_Of_Strings(char **Starting_Adresses);

void Swapping_Places_Old(char *String_1, char *String_2);

void Filling_Each_Adress(char **Starting_Adresses, int *Lengths_Of_Strings,
                int Amount_Of_Strings, char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS]);

void Swapping_Places(char **Starting_Adresses, int Adress_Of_Sting_1, int Adress_Of_Sting_2);

off_t Fsize(const char *filename);

int main()
{
    struct stat Stat_Buffer = {};
    stat("Text_Of_Onegin.txt", &Stat_Buffer);
    printf ("\nBad_Method:\n\v%d\n\v", Stat_Buffer.st_size);

    int Size_Of_File = Fsize("Text_Of_Onegin.txt");
    printf ("Good method:\n\v%d\n\v", Size_Of_File);

    struct All_Needed_For_Onegin Onegin = {0, 0, 0, 0};


    Onegin.Amount_Of_Strings = AMOUNT_OF_STRINGS;


    for (int i = 0; i < Onegin.Amount_Of_Strings; i++)
        Onegin.Lengths_Of_Strings[i] = LENGTH_OF_STRINGS;

    Onegin.Adresses = (char **)calloc(Onegin.Amount_Of_Strings, sizeof(char*));

    Onegin.Adresses[0] = &(Onegin.Text[0][0]);

    Reader(Onegin.Text);

    printf("\n          The text was:\n\v");

    for (int i = 0; i < Onegin.Amount_Of_Strings; i++)
        printf("%s", Onegin.Text[i]);
    printf("\n");

    Filling_Each_Adress(Onegin.Adresses, Onegin.Lengths_Of_Strings, Onegin.Amount_Of_Strings, Onegin.Text);

    Bubble_Sort_Of_Strings(Onegin.Adresses);

    printf("\n          The text became:\n\v");



    for (char i = 0; i < Onegin.Amount_Of_Strings; i++)
    {
        //t += 1;
        for (char j = 0; j < Onegin.Lengths_Of_Strings[0]; j++)
            printf("%c",Onegin.Adresses[i][j]); // + t
    }
}



void Reader(char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS])
{
    FILE *Opened_File = fopen("Text_Of_Onegin.txt", "r");

    if (Opened_File != NULL)
    {
        char Input_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS] = {};

        for (int i = 0; i < AMOUNT_OF_STRINGS; i++)
        {
            fgets(Input_Text[i], LENGTH_OF_STRINGS, Opened_File);

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
                    tolower(Starting_Adresses[i][j]) - tolower(Starting_Adresses[i + 1][j]) > 0
                    )
                {
                    Swapping_Places(Starting_Adresses, i, i + 1);
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



void Swapping_Places(char **Starting_Adresses, int Adress_Of_Sting_1, int Adress_Of_Sting_2)
{
    char *Temp = Starting_Adresses[Adress_Of_Sting_1];

    Starting_Adresses[Adress_Of_Sting_1] = Starting_Adresses[Adress_Of_Sting_2];
    Starting_Adresses[Adress_Of_Sting_2] = Temp;
}



void Filling_Each_Adress(char **Starting_Adresses, int *Lengths_Of_Strings,
        int Amount_Of_Strings, char Output_Text[AMOUNT_OF_STRINGS][LENGTH_OF_STRINGS])
{
    for (int i = 0; i < Amount_Of_Strings; i++)
        Starting_Adresses[i] = Output_Text[i];
}



off_t Fsize(const char *filename)
{
    struct stat st;
    if (stat(filename, &st) == 0)
        return st.st_size;
    return -1;
}


