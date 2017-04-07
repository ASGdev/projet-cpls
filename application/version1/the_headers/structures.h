typedef enum couleur_t {
	BLANC, NOIR
} couleur_t ;

typedef enum piece_t {
	K, Q, B, N, R, P, VIDE, ETOILE // VIDE=' ' ETOILE= '*' 
} piece_t ;

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
}coup_t;