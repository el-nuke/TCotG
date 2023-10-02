#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carta
{
    int ID, HP, AP, DP; //ID, Health, Attack, Defense
    char type[20], name[50];
};

int main(){
    
    FILE *file = fopen("deck.txt", "r");

    if (file == NULL) {
        perror("\nCouldnt find 'deck.txt' \n");
        return 1;
    }

    struct Carta Deck[500];
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