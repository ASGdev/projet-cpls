#include <stdlib.h>
#include <stdio.h>
#include "prototype.h"

piece_t piece_de_lettre (char piece){
	#if FR
		switch (piece){
			case 'R':
				return(K);
				break;
			case 'D':
				return(Q);
				break;
			case 'F':
				return(B);
				break;
			case 'C':
				return(N);
				break;
			case 'T':
				return(R);
				break;
			case 'P':
				return(P);
				break;
			case ' ':
				return(VIDE);
				break;
			default:
				return(ETOILE);
			  	break;
		}
	#else
		switch (piece){
			case 'K':
				return(K);
				break;
			case 'Q':
				return(Q);
				break;
			case 'B':
				return(B);
				break;
			case 'N':
				return(N);
				break;
			case 'R':
				return(R);
				break;
			case 'P':
				return(P);
				break;
			case ' ':
				return(VIDE);
				break;
			default:
				return(ETOILE);
			  	break;
		}
    #endif
}

char lettre_de_piece (piece_t piece){
	#if FR
		switch (piece){
			case K:
				return('R');
				break;
			case Q:
				return('D');
				break;
			case B:
				return('F');
				break;
			case N:
				return('C');
				break;
			case R:
				return('T');
				break;
			case P:
				return('P');
				break;
			case VIDE:
				return(' ');
				break;
			default:
				return('*');
			  	break;
		}
	#else
		switch (piece){
			case K:
				return('K');
				break;
			case Q:
				return('Q');
				break;
			case B:
				return('B');
				break;
			case N:
				return('N');
				break;
			case R:
				return('R');
				break;
			case P:
				return('P');
				break;
			case VIDE:
				return(' ');
				break;
			default:
				return('*');
			  	break;
		}
	#endif
	return('*');
}