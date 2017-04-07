typedef struct coup_t {
	int numero;
	couleur_t joueur;
	echiquier_t courant;
	char commentaire [255];
	struct coup_t *prochain;
}coup_t;

int creer_coup(coup_t *liste, char c[255], char move[4]);