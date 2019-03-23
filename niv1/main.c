/**
 * \file main.c
 * \brief Programme principal
 * \author Alexis Kohler
 * \version 0.1
 * \date 23 mars 2019
 */

#include "sdl-light.h"

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 1288

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 725

/**
 * \brief Taille d'une boule
 */
#define BALL_SIZE 42

#define SPEED_COEF 0.1




/**
 * \brief Représentation du monde du jeu
 */
struct ball_s{

  float x;
  float y;
  float vx;
  float vy;
};

typedef struct ball_s ball_t;

struct world_s{

    SDL_Surface* table;
    SDL_Surface* bowls;
    int gameover;
};

typedef struct world_s world_t;



/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data( world_t * world, ball_t * bowl ){

    world->table = load_image( "ressources/table.bmp" );
    world->bowls=load_image("ressources/boules.bmp");

    world->gameover = 0;

    bowl->x= SCREEN_WIDTH/2;
    bowl->y=SCREEN_HEIGHT/2;

    bowl->vy=0;
    bowl->vx=0;
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data( world_t *world ){

    SDL_FreeSurface(world->table);
    SDL_FreeSurface(world->bowls);
}




/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over( world_t *world ){

    return world->gameover;
}


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data( ball_t * bowl ){

    bowl->x = bowl->x + bowl->vx;
    bowl->y = bowl->y + bowl->vy;
    bowl->vx -= bowl->vx*0.05;
    bowl->vy -= bowl->vy*0.05;
}


/**
 * \brief La fonction initialise les transparences des différentes surfaces
 * \param screen la surface correspondant à l'écran de jeu
 * \param world les données du monde
 */

void  init_graphics( SDL_Surface *screen, world_t *world ){

    set_transparence( screen,world->bowls,255,0,255 );
}








/**
 * \brief La fonction rafrachit l'écran en fonction de l'état des données du monde
 * \param screen la surface de l'écran de jeu
 * \param world les données du monde
 */

void refresh_graphics( SDL_Surface *screen, world_t *world, ball_t *bowl ){

    apply_surface( world->table,screen,0,0 );
    apply_sub_surface( world->bowls,screen,0,0,BALL_SIZE,BALL_SIZE,bowl->x,bowl->y );

    refresh_surface( screen );
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */


void handle_events( SDL_Event *event, world_t *world, ball_t *bowl ){

    int x,y;
    while( SDL_PollEvent( event ) ) {

        //Si l'utilisateur a cliqué sur le X de la fenêtre

        if( event->type == SDL_QUIT ) {
            //On quitte le programme
            world->gameover = 1;
        }

        if( event->type == SDL_MOUSEBUTTONUP ){

           SDL_GetMouseState(&x, &y);
	         bowl->vx= SPEED_COEF*(x-bowl->x);
	         bowl->vy= SPEED_COEF*(y-bowl->y);
	      }
    }
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] ){

    SDL_Event event;
    world_t world;
    ball_t bowl;
    SDL_Surface *screen;

    screen = init_sdl( SCREEN_WIDTH, SCREEN_HEIGHT );

    init_data( &world,&bowl );
    init_graphics( screen,&world );


    while( !is_game_over(&world) ){

        handle_events( &event,&world,&bowl );
        update_data( &bowl );
        refresh_graphics( screen,&world,&bowl );
        SDL_Delay( 10 );
    }

    clean_data( &world );
    quit_sdl();

    return EXIT_SUCCESS;
}
