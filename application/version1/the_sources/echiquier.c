#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include "prototype.h"

/**
 *
 * \return coup_t contenant l'échiquier initialisé le numero à 0, la couleur NOIR, aucun prochain coup, et commme commentaire "init"
 */

coup_t initechequier(){
	int i=0;
	int j=0;
	echiquier_t echec;
	for (i = 0; i < 8; ++i){
		for (j = 0; j < 8; ++j){
			if (i+j%2 == 0){
				echec.tab[i][j] = (case_t){BLANC, VIDE};
			}else{
				echec.tab[i][j] = (case_t){NOIR, VIDE};
			}
		}
	}
	for(int j = 0; j<8; j++){
		for (int i = 0; i < 8; ++i){
			if(j==6 || j==1){
				echec.tab[i][j].piece = P;
			}
			if ((i==0 && j==0) || (i==7 && j==0) || (i==0 && j==7) || (i==7 && j==7 )){
				echec.tab[i][j].piece = R;
			}

			if ((i==1 && j==0) || (i==6 && j==0) || (i==1 && j==7) || (i==6 && j==7)){
				echec.tab[i][j].piece = N;
			}

			if ((i==2 && j==0) || (i==5 && j==0) || (i==2 && j==7) || (i==5 && j==7)){
				echec.tab[i][j].piece = B;
			}

			if ((i==4 && j==0) || (i==3 && j==7)){
				echec.tab[i][j].piece = Q;
			}

			if ((i==3 && j==0) || (i==4 && j==7)){
				echec.tab[i][j].piece = K;
			}

			if (j==6 || j==7){
				echec.tab[i][j].couleur = NOIR;
			}
			if (j==0 || j==1){
				echec.tab[i][j].couleur = BLANC;
			}

		}
	}
	coup_t init;
	init.courant = echec;
	init.numero = 0;
	init.joueur = NOIR;
	init.prochain = NULL;
	strcpy(init.commentaire, "init");

	return (init);
}

/**
 *
 * \param piece : une piece de type piece_t
 * \param couleur : une couleur pour la piece de type couleur_t
 * \return une caset_t contenant la couleur et la piece donné en paramètre
 */

case_t case_t_de_pc(piece_t piece, couleur_t couleur){
	return ((case_t) {couleur, piece});
}

/**
 *
 * \param caset : une case_t
 * \return la piece contenu dans la case_t donnée en paramètre
 */

piece_t piece_t_de_case_t(case_t caset){
	return (caset.piece);
}

/**
 *
 * \param caset : une case_t
 * \return la couleur contenu dans la case_t donnée en paramètre
 */

couleur_t couleur_t_de_case_t(case_t caset){
	return (caset.couleur);
}

/**
 *
 * \param ehec : un échiquier
 * \param ligne : une ligne
 * \param colonne : une colonne
 * \param newcase : une case_t à ajoutée à l'échiquier mis en paramètre
 * \return l'échiquier avec la nouvelle case donnée en paramètre
 */

echiquier_t set_case(echiquier_t echec, int ligne, int colonne, case_t newcase){
	echec.tab[ligne][colonne] = newcase;
	return echec;
}

/**
 *
 * \param ehec : un échiquier
 * \param ligne : une ligne
 * \param colonne : une colonne
 * \param newcase : une case_t vide
 * \return la case_t donnée en paramètre avec le contenu de la case qu'il y a au coordonnées données
 */

case_t get_case(echiquier_t echec, int ligne, int colonne, case_t newcase){
	newcase = echec.tab[ligne][colonne];
	return newcase;
}

/**
 *
 * \param l : char indiquant une ligne de l'échiquier
 * \return l'entier correspondant au char de la ligne
 */

int indice_de_ligne(char l){
    return l-'0';
}

/**
 *
 * \param i : entier correspond à une ligne
 * \return char correspondant à l'entier donné pour la ligne
 */

char ligne_de_indice(int i){
    return i+'0';
}

/**
 *
 * \param l : char indiquant une colonne de l'échiquier
 * \return l'entier correspondant au char de la colonne
 */

int indice_de_colonne(char l){
    return l-'a';
}

/**
 *
 * \param i : entier correspond à une colonne
 * \return char correspondant à l'entier donné pour la colonne
 */

char colonne_de_indice(int i){
    return i+'a';
}

/**
 *
 * \param l : char indiquant une ligne donnée de l'échiquier
 * \return 0 si la ligne donnée est valide, 0 sinon
 */

int char_ligne_valide(char l){
    return (l-'1'>-1 && l-'1'<8);
}

/**
 *
 * \param l : char indiquant une colonne de l'échiquier
 * \return 0 si la colonne donnée est valide, 0 sinon
 */

int char_colonne_valide(char l){
    return (l-'a'>-1 && l-'a'<8);
}