#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXI 100001

bool crivo[ MAXI ];
int primos[ MAXI ], contp;
int fatm[ MAXI ]; //Fatoracao do m
int p[ MAXI ]; //Os fatores
int contm;
int fatc[ MAXI ]; //Fatoracao do coeficiente binomial
int resp[ MAXI ], contr;

void gerar(){
	fill( crivo, crivo + MAXI, true );
	
	for( int i = 4; i <= MAXI; i += 2 )
		crivo[ i ] = false;
	
	for( int i = 3; i * i <= MAXI; i += 2 ){
		if( crivo[ i ] == false ) continue;
		
		for( int j = i * i; j <= MAXI; j += ( i << 1 ) )
			crivo[ j ] = false;
	}
	
	contp = 1;
	primos[ 0 ] = 2;
	for( int i = 3; i <= MAXI; i += 2 ){
		if( crivo[ i ] )
			primos[ contp++ ] = i;
	}
	
}

int main(){
	gerar();
	int n, m;
	
	while( scanf( "%d %d", &n, &m ) != EOF ){
		contm = 0;
		contr = 0;
		int temp = m;
		
		for( int i = 0; i < contp; ++i ){
			if( temp == 1 || primos[ i ] * primos[ i ] > m ) break;
			
			if( temp % primos[ i ] == 0 ){
				fatm[ contm ] = 0;		
				p[ contm ] = primos[ i ];
				
				do{
					temp /= primos[ i ];
					++fatm[ contm ];
				}while( temp % primos[ i ] == 0 );
				++contm;
			}
			

		}
		
		if( temp != 1 ){
			fatm[ contm ] = 1;
			p[ contm ] = temp;
			++contm;
		}
				
		fill( fatc, fatc + contm, 0 );
		for( int k = 1; k < n; ++k ){
			int nume = n - k, deno = k;
			
			for( int i = 0; i < contm; ++i ){
				while( nume % p[ i ] == 0 ){
					++fatc[ i ];
					nume /= p[ i ];
				}
				
				while( deno % p[ i ] == 0 ){
					--fatc[ i ];
					deno /= p[ i ];
				}
			}
			
			bool dm = false;
			for( int i = 0; i < contm; ++i ){
				if( fatc[ i ] < fatm[ i ] ){
					dm = true; 
					break;
				}
			}
			
			if( dm == false )
				resp[ contr++ ] = k + 1;				
		}
				
		printf( "%d\n", contr );
		if( contr ){
			printf( "%d", resp[ 0 ] );
			for( int i = 1; i < contr; ++i )
				printf( " %d", resp[ i ] );
		}
		printf( "\n" );
	}
}

