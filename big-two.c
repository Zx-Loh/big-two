#include <stdio.h>
#include <stdlib.h>

typedef struct 
{

    // Cards will be a data struct with 2 ints
    // Suits will be from 0 to 3 in the order Diamonds, Clubs, Hearts, Spades
    // Card values will be 10 for Jack, 11 for Queen, 12 for King, 13 for Ace.
    // Due to game rules, 2 is the highest scoring card so it will be listed as 14
    
    int suit;
    int value;

} card;


int init(int *deck);


int main(void) 
{
    card *deck[52];

    // Initialize 
    printf("Welcome to Big Two!\n");
    if (init(deck) == 1)
    {
        printf("Failed to initialize\n");
        return 1;
    }

    for (int i = 0; i < 52; i++)
    {
        displayCard(deck[i]);
    }

    return 0;
}



int init(int *deck)
{
    // Create deck
    // Make 13 cards for each suit in ascending order
    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j < 15; j++)
        {
            // Create new card structure and place in deck
            card* new = malloc(sizeof(card));

            // Check for malloc success
            if (new == NULL)
            {
                return 1;
            }

            new -> suit = i;
            new -> value = j;

            deck[pos] = new;
            pos++;
        }
    }
}

void displayCard(card* playingCard)
{

}