#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../the_headers/vt100.h"


typedef enum piece_t { K = 0, Q = 1, B = 2, N = 3, R = 4, P=5, EMPTY=6, MARK=7} piece_t;
typedef enum couleur_t { white = 0, black = 1} couleur_t; 


typedef uint32_t echiquier_t[8];


typedef uint32_t case_t;

// 1 means user input
typedef struct {
    int inputMode;
    couleur_t couleurCourante;
    FILE *outputFile;
} game_t;

typedef struct {
    int numero; // nuémro du coup
    couleur_t joueur; // couleur du joueur
    echiquier_t courant; // echiquier courant
    char commentaire[255]; // commentaire sur 255 caractères max
    struct coup_t *prochain; // référence sur le prochain coup
} coup_t;

typedef struct
{
    int numeroCourant;
    couleur_t couleurCourante;
    struct coup_t *premierCoup; // référence vers le premier coup
} listeCoup_t;





piece_t piece_de_lettre(char lettre){

    #if LOCALE==fr
        switch(lettre) {
            case 'R' :
                return(K);
                break;
            case 'D' :
                return (Q);
                break;
            case 'F' :
            case 'B' :
                break;
            default :

                break;
        }
    #else
        switch(lettre) {
            case 'R' :
            case 'K' :
                return(K);
                break;
            case 'Q' :
            case 'D' :
                return (Q);
                break;
            case 'F' :
            case 'B' :
                break;
            default :
                break;
        }
    #endif
}




char* getCoups(FILE *fp){
    /* on insère les coups dans une variable "tampon". Permet notamment de libérer le fichier et un accès plus rapide car en mémoire */

    /* itération pour découvrir le nombre de ligne du fichier - optimisation : utiliser realloc on-the-fly */
    int lineCount= 0;
    char string[5];
    while (!feof(fp)) {
        fscanf(fp, "%5c" , &string);
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

case_t case_t_de_pc(piece_t p, couleur_t c){
    case_t t;

    t = p;
    t = t << 1;
    t = t + c;

    return t;
}

piece_t piece_t_de_case_t(case_t c){
    return c>>1;
}

couleur_t couleur_t_de_case_t(case_t c){
    return c&1;
}

echiquier_t *set_case(echiquier_t *e, int l, int c, case_t v){
    uint32_t depart = 43690;
    uint32_t mask = ~240;
    uint32_t b = depart&mask;
    printf("Case content b : %04x", b);
    uint32_t value = 80;
    uint32_t r = b|(value);
    printf("Case content : %04x", r);
}

void get_case(echiquier_t *e, int l, int c, case_t* v){
    int w = (*e[l] & (1111 << (c * 4)));
    printf("Case content : %04x", w);
}

int indice_de_ligne(char l){
    return l-'0';
}

char ligne_de_indice(int i){
    return i+'0';
}

int indice_de_colonne(char l){
    return l-'A';
}

char colonne_de_indice(int i){
    return i+'A';
}

int char_line_valide(char l){
    return ('l'>48 && 'l'<57);
}

int char_colonne_valide(char l){
    return ('l'>64 && 'l'<73);
}

/* Create move */
int creer_coup(listeCoup_t *liste, char c[255], char move[4]){
    // move pas sur la même case
    if (move[0] == move[2] && move[1] == move[3]){
        return -1;
    }

    //get couleur case et vérifier que ce coup est de couleur adverse que le coup précédent

    // le coup est validé
    coup_t *coup = malloc(sizeof(coup_t));
    liste->numeroCourant++;
    //*coup.numero = *liste->numeroCourant;
    



}

int valider_regle(coup_t coup) {
    


}

void afficher_octet(char p, affiche_func_param_t f){
    putchar(p);
}

void maj_affichage(){
    definir_coloris(BSN, WHITE, BLACK);
    definir_coloris(NSB, BLACK, WHITE);
    FILE *fout = stdout;   
    affiche_func_param_t u;


    printf("   a  b  c  d  e  f  g  h\n\n");
    for(int i = 0; i < 8; i++){
        // lignes
        putchar(i+1+'0');
        putchar(' ');
        for(int j = 0; j < 8; j++){
            // colonnes
            dessiner_case(BSN, ' ', afficher_octet, u);
            dessiner_case(BSN, 'p', afficher_octet, u);
            dessiner_case(BSN, ' ', afficher_octet, u);
        }
        printf("\n\n");
    }


}

int ecrire_coup_fichier(){

}

int main(int argc, char *argv[]){
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
        char* l = getCoups(fp);
        
    }

    
    /* initialisation */
    echiquier_t *e = malloc(sizeof(echiquier_t));
    //case_t *c = malloc(sizeof(case_t));

    //e = set_case(e, 0, 0, *c);
    //get_case(e, 0, 0, c);

    //t_coup *listeCoup;

    printf("Nouvel échiquier :\n");

    maj_affichage();

    if (jeu.inputMode == 1){
    	printf("Ecrire \"fin\" pour finir la partie.\n");
    	printf("C'est parti !\n");
    }
    

  
    jeu.couleurCourante = black;


    if(jeu.inputMode == 0){
        // liste

    } else {
        // insertion clavier
        char newMove[5];
        char poub;

        // ouverture du fichier de sortie
        char filename[257];
        FILE *fs;

        printf("Nom de fichier de sortie : ");
        fgets(filename, 257, stdin);
        filename[257] = '\0';

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
            if(jeu.couleurCourante == white){
                printf("Joueur Noir joue : ");
                jeu.couleurCourante = black;
            } else {
                printf("Joueur Blanc joue : ");
                jeu.couleurCourante = white;
            }
            // move ou fin
            fgets(newMove, 15, stdin);
            newMove[4]='\0';
            #ifdef DEBUG
            	printf("Newmove = %s-", newMove);
			#endif	
            printf("\n");

            //ecriture dans le fichier (sauf fin)
            if(newMove[0] != 'f' && newMove[1] != 'i' && newMove[2] != 'n'){
            	fprintf(fs, newMove);
            	fprintf(fs, "\n");
            }
            

        } while(newMove[0] != 'f' && newMove[1] != 'i' && newMove[2] != 'n');
        

    }

}


