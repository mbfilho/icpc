#include <cstdio>
#define maior(a,b) (a) > (b) ? (a) : (b)
int memo[100][100];
int matriz[100][100];

int maior, linhas, colunas;

/*
Para cada uma das posições da matriz, teste a maior sequencia a partir dela.

*/

int resolver( int i, int j ){
	if( memo[i][j] != -1 )
		return memo[i][j];
	
	int len = 1;
	
	if( i - 1 >= 0 && matriz[i - 1][j] < matriz[i][j] )
		len = maior( len, 1 + resolver( i - 1, j ) ); 
	if( i + 1 < linhas && matriz[i + 1][j] < matriz[i][j] )
		len = maior( len, 1 + resolver( i + 1, j ) );
	if( j - 1 >= 0 && matriz[i][j - 1] < matriz[i][j] )
		len = maior( len, 1 + resolver( i, j - 1 ) );
	if( j + 1 < colunas && matriz[i][j + 1] < matriz[i][j] )
		len = maior( len, 1 + resolver( i, j + 1 ) );
	
	
	return memo[i][j] = len;
}

int main(){
	int casos, temp;
	char nome[50000];

	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%s %d %d", nome, &linhas, &colunas );
		
		for( int i = 0; i < linhas; ++i ){
			for( int j = 0; j < colunas; ++j ){
				memo[i][j] = -1;
				scanf( "%d", &matriz[i][j] );
			}
		}
		
		maior = -1;
		
		for( int i = 0; i < linhas; ++i ){
			for( int j = 0; j < colunas; ++j ){
				temp = resolver( i, j );
				if( temp > maior )
					maior = temp;
			}
		}

		printf( "%s: %d\n", nome, maior );
	}
}