#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int compute_score(string word);

int main(void){
    
compute_score("ABCabcXYZxyz");

}

int compute_score(string word)
{
    int index;
    int score[];
    
    // TODO: Compute and return score for string
    for(int i = 0, n = strlen(word); i < n; i++){
        
        if (word[i] >= 'a' && word[i] <= 'z'){
            index = word[i]-96;
            printf("%c  %i\n", word[i], index);
        }
        else if (word[i] >= 'A' && word[i] <= 'Z'){
            index = word[i]-64;
            printf("%c  %i\n", word[i], index);
        }
        else{
            score[i] = 0;
        }
    }
    
    return 0;
    
}