#include <stdio.h>
#include <cs50.h>

// Functions:
int find_length_of_num(long n);
int find_first_number(long n, int i);
string find_cc_type(long n);
bool validate_checksum(long n);

// Main program
int main(void)
{
    // Initiate variables
    long cc_num = NULL;
    bool isValid = false;

    // Prompt user fo cc number (assume all digits and no special characters)
    cc_num = get_long("Enter credit card number\n");

    // Perform checksum validation:
    isValid = validate_checksum(cc_num);

    // Check if valid card
    string card = "INVALID";
    if (isValid)
    {
        card = find_cc_type(cc_num);
    }
    printf("%s\n", card);
}

// Function to find length of cc
int find_length_of_num(long n)
{
    int count = 0;

    while (n != 0)
    {
        n /= 10;
        count++;
    }
    return count;
}

// Function to find first number in cc
int find_first_number(long n, int i)
{
    long first = n;
    int check = 10;

    for (int j = 1; j < i; j++)
    {
        check *= 10;
    }

    while (first > check)
    {
        first /= 10; // removes last digit from number until one digit is left
    }
    return first;
}

// Check credit card type based on first number and length
// - AMEX: 15 digits and starts with 34 or 37
// - MASTERCARD: 16 digits and starts with 51, 52, 53, 54, or 55
// - VISA: 13- & 16- digit numbers and start with 4
string find_cc_type(long cc_num)
{
    int cc_length = find_length_of_num(cc_num);
    string cc_type;

    // AMEX Check
    if (cc_length == 15 && (find_first_number(cc_num, 2) == 34 || find_first_number(cc_num, 2) == 37))
    {
        cc_type = "AMEX";
    }
    // MASTERCARD Check
    else if (cc_length == 16
             && (find_first_number(cc_num, 2) == 51
                 || find_first_number(cc_num, 2) == 52
                 || find_first_number(cc_num, 2) == 53
                 || find_first_number(cc_num, 2) == 54
                 || find_first_number(cc_num, 2) == 55))
    {
        cc_type = "MASTERCARD";
    }
    else if ((cc_length == 16 || cc_length == 13) && (find_first_number(cc_num, 1) == 4))
    {
        cc_type = "VISA";
    }
    else
    {
        cc_type = "INVALID";
    }

    return cc_type;
}

// Function to perform checksum validation using Luhn's Algorithm
bool validate_checksum(long cc_num)
{
    int sum1 = 0;
    int sum2 = 0;
    int cc_length = find_length_of_num(cc_num);

    for (int i = 0; i < cc_length; i++)
    {
        int last = cc_num % 10; // get last digit
        cc_num /= 10; // remove last digit

        // if index (i) is 0 or even number, add last to sum2.
        // else, double last and add to sum1.
        if (i == 0 || i % 2 == 0)
        {
            sum2 = sum2 + last;
        }
        else
        {
            int dbl_last = last * 2;
            // if double digit, split it before adding
            if (dbl_last >= 10)
            {
                sum1 = sum1 + (dbl_last / 10) + (dbl_last % 10); // sum + first + last
            }
            else
            {
                sum1 = sum1 + dbl_last;
            }
        }
    }

    int total = sum1 + sum2;
    bool isLastZero = total % 10 == 0;

    return isLastZero;
}
