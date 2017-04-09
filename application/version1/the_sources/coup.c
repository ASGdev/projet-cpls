#include <stdlib.h>
#include <stdio.h>
#include "prototype.h"

int creer_coup(coup_t *liste, char c[255], char move[4], couleur_t coulJoueur){
    // move pas sur la même case

    if((move[0] == move[2]) && (move[1] == move[3])){
      printf("La case de départ est la meme que la case d'arrivee \n");
        return -1;
    }

    int correct = 0;
    if(char_ligne_valide(move[0])){
        if(char_colonne_valide(move[1])){
            if(char_ligne_valide(move[2])){
                if(char_colonne_valide(move[3])){
                    correct = 1;
                }
            }
        }
    }
    if (!correct){
      printf("Vous jouez hors de l'échiquier ou vous avez mis une commande non valide\n");
      return -2;
    }
    int coldep = indice_de_ligne(move[0])-1;
    int ligdep = indice_de_colonne(move[1]);
    int colarr = indice_de_ligne(move[2])-1;
    int ligarr = indice_de_colonne(move[3]);
    #if DEBUG
	    printf("%d\n", ligdep);
	    printf("%d\n", ligarr);
	    printf("%d\n", coldep);
	    printf("%d\n", colarr);
    #endif

    case_t casecour = get_case(liste->courant, ligdep, coldep, casecour);
    piece_t piececour = piece_t_de_case_t(casecour);
    couleur_t couleurcour = couleur_t_de_case_t(casecour);

    case_t casearr = get_case(liste->courant, ligarr, colarr, casearr);
    piece_t piecearr = piece_t_de_case_t(casearr);
    couleur_t couleurarr = couleur_t_de_case_t(casearr);

   	if (piececour == VIDE) {
      printf("Il n'y as pas de piece là ou vous essayez de jouer\n");
      return -3;
    }else if (piecearr!=VIDE && couleurcour == couleurarr){ // ON NE PEUT PAS MANGER UNE PIECE A NOUS
      printf("Vous ne pouvez pas manger une de vos piece\n");
    	return -4;
   	}else if((piececour!=VIDE && couleurcour == coulJoueur)){ // Si on essaye bien de bouger une de nos pièce on bouge
      printf("On se déplace\n");
      case_t newcase = case_t_de_pc(piececour,couleurcour);
   		liste->courant = set_case(liste->courant,ligarr, colarr, newcase);

      casecour.piece = VIDE;
      liste->courant = set_case(liste->courant,ligdep, coldep, casecour);
      return 1;
   	}else if(couleurcour!=coulJoueur){
      printf("Attention vous essayez de bouger une piece qui ne vous appartient pas ! \n");
      return-5;
    }
    printf("Une erreur c'est produite\n");
    return -10;
}


char* getCoups(FILE *fp){
    /* on insère les coups dans une variable "tampon". Permet notamment de libérer le fichier et un accès plus rapide car en mémoire */

    /* itération pour découvrir le nombre de ligne du fichier - optimisation : utiliser realloc on-the-fly */
    int lineCount= 0;
    char string[5];
    while (!feof(fp)) {
        fscanf(fp, "%5c" , string);
        lineCount++;
    }

    #ifdef DEBUG
      printf("Nombre de lignes du fichier : %d\n",lineCount);
    #endif

    char *listeCoup = malloc(4 * lineCount * sizeof(char));
    char c;
    int flag = 0;
    int i = 0;

    rewind(fp);
    while ((c = fgetc(fp)) != EOF){
        if(c != '\n'){
          #ifdef DEBUG
              printf("%c %d\n", c, flag);
            #endif

            *(listeCoup + i) = c;
            i++;
            flag++;
        } else {
            if(flag < 4){
                printf("\nErreur de données dans le fichier de jeu !\n");
                exit(65); // EX_DATAERR
            }
            flag = 0;
        }
    }

    fclose(fp);
    return listeCoup;
}