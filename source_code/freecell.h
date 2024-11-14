#ifndef FREECELL_H
#define FREECELL_H


typedef struct {
	int number ;
	char* type ;
}Card;

typedef struct element{
	Card* card ;
	struct element* next ;
}Element;

typedef struct
{
    Element *head ;
    char* name ;
}StackCards;

typedef struct zone
{
    StackCards **cols;
    int colsNumber;
} Zone;

//Design functions

void setConsoleColor(int textColor, int bgColor);
void resetConsoleColor();

//Card functions

Card *createCard(int num, char *type);
void displayCard(Card* card);
int isSameColor(Card* card1, Card* card2);

//StackCards functions

Element* createElement(Card *card);
StackCards *createStack(char *name);
void Empiler(StackCards** pile, Card* C);
Card* Depiler(StackCards *pile);
void displayStack(StackCards* pile);

//Zone functions

Zone *createZone(int num);
Zone *createZone1();
Zone *createZone2();
Zone *createZone3();
void displayZone(Zone* zone);
int isZoneEmpty(Zone* zone);
void initZone1(Zone* zone1);

//Movement functions

void move(StackCards *depart, StackCards *arrive);
StackCards* wantedStack(char * text, Zone* z1, Zone* z2, Zone* z3);
void executeMove(Zone* z1, Zone* z2, Zone* z3);
int isValideMove(StackCards *depart, StackCards *arrive);

//Game functions

void displayBoard(Zone *z1, Zone *z2, Zone *z3);
int isStackBlocked(StackCards *pile, Zone* z1, Zone* z2, Zone* z3);
int isGameBlocked(Zone* z1, Zone* z2, Zone* z3);


#endif // FREECELL_H_INCLUDED















