#include "main.c"
#include "pieces.c"

// echiquier_t echiquier1(){
// 	int i=0;
// 	int j=0;
// 	echiquier_t echec;
// 	for (i = 0; i < 8; ++i){
// 		for (j = 0; j < 8; ++j){
// 			if (i+j%2 == 0){
// 				echec.tab[i][j] = (case_t){BLANC, VIDE};	
// 			}else{
// 				echec.tab[i][j] = (case_t){NOIR, VIDE};
// 			}
// 		}
// 	}
// 	// for(int i = 0; i<8; i++){
// 	// 	echiquier.tab[1][i].piece = P;
// 	// 	echiquier.tab[7][i].piece = P;
// 	// }
// }

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

void get_case(echiquier_t echec, int ligne, int colonne, case_t newcase){
	newcase = echec.tab[ligne][colonne];
}

int indice_de_ligne (char indice){
	return(((int) indice )-1);
}

char ligne_de_indice (int indice){
	return((char) indice +1);
}



int indice_de_colonne (char indice){
	switch (indice){
		case 'a':
			return 0;
			break;
		case 'b':
			return 1;
			break;
		case 'c':
			return 2;
			break;
		case 'd':
			return 3;
			break;
		case 'e':
			return 4;
			break;
		case 'f':
			return 5;
			break;
		case 'g':
			return 6;
			break;
		case 'h':
			return 7;
			break;
		default:
			return -1;
		  	break;
	}
}

char colonne_de_indice (int indice){
	switch (indice){
		case 0:
			return 'a';
			break;
		case 1:
			return 'b';
			break;
		case 2:
			return 'c';
			break;
		case 3:
			return 'd';
			break;
		case 4:
			return 'e';
			break;
		case 5:
			return 'f';
			break;
		case 6:
			return 'g';
			break;
		case 7:
			return 'h';
			break;
		default:
			return 'i';
		  	break;
	}
}

int char_ligne_valide(char indice){
	return indice_de_ligne(indice) != -1; // Si c'est vrai renvoie 1 et alors valide
}

int char_colonne_valide(char indice){
	return indice_de_colonne(indice) != -1;
}