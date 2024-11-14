#include "freecell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>



// Design functions

void setConsoleColor(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textColor | (bgColor << 4));
}

void resetConsoleColor()
{
    setConsoleColor(15, 0); // Set text to white and background to black
}



//Card functions
Card *createCard(int num, char *type)
{
    Card *card = (Card *) malloc(sizeof(Card));
    card->number = num;
    card->type = type;
    return card;
}




void displayCard(Card* card)
{
        int textColor, bgColor;

    if (card->type[0] == 'C') {
        textColor = 12; // Red text for hearts
        bgColor = 15;   // White background
    } else {
        textColor = 0;  // Black text for other suits
        bgColor = 15;   // White background
    }

    setConsoleColor(textColor, bgColor);

    if(card->number < 1 || card->number > 13) {
        printf("Erreur, le nombre doit etre entre 1 et 13 !");
    } else {
        switch (card->number)
        {
            case 1:
                printf("A");
                break;
            case 11:
                printf("J");
                break;
            case 12:
                printf("Q");
                break;
            case 13:
                printf("K");
                break;
            default:
                printf("%d",card->number);
        }
    }



    // En utilisant le code ASCII EXTENDED
    char suitSymbol;
    if (strcmp(card->type, "Co") == 0) {
        suitSymbol = 3; // Heart
    } else if (strcmp(card->type, "Pi") == 0) {
        suitSymbol = 6; // Club
    } else if (strcmp(card->type, "Tr") == 0) {
        suitSymbol = 5; // Diamond
    } else if (strcmp(card->type, "Ca") == 0) {
        suitSymbol = 4; // Spade
    }

    printf("  %c", suitSymbol);

    resetConsoleColor();
}

int isSameColor(Card* card1, Card* card2)
{
    if (card1->type[0] == 'C' && card2->type[0] == 'C') return 1; // Ca | Co
    if (card1->type[0] != 'C' && card2->type[0] != 'C') return 1; // Tr | Pi
    return 0;
}

//StackCards Functions

Element* createElement(Card *card)
{
    Element *element = (Element *)malloc(sizeof(Element));
    element->card = card;
    element->next = NULL;
    return element;
}


StackCards *createStack(char *name)
{
    StackCards *pile = (StackCards *)malloc(sizeof(StackCards));
    pile->head = NULL;
    pile->name = name;
    return pile;
}

void Empiler(StackCards **pile, Card* C)
{
    Element *element ;
	element = createElement(C);
    element->next = (*pile)->head;
    (*pile)->head = element;
}

Card* Depiler(StackCards *pile)
{
    Card* card = pile->head->card;
    Element *tmp = pile->head;
    pile->head = pile->head->next;
    free(tmp);
    return card;
}
void displayStack(StackCards* pile)
{
    Element *tete = pile->head;
    if (strlen(pile->name)==2 && pile->name[0]=='C') // Ca ou Co
        printf("\033[1;31m");
    printf("%s  :  ", pile->name);

    while ( tete != NULL)
    {
        displayCard(tete->card);
        if (tete->next != NULL)
            printf(" | ");
        tete = tete->next;
    }
    printf("\n");

}


//Zone functions

Zone *createZone(int num)
{
    Zone* zone = (Zone *)malloc(sizeof(Zone));
    zone->colsNumber = num ;
    zone->cols = (StackCards **)malloc(sizeof(StackCards*) * num);
    int i;
    for (i = 0 ; i < num ; i++)
    {
        zone->cols[i] = createStack("-");
    }
    return zone;
}

Zone *createZone1()
{
    Zone* zone ;
    zone = createZone(8);
    int i ;
    char* names[] = {"1", "2", "3", "4", "5", "6", "7", "8"};
    for(i=0 ; i<zone->colsNumber ; i++ ){
    	zone->cols[i]->head = NULL ;
    	zone->cols[i]->name = names[i] ;
	}
	return zone;
}

Zone *createZone2()
{

    Zone* zone ;
    zone = createZone(4);
    char* names[] = {"A", "B", "C", "D"};
    int i;
    for (i = 0 ; i < zone->colsNumber ; i++)
    {
        zone->cols[i]->head = NULL;
        zone->cols[i]->name = names[i];
    }
    return zone;
}

Zone *createZone3()
{	int i ;
    Zone* zone ;
    zone = createZone(4);
    char* names[] = {"Ca", "Pi", "Co", "Tr"};
    for (i = 0 ; i < zone->colsNumber ; i++)
    {
        zone->cols[i]->head = NULL;
        zone->cols[i]->name = names[i];
    }
    return zone;
}

void displayZone(Zone* zone)
{
	printf("\n");
    int i;
    for (i = 0; i < zone->colsNumber; i++)
    {
        displayStack(zone->cols[i]);
        printf("\n");
    }
}

int isZoneEmpty(Zone* zone)
{
    int i ;
    for (i=0 ; i < zone->colsNumber ; i++ )
    {
        if ( zone->cols[i]->head != NULL) return 0;
    }
    return 1;
}
void initZone1(Zone* zone1)
{
    srand(time(NULL));
    //créer une liste chainée de toutes les cartes
    char *Types[] = {"Ca", "Co", "Pi", "Tr"};
    int i, j , numOfCards = 52;
    StackCards *cardList = createStack("list");
    for (i=0 ; i<4 ; i++ )
    {
        for ( j=1 ; j<=13 ; j++)
        {
            Card *card = createCard(j, Types[i]);
            Empiler(&cardList, card);
        }
    }

    //selectionner une carte et l'empiler dans la zone 1

    Element *chosenCard = NULL; //pointeur parcourant la liste cherchant la carte selectionnée
    Element *previous = NULL;

    for ( i = 0; i<52; i++)
    {
        chosenCard = cardList->head;
        j = rand()%numOfCards; // nombre entre 0 et 51
        if (j == 0)
        {
            cardList->head = cardList->head->next;
        }
        else
        {
            while (j>0)
            {
                if (j == 1)
                {
                    previous = chosenCard;
                }
                chosenCard = chosenCard->next;
                j-- ;
            }
            previous->next = chosenCard->next;
        }
        numOfCards--; // assurer que le j est selectionnée dans un intervalle adéquat

        Empiler(&zone1->cols[i%8], chosenCard->card); // Il ya 8 piles dans la zone 1
        free(chosenCard);
    }

}


//Movement functions

void move(StackCards *depart, StackCards *arrive)
{
    if (depart->head == NULL)
    {
        printf("Erreur: depart est vide\n");
        return;
    }
    Card *card = Depiler(depart);
    Empiler(&arrive, card);
}

StackCards* wantedStack(char * text, Zone* z1, Zone* z2, Zone* z3)
{
    int i = text[0]-'1';
    if (strlen(text)==1 && i >= 0 && i < 8) // number(zone1)
    {
        return z1->cols[i];
    }
    i = text[0]-'A';
    if (strlen(text)==1 && i>=0 && i<4)
    {
        return z2->cols[i];
    }
    if (strcmp(text, "Ca") == 0)    return z3->cols[0];
    if (strcmp(text, "Pi") == 0)    return z3->cols[1];
    if (strcmp(text, "Co") == 0)    return z3->cols[2];
    if (strcmp(text, "Tr") == 0)    return z3->cols[3];

    return NULL;
}

void executeMove(Zone* z1, Zone* z2, Zone* z3)
{
    char text[2];
    StackCards *depart, *arrive;

    printf("Depart (Nom de la pile): ");
    scanf("%s", text);
    depart = wantedStack(text, z1, z2, z3);

    printf("Arrivee (Nom de la pile): ");
    scanf("%s", text);
    arrive = wantedStack(text, z1, z2, z3);

    if (depart == NULL )
    {
        printf("Erreur : colonne de depart invalide\n");
        return;
    }
    if ( arrive == NULL)
    {
        printf("Erreur : colonne arrivee invalide \n");
        return;
    }
    if (isValideMove(depart, arrive))
        move(depart, arrive);
}

int isValideMove(StackCards *depart, StackCards *arrive)
{
    //la pile est vide
    if ( depart->head == NULL)
        return 0;

    //le départ ne peut pas être dans la zone 3
    if (!strcmp(depart->name, "Ca") || !strcmp(depart->name, "Pi") ||
        !strcmp(depart->name, "Co") || !strcmp(depart->name, "Tr"))
        return 0;

    //la pile d'arrivée est dans la zone3
    if (!strcmp(arrive->name, "Ca") || !strcmp(arrive->name, "Pi") ||
        !strcmp(arrive->name, "Co") || !strcmp(arrive->name, "Tr"))
    {
        // Vérification du type
        if ( strcmp( depart->head->card->type, arrive->name ) == 0)
        {
            // s'il ya une carte dans la pile d'arrivée
            if ( (arrive->head != NULL) &&
                depart->head->card->number == arrive->head->card->number + 1 )
                return 1;
            // pile d'arrivée vide
            else if (( arrive->head == NULL) && depart->head->card->number == 1 )
                return 1;
            else
                return 0;
        }
        else
            return 0;
    }

    // pile d'arrivée dans zone 2
    if ( strlen(arrive->name) == 1 &&
        arrive->name[0]-'A' >= 0 && arrive->name[0]-'A' < 4 )
    {
        if ( arrive->head != NULL ) return 0;
        return 1;
    }

    //pile d'arrivée dans zone 1
    if ( strlen(arrive->name) == 1 &&
        arrive->name[0]-'1' >= 0 && arrive->name[0]-'1' < 8 )
    {
        //pile vide
        if ( arrive->head == NULL )    return 1;

        //carte de couleur différente avec ordre
        if ( ! isSameColor(depart->head->card, arrive->head->card) &&
            depart->head->card->number  == arrive->head->card->number - 1 )
            return 1;

        return 0;
    }

}

void displayBoard(Zone *z1, Zone *z2, Zone *z3)
{	printf("------------------------------------------------------------------------------------- Mohammed Benaissa -------------------------------------------------------------------------------------");

	printf("\n\n");

	printf("************* ZONE 2 ************* \n") ;
    displayZone(z2);
    printf("\n");
    printf("************* ZONE 3 ************* \n") ;
    displayZone(z3);
    printf("\n");
    printf("************* ZONE 1 ************* \n") ;
    displayZone(z1);
}

int isStackBlocked(StackCards *pile, Zone* z1, Zone* z2, Zone* z3)
{
    int i ;
    if ( strlen(pile->name) == 2 )  return 1; //piles de zone 3

    for ( i=0 ; i<z1->colsNumber; i++)
    {
        if (isValideMove(pile, z1->cols[i]))    return 0;
    }
    for ( i=0 ; i<z2->colsNumber; i++)
    {
        if (isValideMove(pile, z2->cols[i]))    return 0;
    }
    for ( i=0 ; i<z3->colsNumber; i++)
    {
        if (isValideMove(pile, z3->cols[i]))    return 0;
    }
    return 1;
}

int isGameBlocked(Zone* z1, Zone* z2, Zone* z3)
{
    int i = 0;
    for ( i=0 ; i<z1->colsNumber; i++)
    {
        if ( isStackBlocked( z1->cols[i], z1, z2, z3) == 0)    return 0;
    }
    for ( i=0 ; i<z2->colsNumber; i++)
    {
        if ( isStackBlocked( z2->cols[i], z1, z2, z3) == 0)    return 0;
    }

    return 1;
}

