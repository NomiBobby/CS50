#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
     int p_start;
     int p_end;
     
     do
     {
         p_start = get_int("Start size: ");
     }
    while (p_start < 9);

    // TODO: Prompt for end size

    do
    {
         p_end = get_int("End size: ");
    }
    while (p_end < p_start);

    // TODO: Calculate number of years until we reach threshold
    int population = p_start;
    int num_born, num_dead;
    int n = 0;//n is the number of years
    
    //check if the current size is greater or equal to the end size
    for (n = 0; population < p_end; n = n+1){
        
        num_born = population/3;
        num_dead = population/4;
        population = population + num_born - num_dead;
        
    }
    
    printf("Years: %i\n", n);
    // TODO: Print number of years
}