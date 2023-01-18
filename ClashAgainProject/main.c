//NOM prénom : Hervouet Léo.

#include "SDL.h"
#include "SDL_image.h" // Pour les images en .png
#include "maSDL.h"    //bibliothèque avec des fonction d'affichage pour le jeu 2048
#include "clashagain.h"
#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/*--------- Main ---------------------*/
int main(int argc, char* argv[])
{
    // Initialise la randomisation.
    initRandom();

    SDL_Event event;

    SDL_Window *pWindow;
    SDL_Init(SDL_INIT_VIDEO);

    pWindow = SDL_CreateWindow(
        "-ClashAgain-",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        LARGEURJEU*40,
        HAUTEURJEU*40,
        SDL_WINDOW_SHOWN
    );

    // Installation de SDL_image = https://www.developpez.net/forums/d1444365/applications/developpement-2d-3d-jeux/api-graphiques/sdl/installation-sdl2-codeblocks/
    SDL_Surface* pWinSurf = SDL_GetWindowSurface(pWindow);  //le sprite qui couvre tout l'écran
    SDL_Surface* pSpriteTour = IMG_Load("./data/Tour.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi = IMG_Load("./data/TourRoi.bmp"); //indice 1
    SDL_Surface* pSpriteArcher = IMG_Load("./data/Archer.png"); //indice 2
    SDL_Surface* pSpriteChevalier = IMG_Load("./data/Chevalier.png"); //indice 3
    SDL_Surface* pSpriteDragon = IMG_Load("./data/Dragon.png"); //indice 4
    SDL_Surface* pSpriteGargouille = IMG_Load("./data/Gargouille.png"); //indice 5
    SDL_Surface* pSpriteMap = IMG_Load("./data/mapClashAgain.png"); // indice 6 map du jeu.
    // Les troupes Bleu:
    SDL_Surface* pSpriteTour_bleu = IMG_Load("./data/troupesBleu/Tour_Bleu.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi_bleu = IMG_Load("./data/troupesBleu/TourRoi_Bleu.bmp"); //indice 1
    SDL_Surface* pSpriteArcher_bleu = IMG_Load("./data/troupesBleu/Archer_Bleu.png"); //indice 2
    SDL_Surface* pSpriteChevalier_bleu = IMG_Load("./data/troupesBleu/Chevalier_Bleu.png"); //indice 3
    SDL_Surface* pSpriteDragon_bleu = IMG_Load("./data/troupesBleu/Dragon_Bleu.png"); //indice 4
    SDL_Surface* pSpriteGargouille_bleu = IMG_Load("./data/troupesBleu/Gargouille_Bleu.png"); //indice 5
    // Les troupes Rouge:
    SDL_Surface* pSpriteTour_rouge = IMG_Load("./data/troupesRouge/Tour_Rouge.bmp");  //indice 0 dans tabSprite (via l'enum TuniteDuJeu)
    SDL_Surface* pSpriteTourRoi_rouge = IMG_Load("./data/troupesRouge/TourRoi_Rouge.bmp"); //indice 1
    SDL_Surface* pSpriteArcher_rouge = IMG_Load("./data/troupesRouge/Archer_Rouge.png"); //indice 2
    SDL_Surface* pSpriteChevalier_rouge = IMG_Load("./data/troupesRouge/Chevalier_Rouge.png"); //indice 3
    SDL_Surface* pSpriteDragon_rouge = IMG_Load("./data/troupesRouge/Dragon_Rouge.png"); //indice 4
    SDL_Surface* pSpriteGargouille_rouge = IMG_Load("./data/troupesRouge/Gargouille_Rouge.png"); //indice 5

    if(!pSpriteMap)
    {
        printf("Erreur load map\n");
    }
    SDL_Surface* TabSprite[7]={pSpriteTour,pSpriteTourRoi,pSpriteArcher,pSpriteChevalier,pSpriteDragon,pSpriteGargouille,pSpriteMap};
    SDL_Surface* TabSprite_bleu[7]={pSpriteTour_bleu,pSpriteTourRoi_bleu,pSpriteArcher_bleu,pSpriteChevalier_bleu,pSpriteDragon_bleu,pSpriteGargouille_bleu,pSpriteMap};
    SDL_Surface* TabSprite_rouge[7]={pSpriteTour_rouge,pSpriteTourRoi_rouge,pSpriteArcher_rouge,pSpriteChevalier_rouge,pSpriteDragon_rouge,pSpriteGargouille_rouge,pSpriteMap};

    if(!pSpriteTour_bleu && !pSpriteTourRoi_bleu && !pSpriteArcher_bleu && !pSpriteChevalier_bleu && !pSpriteDragon_bleu && !pSpriteGargouille_bleu)
    {
        printf("Erreur load images bleu\n");
    }
    if(!pSpriteTour_rouge && !pSpriteTourRoi_rouge && !pSpriteArcher_rouge && !pSpriteChevalier_rouge && !pSpriteDragon_rouge && !pSpriteGargouille_rouge)
    {
        printf("Erreur load images rouge\n");
    }

    // Si le chargement des images se passe mal alors le jeu ne se lance pas.
    if (pSpriteTour && pSpriteTourRoi && pSpriteArcher && pSpriteChevalier && pSpriteDragon && pSpriteGargouille && pSpriteMap)
    {
        TplateauJeu jeu = AlloueTab2D(LARGEURJEU,HAUTEURJEU);
        initPlateauAvecNULL(jeu,LARGEURJEU,HAUTEURJEU);
        affichePlateauConsole(jeu,LARGEURJEU,HAUTEURJEU);

        ///********************* NOUVEAUTE ***************************
        TplateauJeuUpgrade jeuUpgrade = AlloueTab2D_Tzone(LARGEURJEU, HAUTEURJEU);
        initPlateauUpgradeAvecNULL(jeuUpgrade, LARGEURJEU, HAUTEURJEU);

        TPlayer player1 = initPlayer(bleu);
        TPlayer player2 = initPlayer(rouge);
        ///********************* fin NOUVEAUTE ***************************

        ///*****************************************************************************///
        ///**DEBUT VARIABLE**///

        // Permet d'avoir des entrées de touches fluides mais avec un jeu lent.
        int time = 0;
        // Permet de rafraichir la fenêtre graphique.
        bool rafraichirFGraphique = false;
        // Pour mettre en pause le jeu.
        bool pauseJeu = false;
        // Pour savoir si la tour de player1 et player2 est détruite.
        bool tourPlayer1Detruite = false;
        bool tourPlayer2Detruite = false;
        // Pour ne plus rentrer dans la boucle qui fait le combat entre player1 et player2.
        bool finJeu = false;

        ///**FIN VARIABLE**///
        ///*****************************************************************************///

        PositionnePlayerOnPlateau_Upgade(player1.listeU, jeuUpgrade);
        PositionnePlayerOnPlateau_Upgade(player2.listeU, jeuUpgrade);
        ConversionEnTplateauJeu(jeuUpgrade, jeu);
        prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
        prepareAllSpriteDuJeuUpgrade(jeuUpgrade, LARGEURJEU, HAUTEURJEU, TabSprite_bleu, TabSprite_rouge, pWinSurf);
        maj_fenetre(pWindow);

        message("Differentes action du jeu","ECHAP : quitter.\nG/ A/ D/ C : pour l\'apprition d\'unites dans le jeu.\nP : pause");

        // boucle principale du jeu
        bool boucleJeu = true;
        while (boucleJeu)
        {
                SDL_PumpEvents(); //do events
                SDL_PollEvent(&event); // Pour le bouton "Quit" de la fenêtre.

                // Une fois sur 30 on fait un tour de jeu.
                if(time < 30)
                {
                    time++;
                }
                else
                {
                    time = 0;
                }

                ///*****************************************************************************///
                ///**DEBUT DU JEU**///

                if(time == 0 && !pauseJeu && !finJeu)
                {
                    // On affiche le tableau dans la console.
                    affichePlateauConsole(jeu, LARGEURJEU, HAUTEURJEU);
                    // On affiche les joueurs.
                    afficheListeUnites(player1.listeU, "player1");
                    afficheListeUnites(player2.listeU, "player2");

                    // On ajoute de l'élixir aux joueurs.
                    addElixirToPlayer(&player1);
                    addElixirToPlayer(&player2);

                    // On met le champ "peutAttaquer" de toutes les troupes des joueurs à 1.
                    resetPeutAttaquer(&player1);
                    resetPeutAttaquer(&player2);

                    // On ajoute au joueur une unité si il y a de la place sur les endroits de d'apparition et si le joueur a assez d'elixir.
                    addUniteToPlayer(&player1, jeuUpgrade, &tourPlayer1Detruite);
                    addUniteToPlayer(&player2, jeuUpgrade, &tourPlayer2Detruite);

                    combatJoueurs(&player1, &player2, jeuUpgrade);

                    // On vide le plateau de jeu pour mettre les chagements.
                    initPlateauUpgradeAvecNULL(jeuUpgrade, LARGEURJEU, HAUTEURJEU);

                    // On rempli le plateauUpgrade avec les deux liste de joueurs.
                    PositionnePlayerOnPlateau_Upgade(player1.listeU, jeuUpgrade);
                    PositionnePlayerOnPlateau_Upgade(player2.listeU, jeuUpgrade);

                    // On modifie la position des unités qui n'ont pas attaqué.
                    modifPosUnitesPlayer(&player1, jeuUpgrade);
                    modifPosUnitesPlayer(&player2, jeuUpgrade);

                    if(tourRoiDetruite(player1.listeU))
                    {
                        message("Defaite","Le joueur 2 a gagne !");
                        finJeu = true;
                    }
                    if(tourRoiDetruite(player2.listeU))
                    {
                        message("Victoire","Le joueur 2 a perdu !");
                        finJeu = true;
                    }

                    //Affichage du jeu à chaque tour.
                    efface_fenetre(pWinSurf);
                    ConversionEnTplateauJeu(jeuUpgrade, jeu);
                    affichePlateauConsole(jeu, LARGEURJEU, HAUTEURJEU);
                    afficheListeUnites(player1.listeU, "player1");
                    afficheListeUnites(player2.listeU, "player2");
                    printf("\nElixir du joueur 1: %d et 2: %d", player1.elixir, player2.elixir);
                    //prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                    prepareAllSpriteDuJeuUpgrade(jeuUpgrade, LARGEURJEU, HAUTEURJEU, TabSprite_bleu, TabSprite_rouge, pWinSurf);
                    maj_fenetre(pWindow);
                }

                ///**FIN DU JEU**///
                ///*****************************************************************************///

                SDL_Delay(30);  // le delay * le "time" max nous donne le temps pour un tour de jeu.

                const Uint8* pKeyStates = SDL_GetKeyboardState(NULL);
                bool modif = false;
                if ( pKeyStates[SDL_SCANCODE_G] ){

                        if(player1.elixir >= 1)
                        {
                            addSpecifiqueUniteToPlayer(&player1, jeuUpgrade, &tourPlayer1Detruite, creeGargouille, &modif);
                            reafficheNbElixir(player1, player2);
                            if(modif)
                            {
                                player1.elixir -= 1;
                            }
                        }
                        else
                        {
                            printf("\nLe joueur n'a pas assez d\'elixir pour un Gargouille.");
                        }

                        rafraichirFGraphique = true;
                }
                if ( pKeyStates[SDL_SCANCODE_C] ){

                        if(player1.elixir >= 4)
                        {
                            addSpecifiqueUniteToPlayer(&player1, jeuUpgrade, &tourPlayer1Detruite, creeChevalier, &modif);
                            reafficheNbElixir(player1, player2);
                            if(modif)
                            {
                                player1.elixir -= 4;
                            }
                        }
                        else
                        {
                            printf("\nLe joueur n'a pas assez d\'elixir pour un Chevalier.");
                        }

                        rafraichirFGraphique = true;
                }
                if ( pKeyStates[SDL_SCANCODE_D] ){

                        if(player1.elixir >= 3)
                        {
                            addSpecifiqueUniteToPlayer(&player1, jeuUpgrade, &tourPlayer1Detruite, creeDragon, &modif);
                            reafficheNbElixir(player1, player2);
                            if(modif)
                            {
                                player1.elixir -= 3;
                            }
                        }
                        else
                        {
                            printf("\nLe joueur n'a pas assez d\'elixir pour un Dragon.");
                        }

                        rafraichirFGraphique = true;
                }
                if ( pKeyStates[SDL_SCANCODE_Q] ){

                        if(player1.elixir >= 2)
                        {
                            addSpecifiqueUniteToPlayer(&player1, jeuUpgrade, &tourPlayer1Detruite, creeArcher, &modif);
                            reafficheNbElixir(player1, player2);
                            if(modif)
                            {
                                player1.elixir -= 2;
                            }
                        }
                        else
                        {
                            printf("\nLe joueur n'a pas assez d\'elixir pour un Archer.");
                        }

                        rafraichirFGraphique = true;
                }
                if ( pKeyStates[SDL_SCANCODE_P] ){

                        if(pauseJeu)
                        {
                            pauseJeu = false;
                            printf("\nLe jeu n\'est plus en pause.\n");
                        }
                        else
                        {
                            pauseJeu = true;
                            printf("\nLe jeu est en pause.\n");
                        }

                        SDL_Delay(300);
                }
                if ( pKeyStates[SDL_SCANCODE_ESCAPE] || event.type == SDL_QUIT){
                        boucleJeu = false;  //sortie de la boucle
                }

                if(rafraichirFGraphique)
                {
                    efface_fenetre(pWinSurf);
                    //prepareAllSpriteDuJeu(jeu,LARGEURJEU,HAUTEURJEU,TabSprite,pWinSurf);
                    prepareAllSpriteDuJeuUpgrade(jeuUpgrade, LARGEURJEU, HAUTEURJEU, TabSprite_bleu, TabSprite_rouge, pWinSurf);
                    maj_fenetre(pWindow);
                    SDL_Delay(300);
                    rafraichirFGraphique = false;
                }
        }
        //fin boucle du jeu

        // Free des surfaces.
        SDL_FreeSurface(pSpriteTour_bleu);
        SDL_FreeSurface(pSpriteTourRoi_bleu);
        SDL_FreeSurface(pSpriteArcher_bleu);
        SDL_FreeSurface(pSpriteChevalier_bleu);
        SDL_FreeSurface(pSpriteDragon_bleu);
        SDL_FreeSurface(pSpriteGargouille_bleu);

        SDL_FreeSurface(pSpriteTour_rouge);
        SDL_FreeSurface(pSpriteTourRoi_rouge);
        SDL_FreeSurface(pSpriteArcher_rouge);
        SDL_FreeSurface(pSpriteChevalier_rouge);
        SDL_FreeSurface(pSpriteDragon_rouge);
        SDL_FreeSurface(pSpriteGargouille_rouge);

        SDL_FreeSurface(pSpriteTour);
        SDL_FreeSurface(pSpriteTourRoi);
        SDL_FreeSurface(pSpriteArcher);
        SDL_FreeSurface(pSpriteChevalier);
        SDL_FreeSurface(pSpriteDragon);
        SDL_FreeSurface(pSpriteGargouille);
        SDL_FreeSurface(pSpriteMap);
        SDL_FreeSurface(pWinSurf);
    }
    else
    {
        fprintf(stdout,"Échec de chargement du sprite (%s)\n",SDL_GetError());
    }

    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}
