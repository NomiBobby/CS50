#include <cs50.h>
#include <stdio.h>
#include <ctype.h>

int main(void)
{
    
    int i, j, k, height;
    
    do
    { 
        
        height = get_int("Height: ");
    
    }
    while (height < 1 || height > 8);
    
    for (i = 0; i < height; i++)
    {
        
        //LEFT
        int num_blankspace = height - i - 1;

        for (k = 0; k < num_blankspace; k++)
        {
            printf(" ");
        }
        
        for (k = 0; k < i + 1; k++)
        {
            printf("#");
        }
            
        
        // two middle spaces
        printf("  ");
        
        //RIGHT
        for (k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        
        //next line
        printf("\n");
    }
}