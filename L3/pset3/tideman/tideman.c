#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool check_loop(int start, int end);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    printf("-----Add pairs below---\n");
    add_pairs();
    printf("-----Sort pairs below---\n");
    sort_pairs();
    printf("-----Lock pairs below---\n");
    lock_pairs();
    printf("-----Print pairs below---\n");
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // find the name in the candidates array (not sorted)
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            // ranks[i] is the index of the candidate who is the ith preference for the voter.
            ranks [rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
// ranks[i] is the voter’s ith preference, where ranks[0] is the first preference
// preferences[i][j] represent the number of voters who prefer candidate i over candidate j
void record_preferences(int ranks[])
{

    int index_winner;
    int index_loser;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            index_winner = ranks[i];
            index_loser = ranks[j];

            // global and static variables are default 0
            preferences[index_winner][index_loser] ++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
// The function should add all pairs of candidates where one candidate is preferred to the pairs array.
// A pair of candidates who are tied (one is not preferred over the other) should not be added to the array.
void add_pairs(void)
{
    // Evaluate preferences[i][j] against preferences[j][i], only need to run i through candidate_count - i
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                // Each pair includes the winner’s candidate index and the loser’s candidate index.
                pairs[pair_count].winner = i;
                pairs[pair_count].loser =  j;
                pair_count ++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                // Each pair includes the winner’s candidate index and the loser’s candidate index.
                pairs[pair_count].winner = j;
                pairs[pair_count].loser =  i;
                pair_count ++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int victory_strength[MAX * (MAX - 1) / 2];

    for (int i = 0; i < pair_count; i++)
    {
        // preferences(i,j - j,i)
        victory_strength[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    int index_max;

    //pair pairs[MAX * (MAX - 1) / 2];
    //pair sorted_pairs[MAX * (MAX - 1) / 2];

    // find the max number from i to pair_count
    for (int i = 0; i < pair_count; i++)
    {
        index_max = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            // compare j with the maximum value so far
            if (victory_strength[j] > victory_strength[index_max])
            {
                // update index_max to j
                index_max = j;
            }
        }

        // swap the ith element with index_max in victory_strength
        int victory_strength_temp;
        victory_strength_temp = victory_strength[i];
        victory_strength[i] = victory_strength[index_max];
        victory_strength[index_max] = victory_strength_temp;

        // swap the ith element with index_max in pairs
        pair pair_temp;
        pair_temp = pairs[i];
        pairs[i] = pairs[index_max];
        pairs[index_max] = pair_temp;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // for each pair, check if this will create a loop
    for (int i = 0; i < pair_count; i++)
    {
        //printf("Check pair %i, winner %s, loser %s\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
        if (check_loop(pairs[i].winner, pairs[i].loser) == false)
        {
            // Lock this pair
            //printf("Added pair %i, winner %s, loser %s\n", i, candidates[pairs[i].winner], candidates[pairs[i].loser]);
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

bool check_loop(int start, int end)
{
    //find true on row end
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[end][i] == true)
        {
            // is i the start?
            if (i == start)
            {
                // found the loop
                //printf("Found a loop from %i to %i\n", end, start);
                return true;

            }
            else
            {
                //check if row loser can go to row winner
                if (check_loop(start, i) == true)
                {
                    //printf("Found a loop from %i to %i\n", end, start);
                    return true;
                }
            }
        }
    }

    // if the program reaches here, means it is the tip, nothing is below
    //printf("No loop\n");
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    //Print locked matrix below
    // for (int i = 0; i < candidate_count; i++)
    // {
    //     for( int j = 0; j < candidate_count; j++)
    //     {
    //         if (locked[i][j] == true)
    //         {
    //             printf("1");
    //         }
    //         else
    //         {
    //             printf("0");
    //         }
    //     }
    //     printf("\n");
    // }

    for (int i = 0; i < candidate_count; i++)
    {
        int sum = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            //column i, row j
            if (locked[j][i] == true)
            {
                sum = sum + 1;
            }
        }

        if (sum == 0)
        {
            //found the winner
            printf("\n%s\n", candidates[i]);
            break;
        }

    }

    return;
}