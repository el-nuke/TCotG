#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

struct Card
{
    int ID;
    int HP; //Health Points
    int AP; //Attack Points
    int DP; //Defense Points
    char type[20], name[50];
};

struct Player
{
    int HP; //def. 5
    char name[3];
    struct Card Deck[15], Hand[15], Table[15];
};

//Stores necesary data for History logs
struct TurnLog
{
    char string[50];
    int turnType; // 0 = None (Reads string), 1 = Placed card, 2 = Attacked, 3 = Defeated
    int playerID; // 1 = User, 2 = CPU
    int attackerID, targetID; // Card's IDs
    int damageDealt, turn;

    //0 = {string}
    
    //1 = Turn {turn} : {playerID} placed {attackerID.name} [HP: {attackerID.HP}][AP: {attackerID.AP}][DP: {attackerID..DP}]

    //2 = Turn {turn} : {playerID} picked {attackerID.name} to attack {targetID.name} and dealt {damagedealt}.

    //3 = Turn {turn} : {playerID} picked {attackerID.name} to defeat {targetID.name}
};

//Shows a single card (for gameplay purposes)
void showCard(struct Card show){ 
    //printf("\n{ID: %d}", show.ID);
    printf("\n[%s] [%s] [HP:%d][AP:%d][DP:%d]", show.name, show.type, show.HP, show.AP, show.DP);
    return;
}

//Creates a card with the provided variables
void createCard(struct Card *Deck, int ccount, char _name[50], char _type[50], int _HP, int _AP, int _DP){ 

    struct Card ncard = {ccount, _HP, _AP, _DP};
    strcpy(ncard.name, _name);
    strcpy(ncard.type, _type);

    Deck[ccount] = ncard;

    return;
}

//Lets user create a custom card step by step
void yourOwnCard(struct Card *Deck, int ccount){ 
    if (ccount >= 500){
        printf("Max deck size reached, can't add any more cards");
        return;
    }

    ccount++;
    
    char _name[50], _type[50];
    int _HP,_AP,_DP;

    printf("\n++ Creating a new card ++");

    printf("\nName: ");
    scanf("%s", _name);

    printf("\nType: ");
    scanf("%s", _type);

    printf("\nHealth Points: ");
    scanf("%d", &_HP);

    printf("\nAttack Points: ");
    scanf("%d", &_AP);

    printf("\nDefense Points: ");
    scanf("%d", &_DP);

    createCard(Deck, ccount, _name, _type, _HP, _AP, _DP);
    
    printf("\nSuccesfully created and added %s to the deck!", Deck[ccount].name);

    return;
}

//Main game loop, most of the game happens here
void gameLoop(struct Player User, struct Player CPU){
    for (int c = 0; c<30; c++){
        if (User.Deck[c].ID != 0){showCard(User.Deck[c]);}
    }
}

//Game setup: Shuffles deck, creates and sets players and deals cards
void gameStart(struct Card *Deck, int ccount){
    struct Card aux;
    int x, y;
    for (int c=0;c<250;c++){
		do{
            x = rand() % ccount;
		    y = rand() % ccount;
        }while (Deck[x].ID == 0 || Deck[y].ID == 0 || x == y);
        		
        aux = Deck[x];
		Deck[x] = Deck[y];
		Deck[y] = aux;
    }
    
    struct Player User;
    strcpy(User.name, "YOU");
    User.HP = 5;
    struct Player CPU;
    strcpy(CPU.name, "CPU");
    CPU.HP = 5;
    
    for(int c=0; c<15; c++){
        User.Deck[c].ID = 0;
        User.Hand[c].ID = 0;
        User.Table[c].ID = 0;
        CPU.Deck[c].ID = 0;
        CPU.Hand[c].ID = 0;
        CPU.Table[c].ID = 0;
    }

    for (int c=0; c<30; c = c+2){
        User.Deck[c] = Deck[c];
        CPU.Deck[c+1] = Deck[c+1];
    }
    for (int c=0; c<3; c++){
        User.Hand[c] = User.Deck[c];
        User.Deck[c].ID = 0;
        CPU.Hand[c] = CPU.Deck[c];        
        CPU.Deck[c].ID = 0;
    }
    
    gameLoop(User, CPU);

    return;
}

int main(){
    system("cls");
    srand(time(NULL));

    struct TurnLog History[100];
    struct Card Deck[500], DeckCopy[500];
    for (int c; c<500; c++){
        Deck[c].ID = 0;
    }
    int ccount=0;    
    FILE *file = fopen("deck.txt", "r");
    if (file == NULL) {
        perror("\nCouldnt find 'deck.txt' \n");
        //return 1;
    }else{        
        printf("\nFound 'deck.txt' to load cards from!");
        char line[100];
        
        while (fgets(line, 200, file) != NULL)
        {
            if(ccount >= 500){
                printf("\nMax deck size reached! (500)");
                break;
            }

            char *token;
            
            token = strtok(line, ",");
            char _name[50];
            strcpy(_name, token);

            token = strtok(NULL, ",");
            char _type[50];
            strcpy(_type, token);
            
            int _HP = atoi(strtok(NULL, ","));
            int _AP = atoi(strtok(NULL, ","));
            int _DP = atoi(strtok(NULL, ","));


            createCard(Deck, ccount, _name, _type, _HP, _AP, _DP);
            ccount++;
        }
        fclose(file);

        printf("\n%d cards loaded into the deck!\n\n", ccount);
    }
    
    system("pause");
    system("cls");

    
    int option;

    do
    {
        printf("\n\t--[ THE CLASH OF THE GUARDIANS ]--");
        printf("\n\n1: Create a card");
        printf("\n2: Start game");
        printf("\n3: Check history");
        printf("\n4: Quit");
        printf("\n\nChoose an option: ");

        scanf("%d", &option);

        switch (option)
        {
            case 1: //Create a card
                yourOwnCard(Deck, ccount);
                break;

            case 2: //Start game
                for (int c=0; c<500; c++){
                    DeckCopy[c] = Deck[c];      // Game receives a copy of the deck so the cards can be modified
                }                               // during gameplay without affecting the original deck.
                gameStart(DeckCopy, ccount);    // The original deck stays the same so it can later be used for History logs.
                break;

            case 3: //Check history
                //checkhistory(); WIP
                break;

            case 4: //Quit
                printf("Closing program...");
                option = 8008;
                return 0;

            case 1337:
                printf("\nPunch a card ID: ");
                scanf("%d", &option);
                showCard(Deck[option]);

                break;

            default:
                break;
        }

    } while (option != 8008);

    return 0;
}