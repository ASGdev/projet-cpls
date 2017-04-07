#include <stdlib.h>
#include <stdio.h>
#include "../the_headers/vt100.h"
#include "vt100.h"

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
            if (j%2 == 0){
                if (i%2 == 0){
                    dessiner_case(NSB, ' ', afficher_octet, u);
                    dessiner_case(NSB, 'p', afficher_octet, u);
                    dessiner_case(NSB, ' ', afficher_octet, u);
                }else{
                    dessiner_case(BSN, ' ', afficher_octet, u);
                    dessiner_case(BSN, 'p', afficher_octet, u);
                    dessiner_case(BSN, ' ', afficher_octet, u);
                }
            }else{
                if (i%2 == 1){
                    dessiner_case(NSB, ' ', afficher_octet, u);
                    dessiner_case(NSB, 'p', afficher_octet, u);
                    dessiner_case(NSB, ' ', afficher_octet, u);
                }else{
                    dessiner_case(BSN, ' ', afficher_octet, u);
                    dessiner_case(BSN, 'p', afficher_octet, u);
                    dessiner_case(BSN, ' ', afficher_octet, u);
                } 
            }
        }
        printf("\n\n");
    }
}

int main(){
    maj_affichage();
	return 0;
}