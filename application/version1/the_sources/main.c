#include <stdlib.h>
#include <stdio.h>
#include "../the_headers/vt100.h"
#include "vt100.h"
#include "string.h"
#include "prototype.h"


void afficher_octet(char p, affiche_func_param_t f){
    putchar(p);
}

void maj_affichage(echiquier_t echiquier){
    definir_coloris(BSN, WHITE, BLACK);
    definir_coloris(NSB, BLACK, WHITE);
    // FILE *fout = stdout;
    affiche_func_param_t u;

    case_t casecour;
    piece_t piececour;
	char cpiececour;

    printf("   a  b  c  d  e  f  g  h\n\n");
    for(int j = 0; j < 8; j++){
        putchar(j+1+'0');
        putchar(' ');
        for(int i = 0; i < 8; i++){
            casecour = get_case(echiquier, i, j, casecour);
            piececour = piece_t_de_case_t(casecour);
            cpiececour = lettre_de_piece(piececour);
            // printf("Piece cour%c", cpiececour); TOUJOUR R
            if (j%2 == 0){
                if (i%2 == 0){
                    dessiner_case(NSB, ' ', afficher_octet, u);
                    dessiner_case(NSB, cpiececour, afficher_octet, u);
                    dessiner_case(NSB, ' ', afficher_octet, u);
                }else{
                    dessiner_case(BSN, ' ', afficher_octet, u);
                    dessiner_case(BSN, cpiececour, afficher_octet, u);
                    dessiner_case(BSN, ' ', afficher_octet, u);
                }
            }else{
                if (i%2 == 1){
                    dessiner_case(NSB, ' ', afficher_octet, u);
                    dessiner_case(NSB, cpiececour, afficher_octet, u);
                    dessiner_case(NSB, ' ', afficher_octet, u);
                }else{
                    dessiner_case(BSN, ' ', afficher_octet, u);
                    dessiner_case(BSN, cpiececour, afficher_octet, u);
                    dessiner_case(BSN, ' ', afficher_octet, u);
                }
            }
        }
        printf("\n\n");
    }
}

int main(int argc, char *argv[]){

    coup_t echiquier = initechequier();
    maj_affichage(echiquier.courant);


    FILE *fp;

    game_t jeu;

    if(argc < 2){
        printf("Pas de fichier de jeu fourni : passage en mode clavier\n");
        // passage en mode clavier
        jeu.inputMode = 1;
    } else {
        // on assume que le chemin du fichier est dans le 1er paramètre
        fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("Erreur dans l'ouverture du fichier de jeu.\n");
            exit(66); //no input - voir man sysexits
        }
        // lecture du fichier
        // char* l = getCoups(fp);
    }

    if (jeu.inputMode == 1){
    	printf("Ecrire \"fin\" pour finir la partie.\n");
    	printf("C'est parti !\n");
    }

    jeu.couleurCourante = NOIR;


    if(jeu.inputMode == 0){
        // liste

    } else {
        // insertion clavier
        char newMove[5];
        // char poub;

        // ouverture du fichier de sortie
        char filename[257];
        FILE *fs;

        printf("Nom de fichier de sortie : ");
        fgets(filename, 257, stdin);
		for(int i=0; i<257; i++){
            if(filename[i] == '\n'){
                filename[i] = '\0';
            }
        }
        fs = fopen(filename, "w+");
        if(fs == NULL){
        	printf("\nErreur de fichier de sortie !\n\n");
        	exit(66);
        }

        do {
            newMove[0] = ' ';
            newMove[1] = ' ';
            newMove[2] = ' ';
            newMove[3] = ' ';
            newMove[4] = ' ';
            if(jeu.couleurCourante == BLANC){
                printf("Joueur Noir joue : ");
                jeu.couleurCourante = NOIR;
            } else {
                printf("Joueur Blanc joue : ");
                jeu.couleurCourante = BLANC;
            }
            // move ou fin
            fgets(newMove, 15, stdin);
            newMove[4]='\0';
            #ifdef DEBUG
            	printf("Newmove = %s-", newMove);
			#endif
            printf("\n");

            char comm [255];
            strcpy(comm, "newcoup");
            int sortie = creer_coup(&echiquier, comm, newMove, jeu.couleurCourante);
            printf("%d\n", sortie);

		    case_t casecour = get_case(echiquier.courant, 4, 0, casecour);
		    piece_t piececour = piece_t_de_case_t(casecour);
			char cpiececour = lettre_de_piece(piececour);
			printf("%c", cpiececour);

    		maj_affichage(echiquier.courant);

            //ecriture dans le fichier (sauf fin)
            if(newMove[0] != 'f' && newMove[1] != 'i' && newMove[2] != 'n'){
            	fputs(newMove,fs);
            	fprintf(fs, "\n");
            }
        } while(newMove[0] != 'f' && newMove[1] != 'i' && newMove[2] != 'n');
    }
}