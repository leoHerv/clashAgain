#include "SDL.h"
#include "clashagain.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h"

#include "zone.h"
#include "types.h"

//////////////////////////////////////////////////////////////////
/*                           Liste                              */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    TListePlayer creerListeVide(void)
    {
        return NULL;
    }

    /*----------------------------------------------------------*/

    bool PlayerEstVide(TListePlayer L)
    {
        return L == NULL;
    }

    /*----------------------------------------------------------*/

    TListePlayer add_fst(TListePlayer L, Tunite* u)
    {
        TListePlayer fst = (TListePlayer) malloc(sizeof(ListePlayer)); //struct T_cell = ListePlayer

        fst->pdata = u;
        fst->suiv = L;
        return fst;
    }

    /*----------------------------------------------------------*/

    TListePlayer add_lst(TListePlayer L, Tunite* u)
    {
        TListePlayer lst = (TListePlayer) malloc(sizeof(ListePlayer)); //struct T_cell = ListePlayer

        lst->pdata = u;
        lst->suiv = NULL;
        if(PlayerEstVide(L)) // Si la liste est vide alors L = lst.
        {
            return lst;
        }
        else // Sinon on va à la fin de la liste et on met lst.
        {
            TListePlayer tmp = L;
            while(tmp->suiv != NULL)
            {
                tmp = tmp->suiv;
            }
            tmp->suiv = lst;
            return L;
        }
    }

    /*----------------------------------------------------------*/

    TListePlayer rem_fst(TListePlayer L)
    {
        if(PlayerEstVide(L)) //Si la liste est vide alors elle reste vide.
        {
            return NULL;
        }
        else // Sinon on enlève et libère le premier element.
        {
            TListePlayer suiv = L->suiv;
            free(L);
            L = NULL;
            return suiv;
        }
    }

    /*----------------------------------------------------------*/

    Tunite* fst(TListePlayer L)
    {
        return L->pdata;
    }

    /*----------------------------------------------------------*/

    int len(TListePlayer L)
    {
        int len = 0;
        TListePlayer tmp = L;
        while(!PlayerEstVide(tmp))
        {
            len++;
            tmp = tmp->suiv;
        }
        return len;
    }

    /*----------------------------------------------------------*/

    TListePlayer clearList(TListePlayer L)
    {
        while(!PlayerEstVide(L)) // Tant que la liste n'est pas vide on enleve le premier element.
        {
             L = rem_fst(L);
        }
        return L;
    }

    /*----------------------------------------------------------*/

    TListePlayer concatList(TListePlayer L1, TListePlayer L2)
    {
        if(PlayerEstVide(L1) && PlayerEstVide(L2))
        {
            return creerListeVide();
        }
        else if(PlayerEstVide(L1))
        {
            return L2;
        }
        else if(PlayerEstVide(L2))
        {
            return L1;
        }
        else
        {
            TListePlayer new_list = creerListeVide();
            while(!PlayerEstVide(L1))
            {
                new_list = add_fst(new_list, fst(L1));
                L1 = L1->suiv;
            }
            while(!PlayerEstVide(L2))
            {
                new_list = add_fst(new_list, fst(L2));
                L2 = L2->suiv;
            }
            return new_list;
        }
    }

    /*----------------------------------------------------------*/

    void swapUnite(TListePlayer l1, TListePlayer l2)
    {
        Tunite* u1 = l1->pdata;
        l1->pdata = l2->pdata;
        l2->pdata = u1;
    }

    /*----------------------------------------------------------*/

    TListePlayer copieList(TListePlayer L)
    {
        TListePlayer copie = creerListeVide();
        TListePlayer tmp = L;
        while(!PlayerEstVide(tmp)) // On fait une copie de la liste L mais à l'envers.
        {
            copie = add_fst(copie, fst(tmp));
            tmp = tmp->suiv;
        }
        TListePlayer copieReverse = creerListeVide();
        while(!PlayerEstVide(copie)) // On inverse la copie pour qu'elle soit dans le bon sens.
        {
            copieReverse = add_fst(copieReverse, fst(copie));
            copie = copie->suiv;
        }
        return copieReverse;
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                           Random                             */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void initRandom(void)
    {
        srand(time(NULL));
    }

    /*----------------------------------------------------------*/

    int random_int(int min, int max)
    {
        return min + rand() % (max+1 - min);
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                           Allocations                        */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    TplateauJeuUpgrade AlloueTab2D_Tzone(int largeur, int hauteur)
    {
        TplateauJeuUpgrade jeu;
        jeu = (Tzone**)malloc(sizeof(Tzone*)*largeur);
        for (int i=0;i<largeur;i++)
        {
            jeu[i] = (Tzone*)malloc(sizeof(Tzone)*hauteur);
        }
        return jeu;  //tab2D contenant des pointeurs
    }

    /*----------------------------------------------------------*/

    TplateauJeu AlloueTab2D(int largeur, int hauteur)
    {
        TplateauJeu jeu;
        jeu = (Tunite***)malloc(sizeof(Tunite**)*largeur);
        for (int i=0;i<largeur;i++)
        {
            jeu[i] = (Tunite**)malloc(sizeof(Tunite*)*hauteur);
        }
        return jeu;  //tab2D contenant des pointeurs
    }

    /*----------------------------------------------------------*/

    Tunite* creeUnite(TuniteDuJeu nom, Tcible cibleAttaquable, Tcible maposition, int pointsDeVie,
                      float vitesseAttaque, int degats, int portee, float vitessedeplacement,
                      int posX, int posY, int peutAttaquer, int coutEnElixir, Tcouleur couleur)
    {
        Tunite* nouv = (Tunite*)malloc(sizeof(Tunite));
        nouv->nom = nom;
        nouv->cibleAttaquable = cibleAttaquable;
        nouv->maposition = maposition;
        nouv->pointsDeVie = pointsDeVie;
        nouv->vitesseAttaque = vitesseAttaque;
        nouv->degats = degats;
        nouv->portee = portee;
        nouv->vitessedeplacement = vitessedeplacement;
        nouv->posX = posX;
        nouv->posY = posY;
        nouv->peutAttaquer = peutAttaquer;
        nouv->coutEnElixir = coutEnElixir;
        nouv->couleur = couleur;
        return nouv;
    }

    /*----------------------------------------------------------*/

    Tunite* creeTour(int posx, int posy, Tcouleur couleur)
    {
        // nom /cibleAttaquable /maposition /pointsDeVie /vitesseAttaque /degats /portee /vitessedeplacement /posX /posY /peutAttaquer /coutEnElixir.
        return creeUnite(tour, solEtAir, sol, 1000, 1.0, 40, 3, 0., posx, posy, 0, 0, couleur);
    }

    /*----------------------------------------------------------*/

    Tunite* creeTourRoi(int posx, int posy, Tcouleur couleur)
    {
        return creeUnite(tourRoi, solEtAir, sol, 1200, 1.2, 50, 4, 0., posx, posy, 0, 0, couleur);
    }

    /*----------------------------------------------------------*/

    Tunite* creeArcher(int posx, int posy, Tcouleur couleur)
    {
        return creeUnite(archer, solEtAir, sol, 60, 0.7, 120, 3, 1., posx, posy, 0, 2, couleur);
    }

    /*----------------------------------------------------------*/

    Tunite* creeGargouille(int posx, int posy, Tcouleur couleur)
    {
        return creeUnite(gargouille, solEtAir, air, 80, 0.6, 90, 1, 3., posx, posy, 0, 1, couleur);
    }

    /*----------------------------------------------------------*/

    Tunite* creeDragon(int posx, int posy, Tcouleur couleur)
    {
        return creeUnite(dragon, solEtAir, air, 200, 1.1, 70, 2, 2., posx, posy, 0, 3, couleur);
    }

    /*----------------------------------------------------------*/

    Tunite* creeChevalier(int posx, int posy, Tcouleur couleur)
    {
        return creeUnite(chevalier, sol, sol, 400, 1.5, 250, 1, 2., posx, posy, 0, 4, couleur);
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                    Ajout / Initialisation                    */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    TPlayer initPlayer(Tcouleur couleur)
    {
        TPlayer p;
        p.listeU = creerListeVide();
        // Joueur en bas de la map.
        if(couleur == bleu)
        {
            AjouterUnite(&p.listeU, creeTour(5, 15, couleur));
            AjouterUnite(&p.listeU, creeTourRoi(5, 17, couleur));
        }
        // Joueur en haut de la map.
        else
        {
            AjouterUnite(&p.listeU, creeTour(5, 3, couleur));
            AjouterUnite(&p.listeU, creeTourRoi(5, 1, couleur));
        }
        p.elixir = 0;
        p.couleurJoueur = couleur;
        return p;
    }

    /*----------------------------------------------------------*/

    void initPlateauAvecNULL(TplateauJeu jeu,int largeur, int hauteur)
    {
        for (int i=0;i<largeur;i++)
        {
            for (int j=0;j<hauteur;j++)
            {
                jeu[i][j] = NULL;
            }
        }
    }

    /*----------------------------------------------------------*/

    void initPlateauUpgradeAvecNULL(TplateauJeuUpgrade jeu,int largeur, int hauteur)
    {
        for (int i=0;i<largeur;i++)
        {
            for (int j=0;j<hauteur;j++)
            {
                jeu[i][j] = creerTzoneVide();
            }
        }
    }

    /*----------------------------------------------------------*/

    bool findPosForUnite(Tcouleur couleur, Tpos* pos, TplateauJeuUpgrade jeuUpgrade, bool tourDetruite, Tcible positionUnite)
    {
        // Il y a deux camps, un pour le joueur1 et un pour le joueur2 (camp = 1 pour joueur1 et 2 pour joueur2).
        int xSpawn[6] = {2,3,4,6,7,8}; // Les emplacements à coté des tours.
        int ySpawn[2] = {0, 0};
        int camp = 1;
        if(couleur == rouge)
        {
            camp = 2;
        }

        if(tourDetruite) // Si la tour est detruite alors on met le point d'apparition en arrière(à coté de la "tour du roi").
        {
            ySpawn[0] = 17;
            ySpawn[1] = 1;
        }
        else // Sinon le point d'apparition est à coté de la "tour".
        {
            ySpawn[0] = 15;
            ySpawn[1] = 3;
        }

        bool possibleToPlaceUnite = false;
        // Si l'unité est dans les airs on regarde si il y a de la place dans les airs et de même pour le sol.
        bool (*fcomparaison)(Tzone* z) = fonctionComparaisonUnite(positionUnite);

        for(int i = 0; i < 6; i++) // On regarde si il y a de la place pour l'apparition une unité.
        {
            if(!fcomparaison(&(jeuUpgrade[xSpawn[i]][ySpawn[camp-1]])))
            {
                possibleToPlaceUnite = true;
            }
        }
        if(!possibleToPlaceUnite) //Si ce n'est pas possible alors on retourne qu'il n'y pas de place.
        {
            return false;
        }
        else // Si il y a de la place alors on tire une position aleatoirement et on ragarde si c'est possible d'y placer l'unité.
        {
            bool posTrouver = false;
            while(posTrouver != true)
            {
                int randNb = random_int(0,5);
                int posX = xSpawn[randNb];
                int posY = ySpawn[camp-1];
                // C'est possible de mettre l'unité donc on change les coordonnées de pos et on dit que c'est possible.
                if(!fcomparaison(&(jeuUpgrade[posX][posY])))
                {
                    pos->x = posX;
                    pos->y = posY;
                    posTrouver = true;
                }
            }
            return true;
        }
    }

    /*----------------------------------------------------------*/

    void AjouterUnite(TListePlayer* player, Tunite* nouvelleUnite)
    {
        *player = add_fst(*player, nouvelleUnite);
    }

    /*----------------------------------------------------------*/

    void addPosToUnite(Tunite* unite, Tpos pos)
    {
        unite->posX = pos.x;
        unite->posY = pos.y;
    }

    /*----------------------------------------------------------*/

    Tunite* AcheteUnite(TPlayer* player)
    {
        if(random_int(0,1) == 0 && player->elixir > 0) // Une chance sur 2 de pouvoir acheter une unité.
        {
            Tcouleur couleurJ = player->couleurJoueur;
            Tunite* troupe = NULL;
            while(troupe == NULL) // Tant que l'unité n'est pas trouvée on continue de chercher.
            {
                int NumTroupe = random_int(2, NOMBRE_DE_TROUPES-1); // On choisit entre toutes les unités.
                switch(NumTroupe)
                {
                    case 2: // Archer
                        if(player->elixir >= 2) // Si l'unité est choisie et que le joueur à assez d'elixir alors on la crée.
                        {
                            player->elixir -= 2;
                            troupe = creeArcher(0, 0, couleurJ);
                        }
                        break;
                    case 3: // Chevalier
                        if(player->elixir >= 4)
                        {
                            player->elixir -= 4;
                            troupe = creeChevalier(0, 0, couleurJ);
                        }
                        break;
                    case 4: // Dragon
                        if(player->elixir >= 3)
                        {
                            player->elixir -= 3;
                            troupe = creeDragon(0, 0, couleurJ);
                        }
                        break;
                    case 5: // Gargouille
                        if(player->elixir >= 1)
                        {
                            player->elixir -= 1;
                            troupe = creeGargouille(0, 0, couleurJ);
                        }
                        break;
                    default:
                        printf("\nErreur AcheteUnite : Aucunes troupes selectionnes par la randomisation.\n");
                        exit(1);
                }
            }
            return troupe;
        }
        else // Si le joueur n'a pas assez d'elixir ou pas de chance.
        {
            return NULL;
        }
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                         Modification                         */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void PositionnePlayerOnPlateau_Upgade(TListePlayer player, TplateauJeuUpgrade jeuUpgrade)
    {
        for(TListePlayer p = player; !PlayerEstVide(p); p = p->suiv)
        {
            Tunite* unite = fst(p);
            jeuUpgrade[unite->posX][unite->posY] = ajouterUnitedansZone(jeuUpgrade[unite->posX][unite->posY], unite);
        }
    }

    /*----------------------------------------------------------*/

    void ConversionEnTplateauJeu(TplateauJeuUpgrade jeuEncours, TplateauJeu jeuEn2D)
    {
        for(int lar = 0; lar < LARGEURJEU; lar++)
        {
            for(int hau = 0; hau < HAUTEURJEU; hau++)
            {
                jeuEn2D[lar][hau] = fstTzone(jeuEncours[lar][hau]);
            }
        }
    }

    /*----------------------------------------------------------*/

    TListePlayer quiEstAPortee_position(Tunite* uneUniteQuiAttaque, TListePlayer toutesUniteDansLeRayonDeLUnite)
    {
        TListePlayer res = creerListeVide();
        for(TListePlayer tmp = toutesUniteDansLeRayonDeLUnite; !(PlayerEstVide(tmp)); tmp = tmp->suiv)
        {
            // Si elle peut attaquer alors on l'ajoute à la liste de retour.
            if(peutAttaquer(uneUniteQuiAttaque, tmp->pdata))
            {
                res = add_fst(res, tmp->pdata);
            }
        }
        return res;
    }

    /*----------------------------------------------------------*/

    TListePlayer quiEstAPortee_Upgrade(TplateauJeuUpgrade jeuEncours, Tunite* uneUniteQuiAttaque)
    {
        TListePlayer toutesUnitesAPortee = creerListeVide();
        int Xunite = uneUniteQuiAttaque->posX;
        int Yunite = uneUniteQuiAttaque->posY;
        int portee = uneUniteQuiAttaque->portee;
        for(int lar = Xunite - portee; lar <= Xunite + portee; lar++)
        {
            for(int hau = Yunite - portee; hau <= Yunite + portee; hau++)
            {
                // Si la position est dans le jeu.
                if(posInMap(lar, hau, LARGEURJEU, HAUTEURJEU))
                {
                    // Si la case est dans la portée.
                    if((abs(lar - Xunite) + abs(hau - Yunite)) <= portee)
                    {
                        Tzone* zone = &(jeuEncours[lar][hau]);
                        if(!estvide(*zone))
                        {
                            Tcouleur cInverse = couleurInverse(*uneUniteQuiAttaque);
                            Tzone TzoneCouleur = getUniteDeCouleur(zone, cInverse);
                            // On converti la Tzone en liste.
                            TListePlayer convertZoneInListe = getAllUnitInZone(&TzoneCouleur);
                            // On ajoute les unités de la zone dans la liste de retour.
                            toutesUnitesAPortee = concatList(toutesUnitesAPortee, convertZoneInListe);
                        }
                    }
                }
            }
        }
        toutesUnitesAPortee = quiEstAPortee_position(uneUniteQuiAttaque, toutesUnitesAPortee);
        return toutesUnitesAPortee;
    }

    /*----------------------------------------------------------*/

    bool compareUnite_vitesseAttaque_croi(Tunite* u1, Tunite* u2)
    {
        return u1->vitesseAttaque < u2->vitesseAttaque;
    }

    /*----------------------------------------------------------*/

    bool compareUnite_pointsDeVie_croi(Tunite* u1, Tunite* u2)
    {
        return u1->pointsDeVie < u2->pointsDeVie;
    }

    /*----------------------------------------------------------*/

    void triList(TListePlayer* l, bool (*fcomparaison)(Tunite* a, Tunite* b))
    {
        // Tri par selection.
        for(TListePlayer en_cours = *l; !PlayerEstVide(en_cours); en_cours = en_cours->suiv)
        {
            TListePlayer plus_petit = en_cours;
            for(TListePlayer j = en_cours; !PlayerEstVide(j); j = j->suiv)
            {
                if(fcomparaison(j->pdata, plus_petit->pdata))
                {
                    plus_petit = j;
                }
            }
            swapUnite(en_cours, plus_petit);
        }
    }

    /*----------------------------------------------------------*/

    void diviseListeFoncCouleur(TListePlayer* listeADivise, TListePlayer* pBleu, TListePlayer* pRouge)
    {
        for(TListePlayer tmp = *listeADivise; !PlayerEstVide(tmp); tmp = rem_fst(tmp))
        {
            Tunite* unite = fst(tmp);
            if(unite->couleur == bleu)
            {
                AjouterUnite(pBleu, unite);
            }
            else
            {
                AjouterUnite(pRouge, unite);
            }
        }
    }

    /*----------------------------------------------------------*/

    void combatJoueurs(TPlayer* player1, TPlayer* player2, TplateauJeuUpgrade jeuEncours)
    {
        // On met les unités des deux joueurs dans une seule liste.
        TListePlayer allUnites = concatList(player1->listeU, player2->listeU);
        // On efface les listes des joueurs car elles seront remise à la fin en un ordre different.
        player1->listeU = clearList(player1->listeU);
        player2->listeU = clearList(player2->listeU);

        // On tri "allUnites" en fonction de la vitesse d'attaque.
        triList(&allUnites, compareUnite_vitesseAttaque_croi);

        for(TListePlayer tmp = allUnites; !PlayerEstVide(tmp); tmp = tmp->suiv)
        {
            Tunite* uniteQuiAttaque = fst(tmp);
            TListePlayer unitesAPortee = quiEstAPortee_Upgrade(jeuEncours, uniteQuiAttaque);

            // On tri les unités à portée en fonction de leurs "pointsDeVie".
            triList(&unitesAPortee, compareUnite_pointsDeVie_croi);

            if(!PlayerEstVide(unitesAPortee))
            {
                Tunite* premiereUnite = fst(unitesAPortee);
                uniteQuiAttaque->peutAttaquer = 0;
                if(premiereUnite->pointsDeVie > uniteQuiAttaque->degats)
                {
                    premiereUnite->pointsDeVie -= uniteQuiAttaque->degats;
                }
                // On supprime l'unite de la liste "allUnites" et de la Tzone dans laquelle elle se trouve.
                else
                {
                    int XaDetruire = premiereUnite->posX;
                    int YaDetruire = premiereUnite->posY;
                    jeuEncours[XaDetruire][YaDetruire] = supprimerUnitedansZone(jeuEncours[XaDetruire][YaDetruire], premiereUnite);
                    supprimerUnite(&allUnites, premiereUnite);
                }
            }
        }
        // On remet toutes les unités dans les bonnes liste de joueurs.
        diviseListeFoncCouleur(&allUnites, &(player1->listeU), &(player2->listeU));
    }

    /*----------------------------------------------------------*/

    void resetPeutAttaquer(TPlayer* player)
    {
        TListePlayer tmp = player->listeU;
        while(!PlayerEstVide(tmp)) // Pour tout les elements de player, "peutAttaquer" = 1.
        {
            tmp->pdata->peutAttaquer = 1;
            tmp = tmp->suiv;
        }
    }

    /*----------------------------------------------------------*/

    void addElixirToPlayer(TPlayer* player)
    {
        player->elixir += random_int(1,3); // Entre 1 et 3 elixir(s) est/sont donné(s) au joueur.
    }

    /*----------------------------------------------------------*/

    void changeUnitePosInMap(Tunite* unite, Tpos pos, TplateauJeuUpgrade jeuUpgrade)
    {
        // Tpos = int x et int y.
        jeuUpgrade[unite->posX][unite->posY] = supprimerUnitedansZone(jeuUpgrade[unite->posX][unite->posY], unite);
        unite->posX = pos.x;
        unite->posY = pos.y;
        jeuUpgrade[unite->posX][unite->posY] = ajouterUnitedansZone(jeuUpgrade[unite->posX][unite->posY], unite);
    }

    /*----------------------------------------------------------*/

    void modifPosUnitePeutAttaquer(Tcouleur couleur, Tunite* unite, TplateauJeuUpgrade jeuUpgrade)
    {
        // Mouvement permet de déplacer une unité en haut, en bas , à droite ou à gauche selon l'axe et la situation .
        int mouvement[2] = {-1, 1};
        int camp = 1;
        if(couleur == rouge)
        {
            camp = 2;
        }
        // Si l'unité est dans les airs on regarde si il y a de la place dans les airs et de même pour le sol.
        bool (*fcomparaison)(Tzone* z) = fonctionComparaisonUnite(unite->maposition);
        Tpos pos;

        if(unite->posX == 5) // Si l'unité est au milieu.
        {
            pos.y = unite->posY + mouvement[camp-1];
            if(!fcomparaison(&(jeuUpgrade[5][pos.y]))) // On regarde devant s'il y a de la place pour la déplacer.
            {
                pos.x = 5;
                changeUnitePosInMap(unite, pos, jeuUpgrade);
            }
            else if(!fcomparaison(&(jeuUpgrade[5-1][pos.y]))) // On regarde devant à gauche si il y a de la place pour la déplacer.
            {
                pos.x = 5-1;
                changeUnitePosInMap(unite, pos, jeuUpgrade);
            }
            else if(!fcomparaison(&(jeuUpgrade[5+1][pos.y]))) // On regarde devant à droite si il y a de la place pour la déplacer.
            {
                pos.x = 5+1;
                changeUnitePosInMap(unite, pos, jeuUpgrade);
            }
        }
        else
        {
            int horizon;
            if(unite->posX < 5) // Si l'unité est sur la gauche alors on la déplace sur la droite.
            {
                horizon = 1;
            }
            else // Sinon on la déplace sur la gauche.
            {
                horizon = -1;
            }
            // Si il y a une position libre devant(à droite ou à gauche).
            if(!fcomparaison(&(jeuUpgrade[unite->posX+horizon][unite->posY + mouvement[camp-1]])))
            {
                pos.x = unite->posX+horizon;
                pos.y = unite->posY + mouvement[camp-1];
                changeUnitePosInMap(unite, pos, jeuUpgrade);
            }
            // Si il y a une position libre (à droite ou à gauche).
            else if(!fcomparaison(&(jeuUpgrade[unite->posX+horizon][unite->posY])))
            {
                pos.x = unite->posX+horizon;
                pos.y = unite->posY;
                changeUnitePosInMap(unite, pos, jeuUpgrade);
            }
            // Si il y a une position libre devant.
            else if(!fcomparaison(&(jeuUpgrade[unite->posX][unite->posY + mouvement[camp-1]])))
            {
                pos.x = unite->posX;
                pos.y = unite->posY + mouvement[camp-1];
                changeUnitePosInMap(unite, pos, jeuUpgrade);
            }
        }
    }

    /*----------------------------------------------------------*/

    void modifPosUnitesPlayer(TPlayer* player, TplateauJeuUpgrade jeuUpgrade)
    {
        TListePlayer tmp = player->listeU;
        while(!PlayerEstVide(tmp)) // Tant que la liste n'est pas vide.
        {
            if(tmp->pdata->peutAttaquer == 1 && tmp->pdata->vitessedeplacement != 0) // Si l'unité peut se déplacer et n'a pas attaquée.
            {
                tmp->pdata->peutAttaquer = 0;
                modifPosUnitePeutAttaquer(player->couleurJoueur, tmp->pdata, jeuUpgrade);
            }
            tmp = tmp->suiv;
        }
    }

    /*----------------------------------------------------------*/

    void addUniteToPlayer(TPlayer* player, TplateauJeuUpgrade jeuUpgrade, bool* tourPlayerDetruite)
    {
        // Achete une unité.
        Tunite* unite = AcheteUnite(player);
        Tpos posTroupe;
        if(unite != NULL)
        {
            if(findPosForUnite(player->couleurJoueur, &posTroupe, jeuUpgrade, *tourPlayerDetruite, unite->maposition))
            {
                // Ajoute les coordonnées trouvées par "findPosForUnite" à l'unité.
                addPosToUnite(unite, posTroupe);
                // Ajoute l'unité au joueur.
                AjouterUnite(&(player->listeU), unite);
            }
            else
            {
                free(unite);
            }
        }
    }

    /*----------------------------------------------------------*/

    void addSpecifiqueUniteToPlayer(TPlayer* player, TplateauJeuUpgrade jeuUpgrade, bool* tourPlayerDetruite, Tunite* (creeUnite)(int x, int y , Tcouleur c), bool* modif)
    {
        // Achete une unité.
        Tunite* unite = creeUnite(0, 0, player->couleurJoueur);

        Tpos posTroupe;
        if(findPosForUnite(player->couleurJoueur, &posTroupe, jeuUpgrade, *tourPlayerDetruite, unite->maposition))
        {
            if(unite != NULL)
            {
                // Ajoute les coordonnées trouvées par "findPosForUnite" à l'unité.
                addPosToUnite(unite, posTroupe);
                // On ajoute l'unité au plateau de jeu.
                jeuUpgrade[unite->posX][unite->posY] = ajouterUnitedansZone(jeuUpgrade[unite->posX][unite->posY], unite);
                // Ajoute l'unité au joueur.
                AjouterUnite(&(player->listeU), unite);
                *modif = true;
            }
        }
        else
        {
            free(unite);
        }
    }

    /*----------------------------------------------------------*/

    Tcouleur couleurInverse(Tunite unite)
    {
        if(unite.couleur == bleu)
        {
            return rouge;
        }
        else
        {
            return bleu;
        }
    }

    /*----------------------------------------------------------*/

    char* couleurUnite(Tunite unite)
    {
        if(unite.couleur == bleu)
        {
            return "bleu";
        }
        else
        {
            return "rouge";
        }
    }

    /*----------------------------------------------------------*/

    bool (*fonctionComparaisonUnite(Tcible positionUnite))(Tzone* z)
    {
        if(positionUnite == sol)
        {
            return UniteAuSolPresente;
        }
        else if(positionUnite == air)
        {
            return UniteEnVolPresente;
        }
        else
        {
            printf("erreur findPosForUnite : unite du mauvais Tcible");
            exit(1);
        }
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                        Suppression                           */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void supprimerUnite(TListePlayer* player, Tunite* UniteDetruite)
    {
        int finSuppression = 0;
        TListePlayer precUnit = NULL;
        TListePlayer Unit = *player;
        if(Unit->suiv == NULL) // Si il n'y a qu'un seul element dans la liste.
        {
            if(Unit->pdata == UniteDetruite) // Si l'unité à supprimer est celle de la liste.
            {
                free(Unit);
                *player = NULL;
            }
        }
        else // Si il y a plus d'un element.
        {
            // Tant que l'unité n'est pas supprimée de la liste et que la liste n'est pas encore vide.
            while(finSuppression == 0 && (*player) != NULL)
            {
                if(Unit->pdata == UniteDetruite) // Si l'unité correspond à l'unité à detruire.
                {
                    finSuppression = 1; // Fin de la boucle.
                    if(precUnit != NULL) // Si l'unité n'est pas en debut de liste.
                    {
                        precUnit->suiv = Unit->suiv;
                        free(Unit);
                        Unit = NULL;
                    }
                    else
                    {
                        TListePlayer tmp = Unit->suiv;
                        free(Unit);
                        *player = tmp;
                    }
                }
                else // Si ce n'est pas l'unité à détruire on continue de chercher.
                {
                    precUnit = Unit;
                    Unit = Unit->suiv;
                }
            }
        }
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                      Verification                            */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    bool tourRoiDetruite(TListePlayer player) //Cherche la "tour du roi" afin de vérifié si  elle est détruite ou non.
    {
        TListePlayer tmp = player;
        while(!PlayerEstVide(tmp))
        {
            if(tmp->pdata->nom == tourRoi) // Si on trouve la "tour du roi" alors elle est toujours là et donc elle n'est pas detruite.
            {
                return false;
            }
            tmp = tmp->suiv;
        }
        return true; // On ne trouve pas la "tour du roi" donc elle est detruite.
    }

    /*----------------------------------------------------------*/

    bool tourDetruite(TListePlayer player) //Cherche la "tour" afin de vérifié si  elle est détruite ou non.
    {
        TListePlayer tmp = player;
        while(!PlayerEstVide(tmp))
        {
            if(tmp->pdata->nom == tour) // Si on trouve la "tour" alors elle est toujours là et donc elle n'est pas detruite.
            {
                return false;
            }
            tmp = tmp->suiv;
        }
        return true; // On ne trouve pas la "tour" donc elle est detruite.
    }

    /*----------------------------------------------------------*/

    bool peutAttaquer(Tunite* uniteQuiAttaque, Tunite* uniteQuiDefend)
    {
        if(uniteQuiAttaque->cibleAttaquable == solEtAir) // L'unité peut attaquer les ennemis au sol et dans les airs.
        {
            return true;
        }
        else if(uniteQuiAttaque->cibleAttaquable == uniteQuiDefend->maposition) // L'unité est au même niveau que l'autre unité donc elle peut l'attaquer.
        {
            return true;
        }
        else // Impossible d'attaquer l'unité ennemie(uniteQuiDefend).
        {
            return false;
        }
    }

    /*----------------------------------------------------------*/

    bool posInMap(int x, int y, int largeur, int hauteur)
    {
        return (x >= 0 && x < largeur) && (y >= 0 && y < hauteur);
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////
/*                   Affichage Console                          */
//////////////////////////////////////////////////////////////////

    /*----------------------------------------------------------*/

    void affichePlateauConsole(TplateauJeu jeu, int largeur, int hauteur){
        // Pour un affichage sur la console, en relation avec enum TuniteDuJeu.
        const char* InitialeUnite[6]={"T", "R", "A", "C", "D", "G"};

        printf("\n");
        for (int i=0;i < largeur+2; i++)
        {
            printf("/");
        }
        printf("\n");
        for (int j=0;j<hauteur;j++)
        {
            printf("/");
            for (int i=0;i<largeur;i++)
            {
                if (jeu[i][j] != NULL)
                {
                        printf("%s",InitialeUnite[jeu[i][j]->nom]);
                }
                else // Pas d'unité sur cette case.
                {
                    printf(".");
                }
            }
            printf("/\n");
        }
        for (int i=0;i < largeur+2; i++)
        {
            printf("/");
        }
        printf("\n");
    }

    /*----------------------------------------------------------*/

    void afficheUneUnite(Tunite* unite)
    {
        // En fonction du type enum TuniteDuJeu on a un string pour chaque unité.
        const char* troupes[NOMBRE_DE_TROUPES] = {"Tour", "Tour du Roi", "Archer", "Chevelier", "Dragon", "Gargouille"};
        // On affiche le nom, la vitesse d'attaque, les points de vie et les degats.
        printf("%s avec VitesseAttaque: %f, points de vie %d, degats: %d, X: %d, Y: %d, couleur: %s\n",
               troupes[unite->nom], unite->vitesseAttaque, unite->pointsDeVie, unite->degats, unite->posX, unite->posY, couleurUnite(*unite));
    }

    /*----------------------------------------------------------*/

    void afficheListeUnites(TListePlayer player, const char* nomPlayer)
    {
        printf("\nAffichage de la liste de \"%s\" :\n", nomPlayer);
        printf("----------------------------------------------------------------------\n");
        if(PlayerEstVide(player))
        {
            printf("La liste est vide.\n");
        }
        else
        {
            TListePlayer tmp = player;
            while(!PlayerEstVide(tmp)) // Affiche toutes les unités.
            {
                afficheUneUnite(tmp->pdata);
                tmp = tmp->suiv;
            }
        }
        printf("----------------------------------------------------------------------\n");
    }

    /*----------------------------------------------------------*/

    void reafficheNbElixir(TPlayer p1, TPlayer p2)
    {
        printf("\r");
        printf("Elixir du joueur 1: %d et 2: %d", p1.elixir, p2.elixir);
    }

    /*----------------------------------------------------------*/

//////////////////////////////////////////////////////////////////





