// #include "structures.h"


echiquier_t initechequier();

case_t case_t_de_pc(piece_t piece, couleur_t couleur);

piece_t piece_t_de_case_t(case_t caset);

couleur_t couleur_t_de_case_t(case_t caset);

echiquier_t set_case(echiquier_t echec, int ligne, int colonne, case_t newcase);

void get_case(echiquier_t echec, int ligne, int colonne, case_t newcase);

int indice_de_ligne (char indice);

char ligne_de_indice (int indice);

int indice_de_colonne (char indice);

char colonne_de_indice (int indice);

int char_ligne_valide(char indice);

int char_colonne_valide(char indice);