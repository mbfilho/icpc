#include <cstdio>
#include <cstdlib>
#include <iostream>

#define max 15

class Numero{
	public:
		int numero[ max ], tam;
		
		Numero( int arg ){
			memset( numero, 0, max * sizeof( int ) );
			numero[ 0 ] = arg;
			tam = 1;
		}

		inline void somar( const Numero& outro, Numero& resultado ){
			int carry = 0;
			resultado.tam = max;
			
			for( int i = 0; i < max; ++i ){
				resultado.numero[ i ] = numero[ i ] + outro.numero[ i ] + carry;
				
				if( resultado.numero[ i ] >= 10 ){
					resultado.numero[ i ] -= 10;
					carry = 1;
				}else
					carry = 0;
				
				
				if( resultado.numero[ i ] == 0 ){
					if( i < resultado.tam )
						resultado.tam = i;
				}else
					resultado.tam = i + 1;
					
			}
		}
		
		inline void subtrair( const Numero& outro, Numero& resultado ){
			int carry = 0;
			resultado.tam = max;
			
			for( int i = 0; i < max; ++i ){
				resultado.numero[ i ] = numero[ i ] - outro.numero[ i ] - carry;
				
				if( resultado.numero[ i ] < 0 ){
					resultado.numero[ i ] += 10;
					carry = 1;
				}else
					carry = 0;
				
				
				if( resultado.numero[ i ] == 0 ){
					if( i < resultado.tam )
						resultado.tam = i;
				}else
					resultado.tam = i + 1;
				
			}
		}

		inline void ficarIgualA( Numero& outro ){
			for( int i = 0; i < max; ++i )
				numero[ i ] = outro.numero[ i ];
			
			tam = outro.tam;
		}
		
};

int main(){
	int n,  cenarios, cont = 1;
	Numero temp(0), soma(0), perigosos(0);
	Numero const_2( 2 ), const_1( 1 );
//	freopen( "in.txt", "r", stdin );
//	freopen( "out.txt", "w", stdout );
	scanf( "%d", &cenarios );

	while( cenarios-- ){
		scanf( "%d", &n );

			soma.ficarIgualA( const_2 );
			
			perigosos.ficarIgualA( const_1 );
			
			for( int bits = 2; bits <= n; ++bits ){
				temp.ficarIgualA( soma );
				soma.somar( soma, soma );
				soma.subtrair( perigosos, soma );
				//soma = ( soma + soma ) - perigosos; 
				temp.subtrair( perigosos, perigosos );
				//perigosos = temp - perigosos;
				
			} 
				
		printf( "Scenario #%d:\n", cont++ ); 
		for( int i = soma.tam - 1; i >= 0; --i )
			printf( "%d", soma.numero[ i ] );
		printf( "\n\n" );
	}
	
}

