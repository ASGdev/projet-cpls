#if defined(LOCALE) && LOCALE==FR
    #define locale 0 // locale is FR
    #define enum Color { red, green, blue }
#else
    #define locale 1 // locale is EN
#endif

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    FILE *f;

    if(argc < 2){
        printf("Pas de fichier de jeu fourni.");
    } else {
        // on assume que le chemin du fichier est dans le 1er paramètre
        f = fopen(argv[1], "r");
        if(f == NULL){
            printf("Erreur dans le fichier.");
            exit(66); //no input - see man sysexits
        }
    }
    //printf("Locale is %d", locale);


}

char* getCoups(FILE *f){
    /* on insère les coups dans une variable "tampon". Permet notamment de libérer le fichier et un accès plus rapide car en mémoire */

    /* itération pour découvrir le nombre de ligne du fichier - optimisation : utiliser realloc on-the-fly */
    int lines = 0;
    while (!feof(fp)) {
        fgets(line,150,fp);
        lines++;
    }

    printf("%d",lines);

    char listeCoup* = malloc(4 * lines * sizeof(char));

    int i = 0;
    while (true)
    {
        l = fscanf(f, "%c%c%c%c", *(listeCoup + i), *(listCoup + i + 1), *(listCoup + i + 2), *(listCoup + i + 3));
        i += 4;
        if( l == EOF )
           break;
    }

    fclose(f);
    return listeCoup;
}

