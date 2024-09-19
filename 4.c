#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>



enum All_Exit_Codes
{
    EXIT_CODE_ERROR = -1,
    PROGRAMM_IS_IN_PROGRESS = 0,
    SUCCESFUL_EXIT = 1,
};



struct Must_Needed_For_Text
{
    char *Text;
    char **Addresses;
    int Amount_Of_Strings;
    int *Lengths_Of_Strings;
};



void Reader(char **Output_Text, int Size_Of_File, int *Amount_Of_Strings, char **Addresses);

void Buble_Sorting(void *Starting_Addresses, int Amount_Of_Strings,
                                            int (*Compare_Func)(void *, void *));

int Compare_Func (void *First_String, void *Second_String);

void Quick_Sort(void *Starting_Addresses, int Left_Ad, int Right_Ad,
                                            int (*Compare_Func)(void *, void *));

void Swapping_Places(void *Address_Of_Sting_1, void *Address_Of_Sting_2,  int Size_Of_Cymbol);

off_t Fsize(const char *filename);



int main()
{
    // This will get a size of file
    struct stat Stat_Buffer = {};
    stat("Text_Of_Onegin.txt", &Stat_Buffer);
    printf ("\nBad_Method:\n\v%ld\n\v", Stat_Buffer.st_size);

    int Size_Of_File = Fsize("Text_Of_Onegin.txt");
    printf ("Good method:\n\v%d\n\v", Size_Of_File);


    // This is a start of working with text
    struct Must_Needed_For_Text Onegin = {0, 0, 0, 0};

    Onegin.Text = (char *)calloc(Size_Of_File, sizeof(char));
    Onegin.Amount_Of_Strings = 0;
    Onegin.Addresses = (char **)calloc(Size_Of_File, sizeof(char*));
    Onegin.Addresses[0] = &(Onegin.Text[0]);



    Reader(&Onegin.Text, Size_Of_File, &Onegin.Amount_Of_Strings, Onegin.Addresses);


    // This is going to write text b4 and after sorting
    printf("\nAmount Of Strings: %d\n", Onegin.Amount_Of_Strings);

    printf("\n\t\t\tThe text was:\n\v");
    for (int i = 0; i < Size_Of_File - Onegin.Amount_Of_Strings; i++)
        printf("%c", Onegin.Text[i]);


    Buble_Sorting( Onegin.Addresses, Onegin.Amount_Of_Strings, Compare_Func);


    printf("\n\t\t\tThe text became:\n\v");
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


/************

void Quick_Sort(void *Starting_Addresses, int Left_Ad, int Right_Ad,
                                            int (*Compare_Func)(void *, void *))
{

    //int a = (*Compare_Func)((char *)Starting_Addresses + 0 * sizeof(char*), (char *)Starting_Addresses + 1 * sizeof(char*) );
    //printf("Compare_Func %d", a);

    Swapping_Places (Starting_Addresses, 0, 2);
    int i = 0, Last_Ad = 0;
    if (Left_Ad >= Right_Ad)
        return;

    Swapping_Places (Starting_Addresses, Left_Ad, (Left_Ad + Right_Ad )/2);

    Last_Ad = Left_Ad;



    //        for (int i = 0; i < 14; i++)
    //        {
    //            int j = 0;
    //            while ( *((char *)Starting_Addresses + (i*14 + j) * sizeof(char*)) != '\n')
    //            {
    //                printf("%c", (char *)Starting_Addresses + (i*14 + j) * sizeof(char*));
    //                j++;
    //            }
    //            printf("\n");
    }


    for (i = Left_Ad + 1; i <= Right_Ad; i++)

        if ( (*Compare_Func)(  ((char *)Starting_Addresses + i * sizeof(char*)),  ((char *)Starting_Addresses + Left_Ad * sizeof(char*))  ) < 0)
            Swapping_Places (Starting_Addresses, ++Last_Ad, i);

    Swapping_Places (Starting_Addresses, Left_Ad, Last_Ad);
    Quick_Sort(Starting_Addresses, Left_Ad, Last_Ad - 1, Compare_Func);
    Quick_Sort(Starting_Addresses, Left_Ad, Right_Ad, Compare_Func);
}

***********/



int Compare_Func (void *First_String, void *Second_String)  // This func is comparing symbols
{
    int j = 0;

    while ( *((char *)First_String + j * sizeof(char)) != '\n' &&   *((char *)Second_String + j * sizeof(char)) != '\n')
        {
                //printf ("%d\n", First_String);
                //printf ("%d\n", *((char *)First_String + j * sizeof(char*)));
            if  (
                tolower(*((char *)First_String + j * sizeof(char))) -
                tolower(*((char *)Second_String + (j + 1) * sizeof(char))) > 0
                )
            {
                return 1;
            }
            else if
                (
                tolower(*((char *)First_String + j * sizeof(char))) -
                tolower(*((char *)Second_String + (j + 1) * sizeof(char))) == 0
                )
            {
                //printf ("%d\n", ((char *)Second_String + j * sizeof(char*)));

                j += 1;
            }
            else
                return -1;
        }

    return 0;
}






void Buble_Sorting(void *Starting_Addresses, int Amount_Of_Strings,
                                            int (*Compare_Func)(void *, void *))
{
    /*
    printf("Was    %d\n",    *((char *)Starting_Addresses + 0 * sizeof(char*)) );
    printf("       %d\n",   *((char *)Starting_Addresses + 1 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 2 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 3 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 4 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 5 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 6 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 7 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 8 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 9 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 10 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 11 * sizeof(char*)));
    printf("       %d\n\n", *((char *)Starting_Addresses + 12 * sizeof(char*)));
    */
    for (int Left_Ad = 0; Left_Ad < Amount_Of_Strings; Left_Ad++)
    {
        for (int i = 0; i < Amount_Of_Strings - 1; i++)
        {
            printf("%c\n", *((char *)Starting_Addresses + (i)     * sizeof(char*)));

            int Compator = (*Compare_Func)(((char *)Starting_Addresses + (i)     * sizeof(char*)),
                                           ((char *)Starting_Addresses + (i + 1) * sizeof(char*)));
            //printf("%d\n", Compator);
            if  (Compator > 0)
                Swapping_Places( ((char *)Starting_Addresses + (i)     * sizeof(char*)),
                                 ((char *)Starting_Addresses + (i + 1) * sizeof(char*)),
                                                                         sizeof(char*));
        }
    }

    /*
    printf("Became %d\n",   *((char *)Starting_Addresses + 0 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 1 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 2 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 3 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 4 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 5 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 6 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 7 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 8 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 9 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 10 * sizeof(char*)));
    printf("       %d\n",   *((char *)Starting_Addresses + 11 * sizeof(char*)));
    printf("       %d\n\n", *((char *)Starting_Addresses + 12 * sizeof(char*)));
    */
}




void Swapping_Places(void *Address_Of_Sting_1, void *Address_Of_Sting_2, int Size_Of_Cymbol)
{
    assert(Address_Of_Sting_1);
    if (Address_Of_Sting_1 == 0)
    {
        printf("Swapping_Places: returned code 0\n");
        return ;
    }

    assert(Address_Of_Sting_2);
    if (Address_Of_Sting_1 == 0)
    {
        printf("Swapping_Places: returned code 0\n");
        return ;
    }

    unsigned long long int Temp = 0;
    int Adding_Memory = 0;

    /*
    printf("Adresses b4 sorting:\n");
    printf("%d\n",   Address_Of_Sting_1);
    printf("%d\n\n", Address_Of_Sting_2);
    */

    while (Size_Of_Cymbol > 0)
    {


        if      ( (Size_Of_Cymbol >> 3) > 0)
            Adding_Memory = sizeof(long long int);

        else if ( (Size_Of_Cymbol >> 2) > 0)
             Adding_Memory = sizeof(int);

        else if ( (Size_Of_Cymbol >> 1) > 0)
            Adding_Memory = sizeof(short);

        else
            Adding_Memory = sizeof(char);

        memcpy(&Temp, Address_Of_Sting_2,              Adding_Memory);
        memcpy(Address_Of_Sting_2, Address_Of_Sting_1, Adding_Memory);
        memcpy(Address_Of_Sting_1, &Temp,              Adding_Memory);

        Address_Of_Sting_1 = (char *) Address_Of_Sting_1 + Adding_Memory;
        Address_Of_Sting_2 = (char *) Address_Of_Sting_2 - Adding_Memory;

        Size_Of_Cymbol -= Adding_Memory;

    }


    //printf("Adresses after Sorting:\n");
    //printf("%c\n",  *((char *) Address_Of_Sting_1));
    //printf("%d\n\n", Address_Of_Sting_2);

}



off_t Fsize(const char *filename)
{
    struct stat st = {};
    if (stat(filename, &st) == 0)
        return st.st_size;
    return -1;
}


