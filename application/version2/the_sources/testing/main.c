#if LOCALE==fr
    #define locale 0 // locale is FR
#else
    #define locale 1 // locale is EN
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "tap.h"

typedef enum piece_t { K = 0, Q = 1, B = 2, N = 3, R = 4, P=5, EMPTY=6, MARK=7} piece_t;
typedef enum couleur_t { white = 0, black = 1} couleur_t; 



typedef uint32_t echiquier_t[8];

typedef uint32_t case_t;



typedef struct {
    int numero; // nuémro du coup
    couleur_t joueur; // couleur du joueur
    echiquier_t courant; // echiquier courant
    char commentaire[255]; // commentaire sur 255 caractères max
    struct coup_t *prochain; // référence sur le prochain coup
} coup_t;

struct
{
    int numeroCourant;
    couleur_t couleurCourante;
    struct coup_t *premierCoup; // référence vers le premier coup
} listeCoup;





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
    /* on insère les coups dans une variable "tampon". Permet notamment de libérer le fichier et un accès plus rapide car en mémoire */

    /* itération pour découvrir le nombre de ligne du fichier - optimisation : utiliser realloc on-the-fly */
    int lines = 0;
    char *line;
    while (!feof(fp)) {
        fgets(line,150,fp);
        lines++;
    }

    printf("%d",lines);

    char *listeCoup = malloc(4 * lines * sizeof(char));

    int i = 0;
    char *l;
    while (1)
    {
        fscanf(fp, "%c%c%c%c", *(listeCoup + i), *(listeCoup + i + 1), *(listeCoup + i + 2), *(listeCoup + i + 3));
        i += 4;
        if( fscanf(input,"%s") == EOF )
           break;
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
int creer_coup(coup_t *liste, char c[255], char move[4]){
    // move pas sur la même case
    if (move[0] == move[2] && move[1] == move[3]){
        return -1;
    }

    //get couleur case et vérifier que ce coup est de couleur adverse que le coup précédent

    // le coup est validé
    t_coup *coup = malloc(sizeof(coup_t));
    *liste->numeroCourant++;
    *coup->numero = *liste->numeroCourant;
    



}


int main(int argc, char *argv[]){
    FILE *fp;

    if(argc < 2){
        printf("Pas de fichier de jeu fourni.\n");
    } else {
        // on assume que le chemin du fichier est dans le 1er paramètre
        fp = fopen(argv[1], "r");
        if(fp == NULL){
            printf("Erreur dans le fichier.\n");
            exit(66); //no input - see man sysexits
        }
    }

    echiquier_t *e = malloc(sizeof(echiquier_t));
    case_t *c = malloc(sizeof(case_t));

    //e = set_case(e, 0, 0, *c);
    //get_case(e, 0, 0, c);

    t_coup *listeCoup;






    printf("\n==== Tests ====\n");
    is(locale, fr);
    done_testing();
}


