#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define mp(x,y) make_pair(x,y)
#define MAXI 801
#define TAM 152

struct Card{
	int add, next;
	char s;
	
	bool operator<( const Card& c ) const{
		return add < c.add;
	}
}crt[ MAXI ];

char spell[ TAM ];
int len, n;

int start[ MAXI ], end[ MAXI ], pd[ TAM ][ MAXI ];


int score( int pos, int add ){

	int& maior = pd[ pos ][ add ];
	
	if( maior != -1 )
		return maior;
	
	maior = 0;

	if( pos == len - 1 ){
		for( int i = start[ add ]; i < end[ add ]; ++i ){
			if( spell[ pos ] == crt[ i ].s )
				maior = max( maior, crt[ i ].next );
		}
	}else{
		int temp;
		for( int i = start[ add ]; i < end[ add ]; ++i ){
			if( crt[ i ].s == spell[ pos ] ){
				temp = score( pos + 1, crt[ i ].next );
				if( temp )
					maior = max( maior, temp + crt[ i ].next );
			}
		}
	}
	
	return maior;
}


int main(){
	int casos;
	char aux[ 20 ];
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		for( int i = 0; i < n; ++i ){
			scanf( "%d %s %d", &crt[ i ].add, aux, &crt[ i ].next );
			crt[ i ].s = aux[ 0 ];
		}
		scanf( "%s", spell );
		len = strlen( spell );
		
		/*
		for( int i = 0; i < TAM; ++i ){
			for( int j = 0; j < MAXI; ++j )
				pd[ i ][ j ] = -1;
		}
		*/
		memset( pd, -1, sizeof( pd ) );
		
		sort( crt, crt + n );
		
		fill( start, start + MAXI, 0x7fffffff );
		fill( end, end + MAXI, -1 );
		
		for( int i = 0; i < n; ++i )
			end[ crt[ i ].add ] = i + 1;
		
		for( int i = n - 1; i >= 0; --i )
			start[ crt[ i ].add ] = i;
		
		printf( "%d\n", score( 0, 1 ) );
	}
}
