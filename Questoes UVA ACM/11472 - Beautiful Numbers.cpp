#include <cstdio>

int m, n;
const int mod = 1000000007;

int pd[ 10 ][ 101 ][ 1 << 11 ];

int rec( int ini, int mask, int tam ){
	if( ini < 0 || ini >= n || tam > m )
		return 0;
	
	if( pd[ ini ][ tam ][ mask ] != -1 )
		return pd[ ini ][ tam ][ mask ];
	
	
	int soma = rec( ini + 1, mask | (1 << ( ini + 1 ) ), tam + 1 );
	soma = ( soma + rec( ini - 1, mask | ( 1 << ( ini - 1 ) ), tam + 1 ) ) % mod;
	if( mask == (1 << n) - 1 )
		++soma;
		
	return pd[ ini ][ tam ][ mask ] = soma;	
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &m );
		
		int soma = 0;
		
		for( int i = 0; i < n; ++i ){
			for( int j = 1; j <= m; ++j ){
				for( int k = 0; k < ( 1 << n ); ++k )
					pd[ i ][ j ][ k ] = -1;
			}
		}
		for( int i = 1; i < n; ++i )
			soma =  ( soma + rec( i, (1 << i), 1 ) ) % mod;
		printf( "%d\n", soma );
	}
}
