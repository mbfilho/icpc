#include <cstdio>

int main(){
	char buf[ 20 ];
	scanf( "%s", buf );
	int cont = 0;
	for( int i = 0; buf[ i ]; ++i )
		if( buf[ i ] == '4' || buf[ i ] == '7' ) ++cont; 
	
	bool p = true;
	
	do{
		if( cont % 10 != 4 && cont % 10 != 7 ) p = false;
		cont /= 10;
	}while( cont );
	
	if( p )
		printf( "YES\n" );
	else
		printf( "NO\n" );
}

