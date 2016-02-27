#include <cstdio>
#define LIM 200

int memo[ LIM ][ LIM ];
int array[ LIM ];

int somatorio( int a, int b ){
	int retorno = 0;
	
	for( ; a <= b; ++a )
		retorno += array[ a ];
	return retorno;
}

void reset(){
	for( int i = 0; i < LIM; ++i ){
		for( int j = 0; j < LIM; ++j )
			memo[ i ][ j ] = -1;
	}
}

int best( int ini, int fin ){
	if( memo[ ini ][ fin ] != -1 )
		return memo[ ini ][ fin ];
	
	if( ini == fin )
		return memo[ ini ][ fin ] = array[ ini ];
		
	int soma;
	int melhor;
	int max = somatorio( ini, fin );
	
	soma = array[ ini ];
	for( int i = ini + 1; i <= fin; ++i ){
		melhor = best( i, fin );
		if( soma - melhor > max )
			max = soma - melhor;
		soma += array[ i ];
	}
	
	soma = array[ fin ];
	for( int j = fin - 1; j >= ini; --j ){
		melhor = best( ini, j );
		if( soma - melhor > max )
			max = soma - melhor;
		soma += array[ j ];
	}
	
	return memo[ ini ][ fin ] = max;
}

int main(){
	int qtd;
	
	while( scanf( "%d", &qtd ) && qtd ){
		for( int i = 0; i < qtd; ++i )
			scanf( "%d", &array[ i ] );
			
		reset();
		printf( "%d\n", best( 0, qtd - 1 ) );
	}
}