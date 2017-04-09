#include <stdlib.h>
#include <stdio.h>
#include "string.h"

#include "prototype.h"

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

	// case_t casecour;
	//    piece_t piececour;
	// char cpiececour;
	//    for (int i = 0; i < 8; ++i)
	//    {
	//    	for (int j = 0; j < 8; ++j)
	//    	{
	//    		casecour = get_case(echec, i, j, casecour);
	//            piececour = piece_t_de_case_t(casecour);
	//            cpiececour = lettre_de_piece(piececour);
	//    		printf("%c", piececour);
	//    	}
	//    	printf("\n");
	//    }
	coup_t init;
	init.courant = echec;
	init.numero = 0;
	init.joueur = NOIR;
	init.prochain = NULL;
	strcpy(init.commentaire, "init");

	return (init);
}

case_t case_t_de_pc(piece_t piece, couleur_t couleur){
	return ((case_t) {couleur, piece});
}

piece_t piece_t_de_case_t(case_t caset){
	return (caset.piece);
}

couleur_t couleur_t_de_case_t(case_t caset){
	return (caset.couleur);
}

echiquier_t set_case(echiquier_t echec, int ligne, int colonne, case_t newcase){
	echec.tab[ligne][colonne] = newcase;
	return echec;
}

case_t get_case(echiquier_t echec, int ligne, int colonne, case_t newcase){
	newcase = echec.tab[ligne][colonne];
	return newcase;
}


int indice_de_ligne(char l){
    return l-'0';
}

char ligne_de_indice(int i){
    return i+'0';
}

int indice_de_colonne(char l){
    return l-'a';
}

char colonne_de_indice(int i){
    return i+'a';
}

int char_ligne_valide(char l){
    return (l-'0'>-1 && l-'0'<8);
}

int char_colonne_valide(char l){
    return (l-'a'>-1 && l-'a'<8);
}