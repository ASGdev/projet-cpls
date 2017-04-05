#if LOCALE==fr
    #define locale 0 // locale is FR
#else
    #define locale 1 // locale is EN
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "vt100.h"

#include "tap.h"

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
    int numero; // nu�mro du coup
    couleur_t joueur; // couleur du joueur
    echiquier_t courant; // echiquier courant
    char commentaire[255]; // commentaire sur 255 caract�res max
    struct coup_t *prochain; // r�f�rence sur le prochain coup
} coup_t;

typedef struct
{
    int numeroCourant;
    couleur_t couleurCourante;
    struct coup_t *premierCoup; // r�f�rence vers le premier coup
} listeCoup_t;





piece_t piece_de_lettre(char lettre){

    if(locale == 0){
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
    }


}




char* getCoups(FILE *fp){
    /* on ins�re les coups dans une variable "tampon". Permet notamment de lib�rer le fichier et un acc�s plus rapide car en m�moire */

    /* it�ration pour d�couvrir le nombre de ligne du fichier - optimisation : utiliser realloc on-the-fly */
    int lineCount= 0;
    char string[5];
    while (!feof(fp)) {
        fscanf(fp, "%5c" , &string);
        lineCount++;
    }

    printf("%d\n",lineCount);

    char *listeCoup = malloc(4 * lineCount * sizeof(char));
    
    char c;
    int flag = 0;
    int i = 0;

    rewind(fp);
    while ((c = fgetc(fp)) != EOF){
        if(c != '\n'){
            printf("%c %d\n", c, flag);
            *(listeCoup + i) = c;
            i++;
            flag++;
        } else {
            if(flag < 4){
                printf("Erreur fichier\n");
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
    // move pas sur la m�me case
    if (move[0] == move[2] && move[1] == move[3]){
        return -1;
    }

    //get couleur case et v�rifier que ce coup est de couleur adverse que le coup pr�c�dent

    // le coup est valid�
    coup_t *coup = malloc(sizeof(coup_t));
    liste->numeroCourant++;
    //*coup.numero = *liste->numeroCourant;
    



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

    game_t jeux;

    if(argc < 2){
        printf("Pas de fichier de jeu fourni : passage en mode clavier\n");
        // passage en mode clavier
        jeux.inputMode = 1;      
    } else {
        // on assume que le chemin du fichier est dans le 1er param�tre
        fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("Erreur dans le fichier.\n");
            exit(66); //no input - voir man sysexits
        }
        // lecture du fichier
        char* l = getCoups(fp);
        for(int i = 0; i<60 ; i++){
            printf(" %c ", *(l+i));
        }
        
    }

    
    /* initialisation */
    echiquier_t *e = malloc(sizeof(echiquier_t));
    //case_t *c = malloc(sizeof(case_t));

    //e = set_case(e, 0, 0, *c);
    //get_case(e, 0, 0, c);

    //t_coup *listeCoup;

    printf("Nouvel �chiquier :\n");

    maj_affichage();

    printf("C'est parti !\n");

    if(jeux.mode == 1){
        jeux.couleurCourante = white;
        printf("Ecrire \"fin\" pour finir la partie.\n");
        printf("Joueur Blanc commence : \n");
    }

    if(jeux.mode == 0){
        // liste

    } else {
        // insertion clavier


    }



    printf("\n==== Tests ====\n");
    //is(locale, fr);
    done_testing();
}

