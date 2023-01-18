#ifndef CLASHAGAIN_H_INCLUDED
#define CLASHAGAIN_H_INCLUDED

#include "zone.h"
#include "types.h"

//////////////////////////////////////////
/*          Types et defines            */
//////////////////////////////////////////

    #define LARGEURJEU 11
    #define HAUTEURJEU 19

    #define NOMBRE_DE_TROUPES 6

    //le plateau du jeu pour l'affichage (reprise du systreme du projet clashLoyal)
    typedef Tunite* **TplateauJeu;

    //tableau a deux dimensions de largeur 11 et hauteur 19 contenant des Tzone
    typedef Tzone **TplateauJeuUpgrade;

///////////////////////////////////////
/*               Liste               */
///////////////////////////////////////

    // Retourne une TListePlayer vide.
    TListePlayer creerListeVide(void);

     // Retourne vrai ou faux si la TListePlayer est vide ou pas.
    bool PlayerEstVide(TListePlayer L);

    // Ajoute une valeur devant la TListePlayer.
    TListePlayer add_fst(TListePlayer L, Tunite* u);

    // Ajoute une valeur derière la TListePlayer.
    TListePlayer add_lst(TListePlayer L, Tunite* u);

    // Retire le premier element de la TListePlayer.
    TListePlayer rem_fst(TListePlayer L);

    // Donne le premier element de la TListePlayer.
    Tunite* fst(TListePlayer L);

    // Donne le nombre d'elements qu'il y a dans la liste.
    int len(TListePlayer L);

    // Vide une TListePlayer.
    TListePlayer clearList(TListePlayer L);

    // On fusionne les deux liste.
    TListePlayer concatList(TListePlayer L1, TListePlayer L2);

    // On inverse la place de deux unités.
    void swapUnite(TListePlayer l1, TListePlayer l2);

    // Fait une copie d'une TListePlayer.
    TListePlayer copieList(TListePlayer L);

//////////////////////////////////////////
/*                Random                */
//////////////////////////////////////////

    // Initialise la randomisation.
    void initRandom(void);

    // Donne un nombre random entre min et max.
    int random_int(int min, int max);

//////////////////////////////////////////
/*             Allocations              */
//////////////////////////////////////////

    // Alloue un tableau 2D de liste d'unités du jeu.
    TplateauJeuUpgrade AlloueTab2D_Tzone(int largeur, int hauteur);

    // Alloue un tableau 2D de pointeurs sur des unités du jeu.
    TplateauJeu AlloueTab2D(int largeur, int hauteur);

    // Alloue une unité.
    Tunite* creeUnite(TuniteDuJeu nom, Tcible cibleAttaquable, Tcible maposition, int pointsDeVie,
                      float vitesseAttaque, int degats, int portee, float vitessedeplacement,
                      int posX, int posY, int peutAttaquer, int coutEnElixir, Tcouleur couleur);

    // Alloue une unité "Tour".
    Tunite* creeTour(int posx, int posy, Tcouleur couleur);

    // Alloue une unité "Tour du Roi".
    Tunite* creeTourRoi(int posx, int posy, Tcouleur couleur);

    // Alloue une unité "Archer".
    Tunite* creeArcher(int posx, int posy, Tcouleur couleur);

    // Alloue une unité "Gargouille".
    Tunite* creeGargouille(int posx, int posy, Tcouleur couleur);

    // Alloue une unité "Dragon".
    Tunite* creeDragon(int posx, int posy, Tcouleur couleur);

    // Alloue une unité "Chevalier".
    Tunite* creeChevalier(int posx, int posy, Tcouleur couleur);

//////////////////////////////////////////
/*         Ajout / Initialisation       */
//////////////////////////////////////////

    // Initialise un player avec une "tour", une "tour du roi" et une couleur.
    TPlayer initPlayer(Tcouleur couleur);

    // Initialise le tableau en début de partie.
    void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur);

    // Initialise le tableauUpgrade avec des Tzone vide.
    void initPlateauUpgradeAvecNULL(TplateauJeuUpgrade jeu,int largeur, int hauteur);

    // Ajoute une unité à la liste d'unité d'un joueur.
    void AjouterUnite(TListePlayer* player, Tunite* nouvelleUnite);

    // Essaye de trouver une position pour une unité et renvoie true si la position est bonne sinon false.
    bool findPosForUnite(Tcouleur couleur, Tpos* pos, TplateauJeuUpgrade jeuUpgrade, bool tourDetruite, Tcible positionUnite);

    // Ajoute une unité à la liste d'unité d'un joueur.
    void AjouterUnite(TListePlayer* player, Tunite* nouvelleUnite);

    // Modifie la position d'une troupe.
    void addPosToUnite(Tunite* unite, Tpos pos);

    // Donne ou non une unité en fonction du nombre d'elixir du joueur.
    Tunite* AcheteUnite(TPlayer* player);

//////////////////////////////////////////
/*            Modification              */
//////////////////////////////////////////

    //void PositionnePlayerOnPlateau(TListePlayer player, TplateauJeu jeu)  //AVANT
    void PositionnePlayerOnPlateau_Upgade(TListePlayer player, TplateauJeuUpgrade jeuUpgrade);

    // Converti un plateau en 3D en 2D.
    void ConversionEnTplateauJeu(TplateauJeuUpgrade jeuEncours, TplateauJeu jeuEn2D);

    // Donne la liste des unités que peuvent attaquer une unité selon sa position(dans les airs, sol ...).
    TListePlayer quiEstAPortee_position(Tunite* uneUniteQuiAttaque, TListePlayer toutesUniteDansLeRayonDeLUnite);

    // Donne toutes les unités qui sont à portée de "uneUniteQuiAttaque".
    TListePlayer quiEstAPortee_Upgrade(TplateauJeuUpgrade jeuEncours, Tunite* uneUniteQuiAttaque);

    // Compare le champ "vitesseAttaque" dans l'ordre croissant.
    bool compareUnite_vitesseAttaque_croi(Tunite* u1, Tunite* u2);

    // Compare le champ "pointsDeVie" dans l'ordre croissant.
    bool compareUnite_pointsDeVie_croi(Tunite* u1, Tunite* u2);

    // Tri un liste d'unités en fonction de ce que l'on veut comparer.
    void triList(TListePlayer* l, bool (*fcomparaison)(Tunite* a, Tunite* b));

    // Divise "listeADivise" en deux liste "pBleu" et "pRouge", en fonction de la couleur de l'unité.
    void diviseListeFoncCouleur(TListePlayer* listeADivise, TListePlayer* pBleu, TListePlayer* pRouge);

    // Fait le combat entre les deux joueurs.
    void combatJoueurs(TPlayer* player1, TPlayer* player2, TplateauJeuUpgrade jeuEncours);

    // Remet à toutes les unités d'une liste la possibilité d'attaquer.
    void resetPeutAttaquer(TPlayer* player);

    // Ajoute un nombre d'elixir à un joueur.
    void addElixirToPlayer(TPlayer* player);

    // Modifie le tableau de jeu pour deplacer une unité de sa position vers une autre.
    void changeUnitePosInMap(Tunite* unite, Tpos pos, TplateauJeuUpgrade jeuUpgrade);

    // On modifie la position d'une unité qui peut encore attaquer(elle converge vers le centre de la map et avance).
    void modifPosUnitePeutAttaquer(Tcouleur couleur, Tunite* unite, TplateauJeuUpgrade jeuUpgrade);

    // On fait avancer toutes les unités d'un joueur qui peuvent encore attaquer.
    void modifPosUnitesPlayer(TPlayer* player, TplateauJeuUpgrade jeuUpgrade);

    // Permet d'ajouter aléatoirement une unité à un joueur.
    void addUniteToPlayer(TPlayer* player, TplateauJeuUpgrade jeuUpgrade, bool* tourPlayerDetruite);

    // Permet d'ajouter une unité à un joueur grace à la fonction de création de l'unité donnée en paramètre.
    void addSpecifiqueUniteToPlayer(TPlayer* player, TplateauJeuUpgrade jeuUpgrade, bool* tourPlayerDetruite, Tunite* (creeUnite)(int x, int y , Tcouleur c), bool* modif);

    // Donne la couleur inverse à la couleur donné en entrée.
    Tcouleur couleurInverse(Tunite unite);

    // Donne la couleur d'unite en une chaine de caractère.
    char* couleurUnite(Tunite unite);

    // Donne une fonction de comparaison en fonction du Tcible de l'unité.
    bool (*fonctionComparaisonUnite(Tcible positionUnite))(Tzone* z);

//////////////////////////////////////////
/*             Suppression              */
//////////////////////////////////////////

    // Supprime une unité de la liste d'unités d'un joueur.
    void supprimerUnite(TListePlayer* player, Tunite* UniteDetruite);

//////////////////////////////////////////
/*             Verification             */
//////////////////////////////////////////

    // Regarde si la "Tour du Roi" est detruite (true : oui, false : non).
    bool tourRoiDetruite(TListePlayer player);

    // Regarde si la "Tour" est detruite (true : oui, false : non).
    bool tourDetruite(TListePlayer player);

    // Permet de savoir si une unité peut attaquer ou non une autre unité.
    bool peutAttaquer(Tunite* uniteQuiAttaque, Tunite* uniteQuiDefend);

    // Permet de savoir si une position X Y est (largeur, hauteur) est dans la map du jeu ou pas.
    bool posInMap(int x, int y, int largeur, int hauteur);

//////////////////////////////////////////
/*           Affichage Console          */
//////////////////////////////////////////

    // Affiche le plateau dans la console avec les noms des unités et rien s'il n'y en a pas.
    void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur);

    // Affiche le nom et la vitesse d'attaque d'une unité.
    void afficheUneUnite(Tunite* unite);

    // Affiche une TListePlayer avec le nom et la vitesse d'attaque.
    void afficheListeUnites(TListePlayer player, const char* nomPlayer);

    // Reaffiche le nombre d'elixir des deux joueurs
    void reafficheNbElixir(TPlayer p1, TPlayer p2);

//////////////////////////////////////////

#endif // CLASHAGAIN_H_INCLUDED
