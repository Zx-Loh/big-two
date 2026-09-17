#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct 
{

    // Cards will be a data struct with 2 ints
    // Suits will be from 0 to 3 in the order Diamonds, Clubs, Hearts, Spades
    // Card values will be 10 for Jack, 11 for Queen, 12 for King, 13 for Ace.
    // Due to game rules, 2 is the highest scoring card so it will be listed as 14
    
    int suit;
    int value;

} card;


int init(card deck[]);
void displayCard(card playingCard);
void shuffle(card deck[]);
void printDeck(card deck[]);


int main(void) 
{
    card deck[52];

    // Initialize 
    printf("Welcome to Big Two!\n");
    if (init(deck) == 1)
    {
        printf("Failed to initialize\n");
        return 1;
    }

    // Display all cards in deck
    for (int i = 0; i < 52; i++)
    {
        displayCard(deck[i]);
    }

    printf("\n\n\n");

    // Shuffle array in place
    shuffle(deck);
    printDeck(deck);


    // Deal cards to all players
    // Will default to 4 players, possible implementation which allows players to choose amount of people in a room



    return 0;
}


// Initialize game by creating deck of 52 cards
int init(card deck[])
{
    // Create deck
    // Make 13 cards for each suit in ascending order
    int pos = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 3; j < 16; j++)
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

            deck[pos] = *new;
            pos++;
        }
    }
}


// Prints out value of specified card and suit to screen
void displayCard(card playingCard)
{
    int suit = playingCard.suit;
    int value = playingCard.value;
    char* faceValue;
    char* cardSuit;

    switch (suit)
        {
            case 0:
                cardSuit = "Diamonds";
                break;

            case 1:
                cardSuit = "Clubs";
                break;

            case 2:
                cardSuit = "Hearts";
                break;

            case 3:
                cardSuit = "Spades";
                break;
        }

    if (value > 10)
    {
        switch (value)
        {
            case 11:
                faceValue = "Jack";
                break;

            case 12:
                faceValue = "Queen";
                break;

            case 13:
                faceValue = "King";
                break;

            case 14:
                faceValue = "Ace";
                break;

            case 15:
                faceValue = "2";
                break;

        }

        printf("%s of %s\n", faceValue, cardSuit);
    }
    else
    {
        printf("%i of %s\n", value, cardSuit);
    }
}

// Randomly shuffles cards in given deck array
void shuffle(card deck[])
{
    // Set seed to current random time
    srand(time(NULL));

    // Swap position of each element in the array with random element
    for (int i = 0; i < 52; i++)
    {
        // Generate random index to swap currenet element with
        int random;
        random = rand() % 51;

        // Ensure random index is not itself
        while (random == i)
        {
            random = rand() % 51;
        }

        // Swap both elements
        card tmp = deck[i];
        deck[i] = deck[random];
        deck[random] = tmp;
    }
}

// Displays whole deck by running displayCard through all items in a set
void printDeck(card deck[])
{
    // Display all cards in deck
    for (int i = 0; i < 52; i++)
    {
        displayCard(deck[i]);
    }
}