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
    int fileProvided;
} game_t;

typedef struct {
    int numero; // numéro du coup
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

    #if LOCALE==0
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
                return (MARK);

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
                return (MARK);
        }
    #endif
    return (MARK);
}

char lettre_de_piece(piece_t p){
    // #if LOCALE==fr
    //     switch(lettre) {
    //         case 'R' :
    //             return(K);
    //             break;
    //         case 'D' :
    //             return (Q);
    //             break;
    //         case 'F' :
    //         case 'B' :
    //             break;
    //         default :
    //             return (MARK);

    //             break;
    //     }
    // #else
    //     switch(lettre) {
    //         case 'R' :
    //         case 'K' :
    //             return(K);
    //             break;
    //         case 'Q' :
    //         case 'D' :
    //             return (Q);
    //             break;
    //         case 'F' :
    //         case 'B' :
    //             break;
    //         default :
    //             break;
    //             return (MARK);
    //     }
    // #endif
}



char* getCoups(FILE *fp){
    /* on insère les coups dans une variable "tampon". Permet notamment de libérer le fichier et un accès plus rapide car en mémoire */

    /* itération pour découvrir le nombre de ligne du fichier - optimisation : utiliser realloc on-the-fly */
    int lineCount= 0;
    char string[5];
    while (!feof(fp)) {
        fscanf(fp, "%5c" , string);
        if(string[0] != '\n'){
            // si ligne pas vide
            lineCount++;
        }
    }

    #ifdef DEBUG
    	printf("Nombre de lignes du fichier : %d\n",lineCount);
    #endif

    char *listeCoup = malloc(4 * lineCount * sizeof(char) + sizeof(char));

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

    *(listeCoup + i + 1) = '\0';
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

void set_case(echiquier_t *e, int l, int c, case_t v){
    // uint32_t depart = 43690;
    // uint32_t mask = ~240;
    // uint32_t b = depart&mask;
    // printf("Case content b : %04x", b);
    // uint32_t value = 80;
    // uint32_t r = b|(value);
    // printf("Case content : %04x", r);

    #ifdef DEBUG
        printf("Ligne : %08x\n", *e[l]);
    #endif
    uint32_t ligne = *e[l]; // 0000001110101
    uint32_t mask = ~((15 << (c * 4))); // 1111111100001111111
    printf("Mask : %08x\n", mask);
    uint32_t t = ligne&mask; //0000 0000 1010
    printf("t : %08x\n", t);
    uint32_t newline = t|(v << (c * 4)); // 000 1111 0000
    printf("newline : %08x\n", t);
    *e[l] = newline;
    #ifdef DEBUG
        printf("Nouvelle ligne : %08x\n", *e[l]);
    #endif
}

void get_case(echiquier_t e, int l, int c, case_t* v){
    int w = (e[l] & (15 << (c * 4)));
    w =  w >> (c * 4);
    printf("Case content : %08x\n", w);
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
    printf("lv : %d\n", (l-'a'>-1 && l-'a'<8));
    return (l-'0'>-1 && l-'0'<8);
}

int char_colonne_valide(char l){
    printf("cv : %d\n", (l-'a'>-1 && l-'a'<8));
    return (l-'a'>-1 && l-'a'<8);
}

/* Create move */
int creer_coup(coup_t *liste, char c[255], char move[4]){
// move pas sur la même case
    // if(move[0] == move[2] && move[1] == move[3]){
    //     return -1;
    // }

    // int coldep = indice_de_colonne(move[0]);
    // int ligdep = indice_de_colonne(move[1]);
    // int colarr = indice_de_colonne(move[2]);
    // int ligarr = indice_de_colonne(move[3]);

    // // if (coldep<0 || ligdep<0 || colarr<0 || ligarr<0 || coldep>7 || ligdep>7 || colarr>7 || ligarr>7){ //Coup pas dans l'échiquier
    // if(char_ligne_valide(ligdep)!=1||char_ligne_valide(ligarr!=1)||char_colonne_valide(coldep)!=1||char_colonne_valide(colarr)!=1){ 
    //     return -1;
    // }

    // case_t casecour;
    // echiquier_t ecourant;

    // get_case(ecourant, ligarr, colarr, &casecour);

    // piece_t piececour = piece_t_de_case_t(casecour);
    // couleur_t couleurcour = couleur_t_de_case_t(casecour);


    // if (piececour!=EMPTY && couleur_t_de_case_t(casecour)==liste->joueur){ // case non vide et pièce de même couleur donc erreur
    //     return -1;
    // } else if((piececour!=EMPTY && couleur_t_de_case_t(casecour)!=liste->joueur) || piececour==EMPTY){
    //     *c='D';
    //     case_t newcase = case_t_de_pc(piececour,liste->joueur);
    //     //set_case(*ecourant,ligarr, colarr, newcase);
    // }

    // return 0;
}


void afficher_octet(char p, affiche_func_param_t f){
    putchar(p);
}

void maj_affichage(echiquier_t e){
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
            // colonne
            case_t casecour;
            get_case(e, i, j, &casecour);
            piece_t piececour = piece_t_de_case_t(casecour);
            char cpiececour = lettre_de_piece(piececour);
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

void executer_tests(){
    printf("=== Début des tests ===\n");
    #ifdef LOCALE
        #if LOCALE==0
            printf("FR\n");
        #else
            printf("EN\n");
        #endif
    #endif
    printf("Ligne a valide %d\n", char_ligne_valide('a'));
    printf("Ligne h valide %d\n", char_ligne_valide('h'));
    printf("Ligne i valide %d\n", char_ligne_valide('i'));

    printf("Colonne 0 valide %d\n", char_colonne_valide('0'));
    printf("Colonne 7 valide %d\n", char_colonne_valide('7'));
    printf("Colonne 8 valide %d\n", char_colonne_valide('8'));

    printf("indice_de_ligne de 1 = %d\n", indice_de_ligne('1'));

    printf("indice_de_colonne de a = %d\n", indice_de_colonne('a'));
    printf("indice_de_colonne de h = %d\n", indice_de_colonne('h'));

    echiquier_t *e = malloc(sizeof(echiquier_t));
    // set une case (2eme colonne)
    *e[0] = 1288;
    printf("E[0] = %08x\n", *e[0]);
    // get la case
    get_case(e, 0, 2, NULL);
    // modifie la case
    case_t c = 10;
    set_case(e, 0, 2, c);
    // get la case
    //get_case(e, 0, 2, NULL);
    printf("E[0] = %08x\n", *e[0]);
    printf("=== Fin des tests ===\n");
}

int main(int argc, char *argv[]){
    FILE *fp;
    char *l;

    game_t jeu;
    jeu.fileProvided = 0;

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


    /* initialisation */
    echiquier_t *e = malloc(sizeof(echiquier_t));
    //case_t *c = malloc(sizeof(case_t));

    //e = set_case(e, 0, 0, *c);
    //get_case(e, 0, 0, c);

    //t_coup *listeCoup;

    executer_tests();


    if (jeu.inputMode == 1){
    	printf("Ecrire \"fin\" pour finir la partie.\n");
    	printf("C'est parti !\n");
    }


    jeu.couleurCourante = black;

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

            coup_t *c;
            creer_coup(c, "", move);
        }
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
        continuer: printf("");
        char newMove[5];

        // ouverture du fichier de sortie
        char filename[257];
        FILE *fs;

        printf("Nom de fichier de sortie : ");
        fgets(filename, 257, stdin);
        // terminate string
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
            if(jeu.couleurCourante == white){
                printf("Joueur Noir joue : ");
                jeu.couleurCourante = black;
            } else {
                printf("Joueur Blanc joue : ");
                jeu.couleurCourante = white;
            }
            // move ou fin et clean entree
            fgets(newMove, 15, stdin);
            newMove[4]='\0';

            int correct = 0;
            if(char_ligne_valide(newMove[0])){
                if(char_colonne_valide(newMove[1])){
                    if(char_ligne_valide(newMove[2])){
                        if(char_colonne_valide(newMove[3])){
                            correct = 1;
                        }
                    }
                }
            }
            #ifdef DEBUG
            	printf("Nouveau mouvement = %s %d-", newMove, correct);
			#endif
            printf("\n");

            //ecriture dans le fichier (sauf fin)
            // TODO : ajout fichier de début si fichier de jeu défini
            // TODO : clean user input ?
            // TODO : gérer saut de ligne dans le fichier
            if(newMove[0] != 'f' && newMove[1] != 'i' && newMove[2] != 'n'){
            	//fprintf(fs, newMove);
                fputs(newMove, fs);
            	fprintf(fs, "\n");
            }


        } while(newMove[0] != 'f' && newMove[1] != 'i' && newMove[2] != 'n');
    }

}


