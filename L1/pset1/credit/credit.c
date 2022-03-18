#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



bool checksum();


int main(void)
{
    long card_number;
    do
    {
        
        card_number = get_long("Number: "); 
    
    }
    while (checksum(card_number));
}

bool checksum(long card_number)
{
    
    // convert card number from long to char/string¬
    char card_number_str[256]; 
    sprintf(card_number_str, "%li", card_number);
    //printf("%s\n",card_number_str);
    
    int num_length = strlen(card_number_str);
    //printf("The length of the string is %i\n", num_length);
    //American Express uses 15-digit numbers, MasterCard uses 16-digit numbers, and Visa uses 13- and 16-digit numbers.
    
    if (num_length == 15 || num_length == 16 || num_length == 13)
    {
    
        int index;
        int sum = 0;
        int num;
        
        //STEP 1
        //Multiply every other digit by 2, starting with the number’s second-to-last digit, 
        // and then add those products’ digits together.
        index = num_length - 2;
        do
        {
            // This is the second to last
            num =  card_number_str[index] - '0';
            //printf("%i", num);
            
            if (num >= 0 && num < 5)
            {
                sum = sum + num * 2;
            }
            else
            {
                sum = sum + 1 + (num * 2 - 10);
            }
            
            index = index - 2;
        }
        while (index >= 0);
        
        //printf("\n-----------------------------\n");
        
        //STEP 2
        //Add the sum to the sum of the digits that weren’t multiplied by 2.
        index = num_length - 1;
        do
        {
            //This is the last
            num =  card_number_str[index] - '0';
            //printf("%i", num);
            sum = sum + num;
            index = index - 2;
        }
        while (index >= 0);
        
        //printf("The sum is: %i\n", sum);
        
        
        //STEP 3
        // If the total’s last digit is 0 (or, put more formally, if the 
        // total modulo 10 is congruent to 0), the number is valid!
        if (sum % 10 == 0)
        {
            // Valid, get the first two digits of the card number
            //All American Express numbers start with 34 or 37; most MasterCard numbers start with 51, 52, 53, 54, or 55
            //(they also have some other potential starting numbers which we won’t concern ourselves with for this problem);
            //and all Visa numbers start with 4.
            char Digit_1st = card_number_str[0];
            char Digit_2st = card_number_str[1];
            if (Digit_1st == '4')
            {
                printf("VISA\n");
            }
            else if (Digit_1st == '3' && (Digit_2st == '4' || Digit_2st == '7'))
            {
                printf("AMEX\n");
            }
            else if (Digit_1st == '5' && (Digit_2st == '1' || Digit_2st == '2'  || Digit_2st == '3' || Digit_2st == '4' || Digit_2st == '5'))
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
            
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    else 
    {
        printf("INVALID\n");
    }
    
    return 0;
}