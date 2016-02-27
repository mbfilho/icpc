#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define M 20100
#define N 200
#define oo -1

int knap[ M ];
int cont[ M ][ 105 ];
int n, m;

int preco[ N ], sats[ N ];
char nome[ N ][ 50 ];

char aux[ 10 ];

void faz(){
	for( int i = 1; i <= m; ++i )
		knap[ i ] = oo;
	knap[ 0 ] = 0;
	
	memset( cont, 0, sizeof cont );
	
	for( int c = 0; c < n; ++c ){
		for( int s = 0; s <= m; ++s ){
			if( knap[ s ] == oo ) continue;
			
			int dt = min( s + sats[ c ], m );
			
			if( knap[ dt ] == oo || knap[ dt ] > knap[ s ] + preco[ c ] ){
				knap[ dt ] = knap[ s ] + preco[ c ];
				
				for( int i = 0; i <= c; ++i )
					cont[ dt ][ i ] = cont[ s ][ i ];
				cont[ dt ][ n ] = cont[ s ][ n ];
				
				++cont[ dt ][ c ];
				if( cont[ dt ][ c ] == 1 ) ++cont[ dt ][ n ];
				
			}else if( knap[ dt ] == knap[ s ] + preco[ c ] ){
				int qtd = cont[ s ][ n ];
				if( cont[ s ][ c ] == 0 ) ++qtd;
				
				if( qtd > cont[ dt ][ n ] ){
					for( int i = 0; i <= c; ++i ) cont[ dt ][ i ] = cont[ s ][ i ];
					cont[ dt ][ n ] = cont[ s ][ n ];
					
					++cont[ dt ][ c ];
					if( cont[ dt ][ c ] == 1 ) ++cont[ dt ][ n ];
				}
			}
		}
	}
}

int main(){
	scanf( "%d %d", &n, &m );
	m *= 1000;
	
	for( int i = 0; i < n; ++i ){
		scanf( "%s %d %s", nome[ i ], preco + i, aux );
		sats[ i ] =  0;
		
		bool passou = false;
		int c = 0;
		for( int j = 0; aux[ j ]; ++j ){
			if( aux[ j ] == '.' ){
				passou = true;
				continue;
			}
			
			if( passou ) ++c;
			sats[ i ] = sats[ i ] * 10 + aux[ j ] - '0';
		}
		
		while( c < 3 ){
			sats[ i ] *= 10;
			++c;
		}
	}
	
	faz();
	printf( "%d\n", knap[ m ] );
	for( int i = 0; i < n; ++i ){
		if( cont[ m ][ i ] )
			printf( "%s %d\n", nome[ i ], cont[ m ][ i ] );
	}
}


