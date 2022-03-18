#include <cs50.h>
#include <stdio.h>

#define MAX 4

bool check_path(int start, int end);
bool locked[MAX][MAX];

int main(void)
{

    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        locked[i][j] = false;
    }
    
    locked[0][1] = true;
    locked[1][2] = true;
    locked[2][3] = true;
    locked[3][0] = true;
    
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            if( i!= j)
            {
                printf("-----Check (%i, %i)-----\n", i, j);
                check_path(i, j);
            }
        }
    }
    
    return 0;
}

// Check if end can go to start, yes - loop, no - no loop
bool check_path(int start, int end)
{
    //find true on row end
    for (int i = 0; i < MAX; i++)
    {
        if (locked[end][i] == true)
        {
            // is i the start?
            if (i == start)
            {
                // found the loop
                printf("Found a loop, checking row %i, column %i\n", end, i);
                return true;
            }
            else
            {
                //check if row loser can go to row winner
                printf("check (row %i)\n", i);
                check_path(start, i);
            }
        }
    }
    
    // if the program reaches here, means it is the tip, nothing is below
    printf("No loop\n");
    return false;
}