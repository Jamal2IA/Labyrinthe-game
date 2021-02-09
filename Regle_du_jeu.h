#ifndef REGLE_DU_JEU_H_INCLUDED
#define REGLE_DU_JEU_H_INCLUDED
#include "stdio.h"

#include <SDL.h>

#include"Regle_du_jeu.h"

int regle_du_jeu(SDL_Surface *image_regle_du_jeu)

{SDL_Surface *ecran=NULL;

SDL_Event event;

    int continuer=1;

    while (continuer)

    {

    SDL_WaitEvent(&event);

        SDL_BlitSurface(image_regle_du_jeu,NULL,ecran ,NULL);

        SDL_Flip(ecran);

        switch(event.type)

        {if (event.key.keysym.sym==SDLK_KP0)

        return 1;

        break;

        }

    }

}


#endif // REGLE_DU_JEU_H_INCLUDED
