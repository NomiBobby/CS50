#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <stdlib.h>
# include <math.h>

int count_letters(string text);
int count_words(string text);
int count_scentences(string text);

int main(void)
{

    string text = get_string("Text:");
    printf("%s\n", text);

    int num_letters = count_letters(text);
    printf("%i letter(s)\n", num_letters);

    int num_words = count_words(text);
    printf("%i word(s)\n", num_words);

    int num_scentences = count_scentences(text);
    printf("%i scentence(s)\n", num_scentences);

    // index = 0.0588 * L - 0.296 * S - 15.8
    //where L is the average number of letters per 100 words in the text,
    // and S is the average number of sentences per 100 words in the text.
    float L = 100 / (float) num_words * (float) num_letters;
    float S = 100 / (float) num_words * (float) num_scentences;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    if (index < 1) 
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 1 && index <= 15)
    {
        printf("Grade %i\n", (int)(round(index)));
    }
    else
    {
        printf("Grade 16+\n");
    }

}

int count_letters(string text)
{
    int total_length = strlen(text);
    int num_letters = 0;

    for (int i = 0; i < total_length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            num_letters++;
        }
    }

    return num_letters;
}

int count_words(string text)
{

    // from text[0], find next space
    int num_words = 0;
    int total_length = strlen(text);

    for (int i = 0; i < total_length; i++)
    {
        if (text[i] == ' ')
        {
            num_words++;
        }
    }

    //for the last word in the string, it does not have a spece at the end
    num_words++;

    return num_words;
}

int count_scentences(string text)
{

    // from text[0], find next .,? and !
    int num_scentences = 0;
    int total_length = strlen(text);

    for (int i = 0; i < total_length; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            num_scentences++;
        }
    }

    return num_scentences;
}