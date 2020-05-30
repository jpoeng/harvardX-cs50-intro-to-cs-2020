#include <stdio.h>
#include <cs50.h>

void print_row(int r, int h);
void print_hash(int r);
void print_spaces(int n);

int main(void)
{
    int height;

    // prompt the user for input between 1-8 (checks on line 17)
    do
    {
        height = get_int("Height of pyramid (1-8): \n");
    }
    while (height < 1 || height > 8); // checks for 0s, negative integers, and values greater than 8

    // being loop and print rows
    for (int i = 0; i <= height; i++)
    {
        print_row(i, height);
    }
}

// prints each row in the pyramid
void print_row(int row, int height)
{
    if (row == 0)
    {
        return; // don't print anything if on row 0
    }
    print_spaces(height - row);
    print_hash(row);
    print_spaces(2);
    print_hash(row);
    printf("\n");
}

// must use loop to print "#" xtimes because in C,
// you can't multiply a character by an integer (e.g. "#" * 5).
void print_hash(int r)
{
    for (int hash = 0; hash < r; hash++)
    {
        printf("#");
    }
}

void print_spaces(int n)
{
    for (int sp = 0; sp < n; sp++)
    {
        printf(" ");
    }
}
