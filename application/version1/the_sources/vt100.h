#ifndef VT100_H
#define VT100_H

#include "fonc_carac.h"

typedef enum { BLACK='0', RED='1', GREEN='2', YELLOW='3', BLUE='4', 
	       MAGENTA='5', CYAN='6', WHITE='7', DEFAULT_COLOR='9'}
        vt_couleur_t;

// BSB : piece blanche sur case blanche
// BSN : piece blanche sur case noire
// NSB : piece noire   sur case blanche
// NSN : piece noire   sur case noire
typedef enum {BSB=0,NSB=1,BSN=2,NSN=3} coloris_dessin_t;

// Modifier la paire de couleurs associee a un colori_t
void definir_coloris (coloris_dessin_t colori,
                      vt_couleur_t piece_c, 
                      vt_couleur_t case_c);

// Gènère une suite de codes ASCII pour afficher une case 
// Lettre : initiale de la piece
// Colori : combinaison de couleur piece/case
// Afficher : fonction utilisee pour envoyer un code vers l'ecran
//            (generalement un fonction qui appelle putchar)

void dessiner_case (coloris_dessin_t colori, 
                    char nom_piece, 
                    affiche_car_func_t *afficher, 
                    affiche_func_param_t param_func);
#endif  // VT100_H
