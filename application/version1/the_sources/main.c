#include <stdlib.h>
#include <stdio.h>
#include "../the_headers/vt100.h"
#include "vt100.h"
#include "string.h"
#include "prototype.h"

/**
 *
 * \param argc : nombre d'argument (non utilisé par l'utilisateur)
 * \param argv : 1 argument, le fichier de jeu en entrée
 * \return 0 si aucune erreur ou sortie utilisateur par CTRL-D
 * \return 65 si problème d'entrée/sortie de fichier
 * Point d'entrée et interfacage avec l'utilisateur
 */

int main(int argc, char *argv[]){
	#if FR
		printf("Mode Francais\n");
	#else
		printf("Mode Anglais\n");
	#endif

	#if DEBUG
		printf("Mode debug actif\n");
	#else
		printf("\n");
	#endif

    coup_t echiquier = initechequier();
    maj_affichage(echiquier.courant);


    FILE *fp;
    char *l;

    game_t jeu;
    jeu.fileProvided = 0;
    jeu.couleurCourante = NOIR;

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
        l = getCoups(fp);
        jeu.fileProvided = 1;
        jeu.inputMode = 0;
    }

    if (jeu.inputMode == 1){
    	printf("Ecrire \"fin\" pour finir la partie.\n");
    	printf("C'est parti !\n");
    }

    if(jeu.inputMode == 0){
        // liste
        int i = 0;
        char move[4];
        while(l[i] != '\0'){
            move[0] = l[i];
            move[1] = l[i+1];
            move[2] = l[i+2];
            move[3] = l[i+3];
            i+=4;

            if(jeu.couleurCourante == BLANC){
                printf("Joueur Noir joue : ");
                jeu.couleurCourante = NOIR;
            } else {
                printf("Joueur Blanc joue : ");
                jeu.couleurCourante = BLANC;
            }
            // move ou fin
            int sortie = 0;
            while(sortie != 1){
	            printf("\n");
	            char comm [255];
	            strcpy(comm, "newcoup");
	            sortie = creer_coup(&echiquier, comm, move, jeu.couleurCourante);
                if(sortie != 1){
                	printf("\nErreur de données dans le fichier de jeu !\n");
                	exit(65);
                }
            }
        }
    	maj_affichage(echiquier.courant);
        printf("Fin du fichier. Voulez-vous continuer (oui : o, fin : autre) ? ");

        char answer;
        answer = getchar();
        // clean retour chariot
        char p = getchar();
        if(answer == 'o'){
            jeu.inputMode = 1;
            #ifdef DEBUG
                printf("Answer : %c\n", answer);
            #endif
            // saute sur partie insertion clavier
            goto continuer;
        }

    } else {
		// insertion clavier
        continuer: printf(" ");
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

        // Sauvegarde le contenu de l'ancien fichier dans le nouveau
        if(jeu.inputMode == 1 && jeu.fileProvided){
            //ajout fichier de début si fichier de jeu défini
            #ifdef DEBUG
                printf("Sauvegarde du fichier...\n");
            #endif
            rewind(fs);
            int i = 0;
            char move[5];
            while(l[i] != '\0'){
                move[0] = l[i];
                move[1] = l[i+1];
                move[2] = l[i+2];
                move[3] = l[i+3];
                move[4] = '\n';
                i+=4;
                fputs(move, fs);
            }
        }

        do {
            if(jeu.couleurCourante == BLANC){
                printf("Joueur Noir joue : ");
                jeu.couleurCourante = NOIR;
            } else {
                printf("Joueur Blanc joue : ");
                jeu.couleurCourante = BLANC;
            }
            // move ou fin
            int sortie = 0;
            while(sortie != 1){
	            newMove[4]='\0';
	            if(fgets(newMove, 15, stdin) == NULL){
	            	printf("\nFin du jeu.\n");
	                exit(0);
	            }
	            #ifdef DEBUG
	            	printf("Newmove = %s-", newMove);
				#endif
	            printf("\n");
	            char comm [255];
	            strcpy(comm, "newcoup");
	            sortie = creer_coup(&echiquier, comm, newMove, jeu.couleurCourante);
                if(sortie != 1){
                	printf("Veuillez rejouer : ");
                }
            }
    		maj_affichage(echiquier.courant);

            //ecriture dans le fichier (sauf fin)
        } while(newMove != NULL);
    }

    return 0;
}


