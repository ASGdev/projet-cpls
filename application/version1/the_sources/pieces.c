typedef enum couleur_t {
	BLANC, NOIR
} couleur_t ;

typedef enum piece_t {
	K, Q, B, N, R, P, VIDE, ETOILE // VIDE=' ' ETOILE= '*' 
} piece_t ;


piece_t piece_de_lettre (char piece){
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
}

char lettre_de_piece (piece_t piece){
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
}