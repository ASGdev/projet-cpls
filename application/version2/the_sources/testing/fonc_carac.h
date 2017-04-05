#ifndef FONC_CARAC_H
#define FONC_CARAC_H

// Le type fonction d'affichage d'un caractère
typedef union pointeur_ou_long {
  void *ptr;
  long entier;
} affiche_func_param_t;;

typedef void affiche_car_func_t (char,affiche_func_param_t);

#endif  // FONC_CARAC_H
