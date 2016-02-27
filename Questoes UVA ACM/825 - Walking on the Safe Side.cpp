#include <cstdio>
#include <cstring>
using namespace std;

int n, m, cruz;

int lin[ 1000 ], col[ 1000 ];
int pd[ 200 ][ 200 ][ 400 ];

int cont( int i, int j, int passos ){
	if( passos > n + m - 2 ) return 0;
	
	int& soma = pd[ i ][ j ][ passos ];
	
	if( soma != -1 )
		return soma;
		
	for( int k = 0; k < cruz; ++k ){
		if( lin[ k ] == i && col[ k ] == j )
			return soma = 0;
	}
	
	if( i == n && j == m ){
		return soma = 1;
	}
	
	soma = 0;
	soma += cont( i + 1, j, passos + 1 );
	soma += cont( i, j + 1, passos + 1 );
	
	return soma;
}

int main(){
	int casos;
	char linha[ 1000 ];
	scanf( "%d", &casos );
	
	for( int caso = 1; caso <= casos; ++caso ){
		scanf( "%d %d", &n, &m );
		
		cruz = 0;
		gets( linha );//\n
		for( int i = 0; i < m; ++i ){
			gets( linha );
			int l, c, aux, aux2;
			
			sscanf( linha, "%d%n", &l, &aux );
			while( sscanf( linha + aux, "%d%n", &c, &aux2 ) != EOF ){
				lin[ cruz ] = l;
				col[ cruz++ ] = c;
				aux += aux2;
			}
			
		}
		memset( pd, -1, sizeof( pd ) );
		int soma = cont( 1, 1, 0 );
		printf( "%d\n", soma );
		
		if( caso != casos )
			printf( "\n" );
	}
}


