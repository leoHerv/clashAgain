#include "SDL.h"
#include "maSDL.h"
#include "clashagain.h"
//#include "types.h"

void message(char *myTitle, char *myMessage){
        const SDL_MessageBoxButtonData buttons[] = {
        { /* .flags, .buttonid, .text */        0, 0, "ok" },
 //       { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
 //       { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
    };
    const SDL_MessageBoxColorScheme colorScheme = {
        { /* .colors (.r, .g, .b) */
            /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
            { 255,   0,   0 },
            /* [SDL_MESSAGEBOX_COLOR_TEXT] */
            {   0, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
            { 255, 255,   0 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
            {   0,   0, 255 },
            /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
            { 255,   0, 255 }
        }
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION, /* .flags */
        NULL, /* .window */
        myTitle, /* .title */
        myMessage, /* .message */
        SDL_arraysize(buttons), /* .numbuttons */
        buttons, /* .buttons */
        &colorScheme /* .colorScheme */
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        //return 1;
    }
    /*
    if (buttonid == -1) {
        SDL_Log("no selection");
    } else {
        SDL_Log("selection was %s", buttons[buttonid].text);
    }
    */
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination )
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, NULL, destination, &offset );
}

void clear_surface(SDL_Surface *psurf){
        Uint32 color = SDL_MapRGB(psurf->format,0,0,0);
        SDL_FillRect(psurf,NULL, color);
}

void prepare_sprite( int x, int y, SDL_Surface* source, SDL_Surface* destination ){
    apply_surface( x, y, source, destination );
}

void efface_fenetre(SDL_Surface *psurf){
    clear_surface(psurf);
}

void maj_fenetre(SDL_Window *pWindow){
    SDL_UpdateWindowSurface(pWindow);
}

// Affichage graphique :

void prepareMapDuJeu(SDL_Surface* map, SDL_Surface* destination)
{
    // La map fait du 440*760 (11*40 et 19*40)
    prepare_sprite(0, 0, map, destination);
}

void prepareAllSpriteDuJeu(TplateauJeu jeu, int largeur, int hauteur, SDL_Surface **TabSprite, SDL_Surface* destination )
{

    prepareMapDuJeu(TabSprite[6], destination);
    for (int j=0;j<hauteur;j++)
    {
        for (int i=0;i<largeur;i++)
        {
            if (jeu[i][j] != NULL)
            {
                prepare_sprite(i*40,j*40,TabSprite[jeu[i][j]->nom],destination);  //remarque les sprites font 40*40 pixels
            }
        }
    }
}

void prepareAllSpriteDuJeuUpgrade(TplateauJeuUpgrade jeuUpgrade, int largeur, int hauteur, SDL_Surface **TabSpriteBleu, SDL_Surface **TabSpriteRouge,
                                    SDL_Surface* destination)
{
    prepareMapDuJeu(TabSpriteBleu[6], destination);
    for (int j=0;j<hauteur;j++)
    {
        for (int i=0;i<largeur;i++)
        {
            if(!estvide(jeuUpgrade[i][j]))
            {
                Tzone* zone = &(jeuUpgrade[i][j]);
                TListePlayer convertZoneInListe = getAllUnitInZone(zone);
                for(TListePlayer tmp = convertZoneInListe; !PlayerEstVide(tmp); tmp = tmp->suiv)
                {
                    Tunite* unite = fst(tmp);
                    int x = i*40;
                    int y = j*40;
                    if(unite->vitessedeplacement != 0)
                    {
                        x -= random_int(0, 5);
                        y -= random_int(0, 5);
                    }
                    if(unite->couleur == bleu)
                    {
                        prepare_sprite(x ,y ,TabSpriteBleu[unite->nom],destination);
                    }
                    if(unite->couleur == rouge)
                    {
                        prepare_sprite(x ,y ,TabSpriteRouge[unite->nom],destination);
                    }

                }
            }
        }
    }
}


