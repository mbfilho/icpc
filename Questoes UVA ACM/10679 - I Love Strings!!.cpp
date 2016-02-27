#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200000

struct No{
	int id, ini, fim;
	
	bool operator<( const No& n ) const{
		if( ini != n.ini )
			return ini < n.ini;
		return fim < n.fim;
	}
};

No nos[ N ];
char text[ N ];
int sufix[ N ][ 2 ];
int tam;
int pot;

char query[ 2000 ];

void array(){
	tam = strlen( text );
	pot = 1;
	while( ( 1 << ( pot - 1 ) ) < strlen( text ) ) ++pot;
	--pot;
	
	for( int i = 0; i < tam; ++i )
		sufix[ i ][ 0 ] = text[ i ] - 'A';
	
	int size = 1, val = 2;
	
	int cont;
	while( val / 2 < tam ){
		cont = 0;
		for( int i = 0; i < tam; ++i ){
			nos[ cont ].id = i;
			nos[ cont ].ini = sufix[ i ][ ( size - 1 ) & 1 ];
			if( i + val < tam )
				nos[ cont ].fim = sufix[ i + val ][ ( size - 1 ) & 1 ];
			else
				nos[ cont ].fim = -1;
			++cont;
		}
		
		sort( nos, nos + cont );
		int x = 0;
		sufix[ nos[0].id ][ size & 1 ] = 0;
		for( int i = 1; i < cont; ++i ){
			if( nos[ i - 1 ].ini == nos[ i ].ini && nos[ i - 1 ].fim == nos[ i ].fim )
				sufix[ nos[ i ].id ][ size & 1 ] = x;
			else
				sufix[ nos[ i ].id ][ size & 1 ] = ++x;
		}
		
		++size;
		val *= 2;
	}
	
	pot = pot & 1;
}

bool search(){
	int ini = 0, fim = tam - 1, meio;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		int ret = 0;
		//text - query
		for( int i = 0; !ret && query[ i ]; ++i ){
			if( text[ sufix[ meio ][ pot ] + i ] == 0 ) ret = -1;
			if( text[ sufix[ meio ][ pot ] + i ] > query[ i ] ) ret = 1;
			else if( text[ sufix[ meio ][ pot ] + i ] < query[ i ] ) ret = -1; 
		}
		
		if( ret == 0 ) return true;
		if( ret < 0 ) ini = meio + 1;
		else fim = meio - 1;
	}
	
	return false;
}


int main(){
	int casos;
	scanf( "%d", &casos );
	for( int c = 1; c <= casos; ++c ){
		scanf( "%s", text );
		array();
//		for( int i = 0; i < tam; ++i )
//			printf( ">> %d\n", sufix[ i ][ pot ] );
		int q;
		scanf( "%d", &q );
		while( q-- ){
			scanf( "%s", query );
			if( search() )
				printf( "y\n" );
			else
				printf( "n\n" );
		}
	}
}

