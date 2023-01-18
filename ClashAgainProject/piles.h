#ifndef PILES_H_INCLUDED
#define PILES_H_INCLUDED

#include <stdbool.h>
#include "types.h"


typedef struct cellule {
    Tunite* elem;            //PILE DE TUNITE
    struct cellule *suiv;
} *pile;

pile creerPileVide();
int estVide(pile p);
pile empiler(pile p, Tunite* c);
pile depiler(pile p);
int hauteurPile(pile p);
Tunite* tetePile(pile p);

#endif // PILES_H_INCLUDED
