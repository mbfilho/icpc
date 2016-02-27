#include <cstdlib>
#include <cstdio>
#include <iostream>

using namespace std;


int ma[ 100 ][ 100 ];

int main(){
	int cores, livre;
		
	scanf( "%d", &cores );
	
	int qtd = cores;
	cores *= 2;
	
	while( (qtd * ( qtd - 1 )) > cores )
		--qtd;
	
	
	livre = 1;
	
	for( int i = 0; i < qtd; ++i ){
		for( int j = 0; j < i; ++j ){
			ma[ i ][ j ] = ma[ j ][ i - 1 ];
		}
		
		for( int k = i; k < qtd - 1; ++k ){
			ma[ i ][ k ] = livre;
			livre++;
		} 
	}	
	
	printf( "%d\n", qtd );
	for( int i = 0; i < qtd; ++i ){
		printf( "%d ", qtd - 1 );
		for( int j = 0; j < qtd - 1; ++j ){
			printf( "%d", ma[ i ][ j ] );
			if( j == qtd - 2 )
				printf( "\n" );
			else
				printf( " " );
		}
	}
	
}

