#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int DECK_SIZE = 52;

typedef struct 
{

    // Cards will be a data struct with 2 ints
    // Suits will be from 0 to 3 in the order Diamonds, Clubs, Hearts, Spades
    // Card values will be 11 for Jack, 12 for Queen, 13 for King, 14 for Ace.
    // Due to game rules, 2 is the highest scoring card so it will be listed as 15
    
    int suit;
    int value;

} card;

typedef struct player
{
    // Each player will be represented by a data structure,
    // that contains an array of held cards and a pointer to the next player.
    // When a card is played, it will be replaced by a 0.
    // The players will form a linked list that also serves as turn order.
    
    card hand[13];
    struct player *next;

} player;



int init(card deck[], int playerCount);
void displayCard(card playingCard);
void shuffle(card deck[]);
void printDeck(card deck[]);
void dealCards(card deck[], int playerCount, player *head);
player *createPlayers(int playerCount);
void showHand(player* currentPlayer);



int main(void) 
{
    // Initialize variables and constants
    card deck[DECK_SIZE];
    int playerCount = 4;
    bool gameOver = false;



    // Initialize 
    printf("Welcome to Big Two!\n");
    if (init(deck, playerCount) != 0)
    {
        printf("Failed to initialize\n");
        return 1;
    }


    // Display all cards in deck
    printDeck(deck);

    printf("\n\n\n");

    // Shuffle array in place
    shuffle(deck);



    // Create 4 player data structures
    player *firstPlayer = createPlayers(playerCount);

    // Check for errors in player initialization
    if (firstPlayer == NULL)
    {
        printf("Player initialization error\n");
        return 1;
    }


    // Deal cards to all players
    // Defautl is 4 players, possible future implementation which allows players to choose amount of people in a room
    dealCards(deck, playerCount, firstPlayer);


    // Show distributed hand cards of all players
    player *tmp = firstPlayer;
    for (int i = 0; i < playerCount; i++)
    {
        printf("Player %i's hand:\n", i + 1);
        showHand(tmp);
        tmp = tmp->next;
    }
    

    // Set variable to store current player
    // This should be set to the first player at the start of the game.
    player *currentPlayer = firstPlayer;

    // Main game loop
    while (gameOver)
    {
        printf("Running\n");
    }

    return 0;
}




// Initialize game by creating deck of 52 cards
int init(card deck[], int playerCount)
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

            new->suit = i;
            new->value = j;

            deck[pos] = *new;
            pos++;
        }
    }

    return 0;
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


// Takes in amount of players in current game, and deals cards in shuffled deck
// evenly based on player count
void dealCards(card deck[], int playerCount, player *head)
{
    int cardsPerPlayer = DECK_SIZE / playerCount;

    // Traverse player list
    player *ptr = head;
    int deckIndex = 0;

    for (int i = 0; i < playerCount; i++)
    {
        for (int j = 0; j < cardsPerPlayer; j++)
        {
            // Assigns first X cards in shuffled deck to current player,
            // where X is the amount of cardsPerPlayer
            ptr->hand[j] = deck[deckIndex];
            deckIndex++;
        }

        // Move to next player
        ptr = ptr->next;
    }
}


// Creates a linked list to store all players in the game
// Linked list also serves as representation of turn order, with the last player 
// pointing back to the head of the list
player *createPlayers(int playerCount)
{
    // Players will be stored as a linked list that also represents the turn order
    player *head = NULL;

    for (int i = 0; i < playerCount; i++)
    {
        // Create new player node
        player *n = malloc(sizeof(player));

        // Check for malloc errors
        if (n == NULL)
        {
            printf("Memory allocation error\n");
            return NULL;
        }

        if (head == NULL) {
            head = n;
        }
        else
        {
            player *tmp = head;

            // Traverse to the end of the linked list
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            }

            // Add new node to end of linked list
            tmp->next = n;

            // If current player node is last, set pointer back to head 
            // Else, set pointer of new node to null
            if (i == playerCount - 1)
            {
                n->next = head;
            }
            else
            {
                n->next = NULL;
            }
        }
    }

    return head;
}



// Function that traverses through all players and prints out all their hand cards
void showHand(player* currPlayer)
{
    for (int j = 0; j < 13; j++)
    {
        printf("%i. ", j + 1);
        displayCard(currPlayer->hand[j]);
    }

    printf("\n");
}