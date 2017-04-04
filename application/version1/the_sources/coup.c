#include "echiquier.c"
#include <stdlib.h>

typedef struct coup_t {
	int numero;
	couleur_t joueur;
	echiquier_t courant;
	char commentaire [255];
	struct coup_t *prochain;
}coup_t;

coup_t creer_coup(char newcoup){

}