#include <stdio.h>
#include <stdlib.h>
#include "zone.h"
#include "clashagain.h"


//////////////////////////////////////////
/*       Initialisation de zone         */
//////////////////////////////////////////

    /*-----------------------------------------------------------------*/

    Tzone creerTzoneVide(void)
    {
        return creerPileVide();
    }

    /*-----------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////
/*                         Ajouter à zone                              */
/////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------*/

    Tzone ajouterUnitedansZone(Tzone z, Tunite *u)
    {
        return empiler(z, u);
    }

    /*-----------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////
/*                         Supprimer de zone                           */
/////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------*/

    Tzone supprimerUnitedansZone(Tzone z,Tunite *u)
    {
        Tunite* uniteASupp = u;
        Tzone unitesANePasSupp = creerTzoneVide();
        bool uniteDansLaPile = false;

        // On cherche si "u" est dans la pile.
        while(!estvide(z) && !uniteDansLaPile)
        {
            Tunite* uniteDeComparaison = tetePile(z);
            z = depiler(z);
            if(uniteDeComparaison != uniteASupp)
            {
                unitesANePasSupp = ajouterUnitedansZone(unitesANePasSupp, uniteDeComparaison);
            }
            else
            {
                uniteDansLaPile = true;
            }
        }
        // Si "u" n'est pas dans le pile alors on affiche un message d'erreur.
        if(!uniteDansLaPile)
        {
            printf("Erreur supprimerUnitedansZone : l\'unite a supprimer n\'est pas dans la pile.\n");
            exit(1);
        }
        // Sinon on remet la pile comme elle était avant mais sans "u".
        else
        {
            retourneTzone(&unitesANePasSupp, &z);
        }
        return z;
    }

    /*-----------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////
/*                         Test de zone                                */
/////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------*/

    bool UniteEstPresentedansZone(Tzone* z, Tunite* u)
    {
        Tunite* uniteATrouver = u;
        Tzone tmp = creerTzoneVide();
        bool uniteDansLaPile = false;

        // On cherche si "u" est dans la pile.
        while(!estvide(*z) && !uniteDansLaPile)
        {
            Tunite* uniteDeComparaison = tetePile(*z);
            *z = depiler(*z);
            tmp = ajouterUnitedansZone(tmp, uniteDeComparaison);
            if(uniteDeComparaison == uniteATrouver)
            {
                uniteDansLaPile = true;
            }
        }
        retourneTzone(&tmp, z);
        return uniteDansLaPile;
    }

    /*-----------------------------------------------------------------*/

    bool UniteAuSolPresente(Tzone* z)
    {
        Tzone tmp = creerTzoneVide();
        bool uniteAuSol = false;

        while(!estvide(*z) && !uniteAuSol)
        {
            Tunite* uniteDeComparaison = tetePile(*z);
            *z = depiler(*z);
            tmp = ajouterUnitedansZone(tmp, uniteDeComparaison);
            // Si on trouve une unité au sol.
            if(uniteDeComparaison->maposition == sol)
            {
                uniteAuSol = true;
            }
        }
        retourneTzone(&tmp, z);
        return uniteAuSol;
    }

    /*-----------------------------------------------------------------*/

    bool UniteEnVolPresente(Tzone* z)
    {
        Tzone tmp = creerTzoneVide();
        bool uniteAir = false;

        while(!estvide(*z) && !uniteAir)
        {
            Tunite* uniteDeComparaison = tetePile(*z);
            *z = depiler(*z);
            tmp = ajouterUnitedansZone(tmp, uniteDeComparaison);
            // Si on trouve une unité dans les airs.
            if(uniteDeComparaison->maposition == air)
            {
                uniteAir = true;
            }
        }
        retourneTzone(&tmp, z);
        return uniteAir;
    }

    /*-----------------------------------------------------------------*/

    bool estvide(Tzone z)
    {
        return estVide(z);
    }

    /*-----------------------------------------------------------------*/

    int lenTzone(Tzone z)
    {
        return hauteurPile(z);
    }

    /*-----------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////
/*                             Modification                            */
/////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------*/

    Tzone getUniteDeCouleur(Tzone* z, Tcouleur couleur)
    {
        Tzone res = creerTzoneVide();
        Tzone tmp = creerTzoneVide();
        while(!estvide(*z))
        {
            Tunite* uniteDeLaPile = tetePile(*z);
            if(uniteDeLaPile->couleur == couleur)
            {
                res = ajouterUnitedansZone(res, uniteDeLaPile);
            }
            *z = depiler(*z);
            tmp = ajouterUnitedansZone(tmp, uniteDeLaPile);
        }
        retourneTzone(&tmp, z);
        return res;
    }

    /*-----------------------------------------------------------------*/

    TListePlayer getAllUnitInZone(Tzone* z)
    {
        TListePlayer l = NULL;
        Tzone tmp = creerTzoneVide();

        while(!estvide(*z))
        {
            Tunite* uniteDeLaPile = tetePile(*z);
            AjouterUnite(&l, uniteDeLaPile);
            *z = depiler(*z);
            tmp = ajouterUnitedansZone(tmp, uniteDeLaPile);
        }
        retourneTzone(&tmp, z);
        return l;
    }

    /*-----------------------------------------------------------------*/

    Tunite* fstTzone(Tzone z)
    {
        if(estvide(z))
        {
            return NULL;
        }
        else
        {
            return tetePile(z);
        }
    }

    /*-----------------------------------------------------------------*/

    void retourneTzone(Tzone* z, Tzone* new_z)
    {
        while(!estvide(*z))
        {
            Tunite* unite = tetePile(*z);
            *new_z = ajouterUnitedansZone(*new_z, unite);
            *z = depiler(*z);
        }
    }

    /*-----------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////
/*                             Affichage                               */
/////////////////////////////////////////////////////////////////////////

    /*-----------------------------------------------------------------*/

    void printTzone(Tzone* z)
    {
        Tzone tmp = creerTzoneVide();
        printf("Affichage zone de len = %d: \n", lenTzone(*z));
        while(!estvide(*z))
        {
            Tunite* fstUnite = tetePile(*z);
            *z = depiler(*z);
            tmp = ajouterUnitedansZone(tmp, fstUnite);
            afficheUneUnite(fstUnite);
        }
        retourneTzone(&tmp, z);
    }

    /*-----------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////

