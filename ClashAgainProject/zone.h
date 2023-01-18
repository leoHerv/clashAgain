#ifndef ZONE_H_INCLUDED
#define ZONE_H_INCLUDED

    #include "piles.h"

    typedef pile Tzone;

//////////////////////////////////////////
/*       Initialisation de zone         */
//////////////////////////////////////////

    // Crée une Tzone vide.
    Tzone creerTzoneVide(void);

//////////////////////////////////////////
/*           Ajouter à zone             */
//////////////////////////////////////////

    // Ajoute une unité à une Tzone.
    Tzone ajouterUnitedansZone(Tzone z, Tunite *u);

//////////////////////////////////////////
/*           Supprimer de zone          */
//////////////////////////////////////////

    // Supprime une unité d'une Tzone.
    Tzone supprimerUnitedansZone(Tzone z,Tunite *u);

//////////////////////////////////////////
/*            Test de zone              */
//////////////////////////////////////////

    // Regarde si u est dans la Tzone.
    bool UniteEstPresentedansZone(Tzone* z, Tunite* u);

    // Regarde si il y a des unités au sol dans la Tzone.
    bool UniteAuSolPresente(Tzone* z);

    // Regarde si il y a des unités dans les airs dans la Tzone.
    bool UniteEnVolPresente(Tzone* z);

    // Regarde si la Tzone est vide.
    bool estvide(Tzone z);

    // Regarde la longueur de la Tzone.
    int lenTzone(Tzone z);

//////////////////////////////////////////
/*            Modification              */
//////////////////////////////////////////

    // Donne une Tzone avec des unités qui on la même couleur qu'en paramètre.
    Tzone getUniteDeCouleur(Tzone* z, Tcouleur couleur);

    // Transforme un Tzone en TListePlayer.
    TListePlayer getAllUnitInZone(Tzone* z);

    // Donne le premier element de la Tzone.
    Tunite* fstTzone(Tzone z);

    // Retourne une Tzone.
    void retourneTzone(Tzone* z, Tzone* new_z);

//////////////////////////////////////////
/*              Affichage               */
//////////////////////////////////////////

    // Affiche la Tzone.
    void printTzone(Tzone* z);

//////////////////////////////////////////


#endif // ZONE_H_INCLUDED
