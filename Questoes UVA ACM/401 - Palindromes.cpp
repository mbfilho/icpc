#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char inv[ 300 ], nome[ 10000 ];
int tam;

void setInv( char a, char b ){
	inv[ a ] = b;
	inv[ b ] = a;
}

bool palindrome( int a, int b ){
	if( a == b )
		return true;
	if( a + 1 == b )
		return nome[ a ] == nome[ b ];
	
	if( nome[ a ] == nome[ b ] )
		return palindrome( a + 1, b - 1 );
	else
		return false;	
}

bool mirroed( int a, int b ){
	if( inv[ nome[ a ] ] == 0 || inv[ nome[ b ] ] == 0 ){
		return false;
	}
	
	if( a == b )
		return true;
	if( a + 1 == b )
		return inv[ nome[ a ] ] == nome[ b ];
	
	if( inv[ nome[ a ] ] == nome[ b ] )
		return mirroed( a + 1, b - 1 );
	else
		return false;
}

int main(){
	for( int i = 0; i <  300; ++i )
		inv[ i ] = 0;
		
	setInv( '3', 'E' );
	setInv( 'J', 'L' );
	setInv( 'S', '2' );
	setInv( '5', 'Z' );
	setInv( 'A', 'A' );
	setInv( 'H', 'H' );
	setInv( 'I', 'I' );
	setInv( 'M', 'M' );
	setInv( 'O', 'O' );
	setInv( 'T', 'T' );
	setInv( 'U', 'U' );
	setInv( 'V', 'V' );
	setInv( 'W', 'W' );
	setInv( 'X', 'X' );
	setInv( 'Y', 'Y' );
	setInv( '1', '1' );
	setInv( '8', '8' );
	
	while( scanf( "%s", nome ) != EOF ){
		tam = strlen( nome );
		bool pal = palindrome( 0, tam - 1 );
		bool mirror = mirroed( 0, tam - 1 );
		
		printf( "%s", nome );
		if( !pal && !mirror )
			printf( " -- is not a palindrome.\n" );
		else if( pal && mirror )
			printf( " -- is a mirrored palindrome.\n" );
		else if( pal )
			printf( " -- is a regular palindrome.\n" );
		else if( mirror )
			printf( " -- is a mirrored string.\n" );
		printf( "\n" );
		
	}
}

