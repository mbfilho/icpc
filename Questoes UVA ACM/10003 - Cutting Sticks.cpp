#include <cstdio>
#include <cstring>

/*
Muito semelhante ao problema da multiplicação de matrizes. Suponha que i e j
sejam os lugares que serão cortados. Eu quero encontrar um 'k' tal que cortar
a madeira atual, cortar de [i..k] e depois de [k..j] tenha o custo mínimo. Se
i + 1 == j, então a madeira só tem os 2 endpoints, é o caso base, pois ela não irá ser 
cortada. Para facilitar o cáculo do tamanho do segmento da madeira coloquei 2 indices
a mais, cuts[0] = 0 e cuts[tam] = tamanho. Assim dá pra calcular o tamanho do segmento
[i..j] fazendo cuts[j] - cuts[i] e a primeira chamada recursiva tem de abranger toda
a madeira, ou seja, resolver( 0, tam ).  
*/

int cuts[52], memo[52][52];
int n;

int resolver( int i, int j ){
	if( memo[i][j] != -1 )
		return memo[i][j];
	if( i + 1 == j )
		return memo[i][j] = 0;
		
	int minimo = 0x7FFFFFFF, temp;
	for( int k = i + 1; k < j; ++k ){
		temp = resolver( i, k ) + resolver( k, j ) + cuts[j] - cuts[i];
		if( temp < minimo )
			minimo = temp;
	}
	
	return memo[i][j] = minimo;
}

int main(){
	int c;
	cuts[0] = 0;
	
	while( scanf( "%d", &n ) && n ){
		scanf( "%d", &c );
		for( int i = 1; i <= c; ++i )
			scanf( "%d", cuts + i );
		cuts[c + 1] = n;
		memset( memo, -1, sizeof( memo ) );
		printf( "The minimum cutting is %d.\n", resolver( 0, c + 1 ) );
	}
	
}
