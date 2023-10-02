#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Card
{
    int ID; 
    int HP; //Health Points
    int AP; //Attack Points
    int DP; //Defense Points
    char type[20], name[50];
};

int main(){
    
    FILE *file = fopen("deck.txt", "r");

    if (file == NULL) { //If theres no deck.txt, theres no cards to load, and no game.
        perror("\nCouldnt find 'deck.txt' \n");
        return 1;
    }

    struct Card Deck[500];
    int ccount=0;

    while (fscanf(file, "%s,%s,%d,%d,%d", Deck[ccount].name, Deck[ccount].type, &Deck[ccount].HP, &Deck[ccount].AP, &Deck[ccount].DP == 5))
    {
        ccount++;

        if(ccount >= 500){
            printf("\nMax deck size reached! (500)");
            break;
        }
    }

    printf("\n%d cards loaded into the deck and ready to go!", ccount);
}