#include <cstdio>
#include <cstring>
using namespace std;

char linha[ 2000000 ];

bool ehOh( int ini, int fim ){
	if( ini > fim ) return false;
	
	if( ini == fim )
		return linha[ ini ] == 'A';
	
	if( fim - ini + 1 < 3 ) return false;
	
	//OAB
	if( linha[ fim ] == 'B' && linha[ fim - 1 ] == 'A' ){
		return ehOh( ini, fim - 2 );
	}else if( linha[ fim ] == 'A' && linha[ ini ] == 'B' ){
		return ehOh( ini + 1, fim - 1 );
	}else
		return false;
}

int main(){
	int n;
	scanf( "%d", &n );
	
	while( n-- ){
		scanf( "%s", linha );
		int tam = strlen( linha );
		
		if( tam == 1 && linha[ 0 ] == 'A' )
			printf( "SIMPLE\n" );
		else if( tam >= 3 ){
			if( linha[ tam - 1 ] == 'B' && linha[ tam - 2 ] == 'A' && ehOh( 0, tam - 3 ) )
				printf( "FULLY-GROWN\n" );
			else if( linha[ 0 ] == 'B' && linha[ tam - 1 ] == 'A' && ehOh( 1, tam - 2 ) )
				printf( "MUTAGENIC\n" );
			else
				printf( "MUTANT\n" ); 
		}else
			printf( "MUTANT\n" );
	}
}



