#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// todo read_To_Buf
// todo

/**
 *
 * todo Read_To_Buf
 * todo (memcopy) Read_To_Buf 2
 *
 * todo Pre_Process in Buf1 switches \r\n on '0'
 * todo in Buf1 Parse_Strings this is gonna write an adress on el after \n
 * todo print each string and each symbol in them
 *
 * todo Bubl_Srt with Buf1
 * todo test it on ints with void* and use comparatre in the easiest way
 * todo print each address in sort b4 and after
 *
 * todo test comparator and use inside an strcmp
 *
 * todo swap and test it on strings
 *  */

enum All_Exit_Codes
{
    EXIT_CODE_ERROR = -1,
    PROGRAMM_IS_IN_PROGRESS = 0,
    SUCCESFUL_EXIT = 1,
};
/*
struct Adresses
{
    char **Starting_Ad
    char **Ending_Ad
};
*/

struct Must_Needed_For_Text
{
    char *Text;
    char **Addresses;
    int Amount_Of_Strings;
    int *Lengths_Of_Strings;
};



void Reader(char **Output_Text, int Size_Of_File, int *Amount_Of_Strings, char **Addresses);

void Buble_Sorting(void *Starting_Addresses, int Amount_Of_Strings, int Size_Of_Cymbol,
                                            int (*Compare_Func)(void *, void *));

int Compare_Func (void *First_String, void *Second_String);

void Quick_Sort(void *Starting_Addresses, int Left_Ad, int Right_Ad,
                                            int (*Compare_Func)(void *, void *));

void Swapping_Places(void *Address_Of_Sting_1, void *Address_Of_Sting_2, int Size_Of_Cymbol);

void *Tell_Me_Address(void *Adresses, int Index, int Size_Of_Cymbol);

off_t Fsize(const char *filename);



int main()
{
    struct stat Stat_Buffer = {};
    stat("Text_Of_Onegin.txt", &Stat_Buffer);
    printf ("\nBad_Method:\n\v%ld\n\v", Stat_Buffer.st_size);

    int Size_Of_File = Fsize("Text_Of_Onegin.txt");
    printf ("Good method:\n\v%d\n\v", Size_Of_File);



    struct Must_Needed_For_Text Onegin = {0, 0, 0, 0};

    Onegin.Text = (char *)calloc(Size_Of_File, sizeof(char));
    Onegin.Amount_Of_Strings = 0;
    Onegin.Addresses = (char **)calloc(Size_Of_File, sizeof(char*));
    Onegin.Addresses[0] = &(Onegin.Text[0]);



    Reader(&Onegin.Text, Size_Of_File, &Onegin.Amount_Of_Strings, Onegin.Addresses);
    Size_Of_File = Size_Of_File - Onegin.Amount_Of_Strings;

    Swapping_Places(&Onegin.Addresses[1],&Onegin.Addresses[2], sizeof(char*));
/*
    printf("\n          The text was:\n\v");



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
*/


    //printf("\t%d\n", Compare_Func(&Onegin.Addresses[12],&Onegin.Addresses[11]));

    printf("\nAmount Of Strings: %d\n", Onegin.Amount_Of_Strings);


    Buble_Sorting( Onegin.Addresses, Onegin.Amount_Of_Strings, sizeof(char *), Compare_Func);
    printf("10\n\n");

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
    if (Opened_File != 0)
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


/*
void Swapping_Places(void *Address_Of_Sting_1, void *Address_Of_Sting_2, int Size_Of_Cymbol)
{
    void *Temp = 0;
    Temp =  Address_Of_Sting_1;
    memcpy (Address_Of_Sting_1, Address_Of_Sting_2, sizeof(char*));
    memcpy (Address_Of_Sting_2, Temp, sizeof(char*));
}
*/



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

    unsigned long long Temp = 0;
    int Adding_Memory = 0;


    while (Size_Of_Cymbol > 0)
    {
        if      ( (Size_Of_Cymbol >> 3) > 0)
            Adding_Memory = sizeof(__int64);

        else if ( (Size_Of_Cymbol >> 2) > 0)
             Adding_Memory = sizeof(__int32);

        else if ( (Size_Of_Cymbol >> 1) > 0)
            Adding_Memory = sizeof(__int16);

        else
            Adding_Memory = sizeof(__int8);

        memcpy(&Temp, Address_Of_Sting_2,               Adding_Memory);
        memcpy(Address_Of_Sting_2, Address_Of_Sting_1,  Adding_Memory);
        memcpy(Address_Of_Sting_1, &Temp,               Adding_Memory);

        Address_Of_Sting_1 = (char *) Address_Of_Sting_1 + Adding_Memory;
        Address_Of_Sting_2 = (char *) Address_Of_Sting_2 + Adding_Memory;

        Size_Of_Cymbol -= Adding_Memory;

    }

    //printf("Adresses after Sorting:\n");
    //printf("%c\n",  *((char *) Address_Of_Sting_1));
    //printf("%d\n\n", Address_Of_Sting_2);

}



void Buble_Sorting(void *Starting_Addresses, int Amount_Of_Strings, int Size_Of_Cymbol,
                                            int (*Compare_Func)(void *, void *))
{
    /*
    printf("Was    %d\n",   *((char **)Starting_Addresses + 0 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 1 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 2 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 3 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 4 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 5 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 6 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 7 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 8 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 9 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 10 * sizeof(char*)));
    printf("       %d\n",   *((char **)Starting_Addresses + 11 * sizeof(char*)));
    printf("       %d\n\n", *((char **)Starting_Addresses + 12 * sizeof(char*)));
    */

    for (int j = 0; j < Amount_Of_Strings; j++)
    {
        for (int i = 0; i < Amount_Of_Strings - 1; i++)
        {
            int Comparator = strcmp(*(char **)Tell_Me_Address(Starting_Addresses, i,     Size_Of_Cymbol),
                                    *(char **)Tell_Me_Address(Starting_Addresses, i + 1,     Size_Of_Cymbol));
            //int Comparator = (*Compare_Func)(*(char **)Tell_Me_Address(Starting_Addresses, i,     Size_Of_Cymbol),
            //                                 *(char **)Tell_Me_Address(Starting_Addresses, i + 1,     Size_Of_Cymbol));

            if  (Comparator > 0)
            {
                //printf("        %d\n", Tell_Me_Address(Starting_Addresses, i,     Size_Of_Cymbol));
                //printf("        %d\n", Tell_Me_Address(Starting_Addresses, i + 1,     Size_Of_Cymbol));

                Swapping_Places( Tell_Me_Address(Starting_Addresses, i,     Size_Of_Cymbol),
                                 Tell_Me_Address(Starting_Addresses, i + 1, Size_Of_Cymbol), Size_Of_Cymbol);

                //printf("        %d\n", Tell_Me_Address(Starting_Addresses, i,     Size_Of_Cymbol));
                //printf("        %d\n\n", Tell_Me_Address(Starting_Addresses, i + 1,     Size_Of_Cymbol));
            }

        }
    }

}



int Compare_Func (void *First_String, void *Second_String)  // This func is comparing symbols
{
    int j = 0;
    //printf("%d\n", *((char*)(Tell_Me_Address)(First_String, 0, sizeof(char *))) );
    while ( *((char*)Tell_Me_Address(First_String, j, sizeof(char*))) != '\n' && *((char*)Tell_Me_Address(Second_String, j, sizeof(char*))) != '\n')
        {
                //int a = *((char*)Tell_Me_Address(First_String, j, sizeof(char*)));
                //printf ("%d\n", a);
                //printf ("%d\n", *((char *)First_String + j * sizeof(char*)));
            if  (
                tolower(*((char*)Tell_Me_Address(First_String, j, sizeof(char  *)))  ) -
                tolower(*((char*)Tell_Me_Address(Second_String, j, sizeof(char *))) ) > 0
                )
            {
                return 1;
            }
            else if
                (
                tolower(*((char*)Tell_Me_Address(First_String, j, sizeof(char  *)))  ) -
                tolower(*((char*)Tell_Me_Address(Second_String, j, sizeof(char *))) ) == 0
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



off_t Fsize(const char *filename)
{
    struct stat st = {};
    if (stat(filename, &st) == 0)
        return st.st_size;
    return -1;
}

void *Tell_Me_Address(void *Adresses, int Index, int Size_Of_Cymbol)
{

    assert (Adresses);
    if (Adresses == 0)
    {
        printf("Tell_Me_Address: returned code 0\n");
        return 0;
    }

    assert (Index >= 0);
    if (Index < 0) {
        printf("Tell_Me_Address: returned code 0\n");
        return 0;
    }

    assert (Size_Of_Cymbol > 0);
    if (Size_Of_Cymbol <= 0)
    {
        printf("Tell_Me_Address: returned code 0\n");
        return 0;
    }

    return ( (char *) Adresses + Index * Size_Of_Cymbol );
}
