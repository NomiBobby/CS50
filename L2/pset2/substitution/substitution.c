#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

bool check_key(string key);

string encrypt(string key, string plaintext);

// argc refers to the number of arguments passed, and argv[] is a pointer
// array which points to each argument passed to the program
// argv[0] is the program itself, argv[1] is the arguement followed the program name
int main(int argc, string argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // while the key does not satisfy the requirement
    if (check_key(argv[1]) == 1)
    {
        return 1;
    }

    //printf("The key is: %s\n", argv[1]);
    
    string plain_text = get_string("plaintext: ");
    
    printf("The plain text is: %s\n", plain_text);
    
    string ciphertext = encrypt(argv[1], plain_text);

}

bool check_key(string key)
{
    // is the key comprised of 26 characters
    int string_length = strlen(key);
    if (string_length == 26)
    {
        for (int i = 0; i < string_length; i++)
        {
            // is alphabet?
            if (isalpha(key[i]))
            {
                //convert string into lower case only
                key[i] = tolower(key[i]);
                
                // any duplicates?
                for (int j = i + 1; j < string_length; j++)
                {
                    if (key[i] == tolower(key[j]))
                    {
                        printf("Key must not contain any duplicates\n");
                        return 1;
                    }
                }

            }
            else
            {
                printf("Key should be alphabetical.\n");
                return 1;
            }
        }
        //key check passed
        return 0;
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
}

string encrypt(string key, string plaintext)
{
    int index = 0;
    int length = strlen(plaintext);
    string ciphertext = plaintext;
    for (int i = 0; i < length; i++)
    {
        // Is this a alphabet? Otherwise conserve the value.
        if (isalpha(plaintext[i]))
        {
            
            printf("i = %i, %c\n", i, plaintext[i]);
            
            // Is lower case
            if (islower(plaintext[i]))
            {
                index = (int) plaintext[i] - 96;
                ciphertext[i] = tolower(key[index - 1]);
            }
            // Is upper case
            else if (isupper(plaintext[i]))
            {
                index = (int) plaintext[i] - 64;
                ciphertext[i] = toupper(key[index - 1]);
            }
        }
    }
    
    printf("ciphertext: %s\n", ciphertext);
    return ciphertext;
    
}