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