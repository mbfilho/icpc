#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define N 200100

char texto[ N * 2 ];
char pat[ N ];
int pi[ N * 2 ];
int tam;

void calc(){
	pi[ 0 ] = -1;
	int k = -1;
	
	for( int i = 1; i < tam; ++i ){
		while( k > -1 && pat[ k + 1 ] != pat[ i ] )
			k = pi[ k ];
		
		if( pat[ k + 1 ] == pat[ i ] )
			++k;
		pi[ i ] = k;
	}
}

bool kmp(){
	int k = -1;
	
	for( int i = 0, j = 0; j < 2 * tam; ++j, i = ( i + 1 ) % tam  ){
		while( k > -1 && texto[ i ] != pat[ k + 1 ] )
			k = pi[ k ];
		if( texto[ i ] == pat[ k + 1 ] )
			++k;
		if( k == tam - 1 && ( i != tam - 1 && i != 2 * tam - 1 ) ) return true;
	}
	
	return false;
}

bool ehPalindrome(){
	for( int i = 0; i < tam / 2; ++i ){
		if( texto[ i ] != texto[ tam - 1 - i ] )
			return false;
	}
	
	return true;
}

int main(){
	int n;
	scanf( "%d", &n );
	
	while( n-- ){
		scanf( "%s", texto );
		tam = strlen( texto );
		for( int i = 0; i < tam; ++i )
			pat[ i ] = texto[ tam - 1 - i ];
		pat[ tam ] = 0;
		
		calc();
		if( kmp() )
			printf( "alindrome\n" );
		else if( ehPalindrome() )
			printf( "palindrome\n" );
		else
			printf( "simple\n" );
	}
}




