// PIECE


typedef enum piece_t {
	K, Q, B, N, R, P, VIDE, ETOILE // VIDE=' ' ETOILE= '*' 
} piece_t ;

piece_t piece_de_lettre (char piece);

char lettre_de_piece (piece_t piece);

// ECHIQUIER

typedef enum couleur_t {
	BLANC, NOIR
} couleur_t ;

typedef struct case_t {
	couleur_t couleur;
	piece_t piece;
} case_t;

typedef struct echiquier_t {
	case_t tab[8][8];
} echiquier_t;




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


// COUP

typedef struct coup_t {
  int numero;
  couleur_t joueur;
  echiquier_t courant;
  char commentaire [255];
  struct coup_t *prochain;
} coup_t;

int creer_coup(coup_t *liste, char c[255], char move[4]);