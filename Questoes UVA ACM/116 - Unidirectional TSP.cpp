#include <cstdio>
#define MENOR( a, b ) (a) < (b) ? (a) : (b)

typedef long long ll;

int matriz[11][101];
ll memo[11][101];
int next[11][101];
int seq[101];

int lin, col;

ll responder( int i, int j ){
	if( next[i][j] )
		return memo[i][j];
			
	if( j == col ){
		next[i][j] = -1;
		return memo[i][j] = matriz[i][j];
	}
	
	ll frente, nord, sud, menor;
	
	menor = frente = responder( i, j + 1 );
	next[i][j] = i;
	
	int indice = (i == 1)? lin : (i - 1);
	nord = responder( indice, j + 1 );
	if( nord < menor ){
		menor = nord;
		next[i][j] = indice;
	}else if( nord == menor )
		next[i][j] = MENOR( next[i][j], indice );
				
	indice = (i == lin)? 1 : ( i + 1 );
	sud = responder( indice, j + 1 );
	if( sud < menor ){
		menor = sud;
		next[i][j] = indice;
	}else if( sud == menor )
		next[i][j] = MENOR( next[i][j], indice );

	return memo[i][j] = matriz[i][j] + menor;
		
}

int preencher( int i ){
	int cont = 0;
	int j = 1;
	
	while( i != -1 ){
		seq[cont] = i;
		i = next[i][j];
		++j;
		++cont;
	}
}

int main(){
	ll melhor, temp;
	
	while( scanf( "%d %d", &lin, &col ) != EOF ){
		for( int i = 1; i <= lin; ++i ){
			for( int j = 1; j <= col; ++j ){
				scanf( "%d", &matriz[i][j] );
				next[i][j] = 0;
			}
		}
		
		melhor = responder( 1, 1 );
		preencher( 1 );
		
		for( int i = 2; i <= lin; ++i ){
			temp = responder( i, 1 );
			if( temp < melhor ){
				melhor = temp;
				preencher( i );
			}
		}
	
		--col;
		for( int i = 0; i < col; ++i )
			printf( "%d ", seq[i] );
		printf( "%d\n", seq[col] );
		printf( "%d\n", melhor );
		
	}
}

