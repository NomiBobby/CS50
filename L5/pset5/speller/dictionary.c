// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 101;

//number of words in dictionary
int num_dicWords = 0;

// Hash table
node *table[N];

// insert a new word into the hash table
bool install(char *word)
{
    struct node *np;
    unsigned hashval;
    //printf("Check if word is in the dictionary:\n");
    if (check(word) == false)/* not found */
    {
        //printf("Word not in the dictionary!\n");
        np = (node *) malloc(sizeof(node));
        if (np == NULL)
        {
          return NULL;
        }

        // copy string from word to node->word
        int i;
        for (i = 0; word[i] != '\0'; i++)
        {
            np->word[i] = word[i];
            //printf("copied %c\n", word[i]);
        }
        np->word[i] = '\0';

        hashval = hash(word);
        np->next = table[hashval];
        table[hashval] = np;
        num_dicWords++;
        //printf("Installed word: %s, hashval = %i\n", np->word, hashval);
        //printf("Retrieved table[%i] word: %s\n", hashval, table[hashval]->word);
        return true;
    }

    return false;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // convert word to lower case
    char lowerWord[LENGTH + 1];
    strcpy(lowerWord, word);
    for(int i=0;i<=strlen(lowerWord);i++)
    {
        if(lowerWord[i]>=65 && lowerWord[i]<=90)
        {
            lowerWord[i]=lowerWord[i]+32;
        }
    }

    node* np;
    for (np = table[hash(lowerWord)]; np != NULL; np = np->next)
    {
        if (strcmp(lowerWord, np->word) == 0) // equals
        {
            return true; // found
        }
    }
    return false;// not found
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //printf("****Start hashing*****\n");
    unsigned hashval = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        //printf("The %ith alphabet is %c,", i, word[i]);
        hashval = word[i] + 31 * hashval;
        //printf("hashval = %u\n",hashval);
    }
    //printf("Hashed to table[%u]\n", hashval % N);
    return hashval % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // read line by line, seperate by "\n"
    FILE *file = fopen(dictionary,"r");
    int bufferLength = 46;
    char buffer[bufferLength];
    if (file == NULL)
    {
        printf("Can't open dictionary.\n");
        return false;
    }
    else
    {
        while(fscanf(file,"%s", buffer) != EOF)
        //while(fgets(buffer, bufferLength, file))
        {
            //remove the "\n" at the end of buffer
            //buffer[strcspn(buffer, "\n")] = '\0';
            install(buffer);
        }
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return num_dicWords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        while(head)
        {
            node *n1 = head;
            head = head->next;
            free(n1);
        }
    }
    return true;
}