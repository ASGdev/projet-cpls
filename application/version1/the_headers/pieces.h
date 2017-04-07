typedef enum piece_t {
	K, Q, B, N, R, P, VIDE, ETOILE // VIDE=' ' ETOILE= '*' 
} piece_t ;

piece_t piece_de_lettre (char piece);

char lettre_de_piece (piece_t piece);