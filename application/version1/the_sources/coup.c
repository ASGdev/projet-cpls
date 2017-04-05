#include "echiquier.c"
#include <stdlib.h>

typedef struct coup_t {
	int numero;
	couleur_t joueur;
	echiquier_t courant;
	char commentaire [255];
	struct coup_t *prochain;
}coup_t;

int creer_coup(coup_t *liste, char c[255], char move[4]){
    // move pas sur la même case
    if(move[0] == move[2] && move[1] == move[3]){
        return -1;
    }

    int coldep = indice_de_colonne(move[0]);
    int ligdep = indice_de_colonne(move[1]);
    int colarr = indice_de_colonne(move[2]);
    int ligarr = indice_de_colonne(move[3]);

    // if (coldep<0 || ligdep<0 || colarr<0 || ligarr<0 || coldep>7 || ligdep>7 || colarr>7 || ligarr>7){ //Coup pas dans l'échiquier
    if(char_ligne_valide(ligdep)!=1||char_ligne_valide(ligarr!=1)||char_colonne_valide(coldep)!=1||char_colonne_valide(colarr)!=1){	
    	return -1;
    }

    case_t casecour;
    piece_t piececour = piece_t_de_case_t(casecour);
    couleur_t couleurcour = couleur_t_de_case_t(casecour);
   	get_case(liste->courant, ligarr, colarr, casecour);
   	if (piececour!=VIDE && couleur_t_de_case_t(casecour)==liste->joueur){ // case non vide et pièce de même couleur donc erreur
    	return -1;
   	}else if(piececour!=VIDE && couleur_t_de_case_t(casecour)!=liste->joueur || piececour==VIDE){
   		*c='D';
        case_t newcase = case_t_de_pc(piececour,liste->joueur);
   		set_case(liste->courant,ligarr, colarr, newcase);
   	}
}