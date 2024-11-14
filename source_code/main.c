#include "impl.c"
#include "freecell.h"

int main()
{
    //init
    Zone *zone1 = createZone1();
    Zone *zone2 = createZone2();
    Zone *zone3 = createZone3();
    initZone1(zone1);

    //début du jeu
    while(1)
    {
    	system("cls");

        displayBoard(zone1, zone2, zone3);

        if (isZoneEmpty(zone1) && isZoneEmpty(zone2))
        {
            printf("\033[1;32m");
            printf("\nTU AS GAGNE !\n");
            printf("\033[0m");
            break;
        }
        if ( isGameBlocked(zone1, zone2, zone3) )
        {
            printf("\033[1;31m");
            printf("\nPARTIE BLOCKEE !\n");
            printf("\033[0m");
            break;
        }

        printf("\n\n");
        executeMove(zone1, zone2, zone3);
    }
    return 0;
}
