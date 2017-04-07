







typedef struct coup_t {
  int numero;
  couleur_t joueur;
  echiquier_t courant;
  char commentaire [255];
  struct coup_t *prochain;
}coup_t;