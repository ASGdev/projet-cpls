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

typedef struct coup_t {
  int numero;
  couleur_t joueur;
  echiquier_t courant;
  char commentaire [255];
  struct coup_t *prochain;
} coup_t;


coup_t initechequier();

case_t case_t_de_pc(piece_t piece, couleur_t couleur);

piece_t piece_t_de_case_t(case_t caset);

couleur_t couleur_t_de_case_t(case_t caset);

echiquier_t set_case(echiquier_t echec, int ligne, int colonne, case_t newcase);

case_t get_case(echiquier_t echec, int ligne, int colonne, case_t newcase);

int indice_de_ligne(char l);
char ligne_de_indice(int i);
int indice_de_colonne(char l);
char colonne_de_indice(int i);
int char_ligne_valide(char l);
int char_colonne_valide(char l);


// COUP



int creer_coup(coup_t *liste, char c[255], char move[4], couleur_t coulJoueur);

char* getCoups(FILE *fp);


typedef struct {
    int inputMode;
    couleur_t couleurCourante;
    FILE *outputFile;
} game_t;

typedef struct{
    int numeroCourant;
    couleur_t couleurCourante;
    struct coup_t *premierCoup; // référence vers le premier coup
} listeCoup_t;