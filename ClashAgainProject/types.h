#ifndef TYPES_H_INCLUDED
#define TYPES_H_INCLUDED

typedef enum{tour, tourRoi, archer, chevalier, dragon, gargouille} TuniteDuJeu;
typedef enum{sol, solEtAir, air } Tcible;
typedef enum{bleu, rouge} Tcouleur;


typedef struct {
    TuniteDuJeu nom;
    Tcible cibleAttaquable;	//indique la position des unités que l’on peut attaquer
    Tcible maposition;		//indique soit « air » soit « sol », utile pour savoir
                            //qui peut nous attaquer
    int pointsDeVie;
    float vitesseAttaque;	//en seconde, plus c’est petit plus c’est rapide
    int degats;
    int portee ;			//en mètre, distance sur laquelle on peut atteindre une
                            //cible

    float vitessedeplacement;	//en m/s
    int posX, posY;			//position sur le plateau de jeu
    int peutAttaquer;		//permet de gérer le fait que chaque unité attaque une
                            //seule fois par tour ;
                            //0 = a déjà attaqué, 1 = peut attaquer ce tour-ci
                            // à remettre à 1 au début de chaque tour
    int coutEnElixir;
    Tcouleur couleur;
} Tunite;

typedef struct T_cell{
    struct T_cell *suiv;
    Tunite *pdata; //pointeur vers une unité
} ListePlayer, *TListePlayer;

typedef struct Tpos
{
    int x;
    int y;
}Tpos;

typedef struct {
    TListePlayer listeU;  //la liste des unités du joueur
    int elixir;
    Tcouleur couleurJoueur;
} TPlayer;

#endif // TYPES_H_INCLUDED
