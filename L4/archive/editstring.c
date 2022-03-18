#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
    // char *s = "hi!";
    // char *t = s;

    string s = "hi!";
    string t = s;

    // t[1] = 'C'; 
    
    printf("%s\n", s);
    printf("%s\n", t);
    
    return 0;
}