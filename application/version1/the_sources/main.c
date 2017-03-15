#if defined LOCALE && LOCALE=FR
    int locale = 0; // locale is FR
#else
    int locale = 1; // locale is EN
#endif



int main(){
    printf("Locale is %d", locale);
}
