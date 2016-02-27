#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;

/*
Se cada dado é uma tripla de probabilidades d1, d2, d3, então:
	d4 = P1 * d1 + P2 * d2 + P3 * d3, onde P1 + P2 + P3 = 1, ou seja,
d4 é resultado de uma soma baricentrica. Como P1, P2 e P3 devem ser positivos, d4
deve estar dentro do triangulo formado por d1, d2 e d3 ( se eles formarem 1 ).
Basta testar isso, tomando cuidado com os casos degenerativos.
*/
struct Ponto{
	ll x, y, z;
	
	Ponto(){}
	
	Ponto( ll a, ll b, ll c ){
		x = a;
		y = b;
		z = c;
	}
	
	Ponto operator%( const Ponto& p ) const{
		return Ponto( y * p.z - p.y * z, z * p.x - x * p.z, x * p.y - p.x * y );
	}
	
	ll operator|( const Ponto& p ) const{
		return x * p.x + y * p.y + z * p.z;
	}
	
	Ponto operator-( const Ponto& p ) const{
		return Ponto( x - p.x, y - p.y, z - p.z );
	}
	bool operator==( const Ponto& p ) const{
		return x == p.x && y == p.y && z == p.z;
	}
}p[ 3 ], ponto;

int main(){
	cin >> p[ 0 ].x >> p[ 0 ].y >> p[ 0 ].z;

	while( ( p[ 0 ].x | p[ 0 ].y | p[ 0 ].z ) ){
		for( int i = 1; i < 3; ++i )
			cin >> p[ i ].x >> p[ i ].y >> p[ i ].z;
		cin >> ponto.x >> ponto.y  >> ponto.z;

		
		Ponto aux[ 3 ];
		aux[ 0 ] = ( p[ 1 ] - p[ 0 ] ) % ( p[ 2 ] - p[ 0 ] );
		//Entra nesse if se os 3 pontos são colineares ( ou coincidentes )
		if( ( aux[ 0 ].x | aux[ 0 ].y | aux[ 0 ].z ) == 0 ){ 
		
			//Entra nesse if se os pontos são coincidentes
			if( p[ 0 ] == p[ 1 ] && p[ 2 ] == p[ 1 ] ){ 
				/*Se os pontos são coincidentes, so e possivel combinar os 3
					para formar o 4º se para cada coordenada dos 4 pontos, 
					ou essa coodenada é zero em todos ou diferente de 0 em todos.
					Essa condição é verificada pelo 'dm'.
				*/
				bool dm = ( ponto.x * p[ 0 ].x == 0 && ( ponto.x | p[ 0 ].x ) );
				dm = dm || ( ponto.y * p[ 0 ].y == 0 && ( ponto.y | p[ 0 ].y ) );
				dm = dm || ( ponto.z * p[ 0 ].z == 0 && ( ponto.z | p[ 0 ].z ) );
				
				if( dm )
					printf( "NO\n" );
				else
					printf( "YES\n" );
			}else{
				/*Aqui os pontos não são coincidentes( apenas colineares ).
				Nesse caso, para haver uma combinação, primeiramente, o 
				4º ponto deve também ser colinear. Além disso, ele deve estar
				'dentro' do segmento formado pelos '3' pontos ( na verdade 
				por 2 desses 3 pontos ). Essa condição é testada no for.  
				*/
				aux[ 0 ] = ( p[ 1 ] - p[ 0 ] ) % ( ponto - p[ 0 ] );
				
				if( ( aux[ 0 ].x | aux[ 0 ].y | aux[ 0 ].z ) == 0 ){
					bool dm = true;
					for( int i = 0; i < 3; ++i ){
						for( int j = 0; j < 3; ++j ){
							if( ( ( ponto - p[ i ] ) | ( p[ j ] - ponto ) ) > 0 ){
								dm = false;
								break;
							}
						}
					}
					
					if( dm )
						printf( "NO\n" );
					else
						printf( "YES\n" );
				}else
					printf( "NO\n" );
			}
		}else{
			/*Finalmente, aqui a entrada não representa um caso degenerativo.
			Basta testar, atraves do produto vetorial, se o 4º ponto está dentro
			do triangulo formado pelos outros 3. Tomando cuidado para não aceitar
			um ponto que esteja em uma aresta.
			*/
			for( int i = 0; i < 3; ++i )
				aux[ i ] = ( p[ ( i + 1 ) % 3 ] - p[ i ] ) % ( ponto - p[ i ] );
			ll temp = aux[ 0 ] | aux[ 1 ];
			
			if( temp > 0 ){
				temp = aux[ 0 ] | aux[ 2 ];
				
				if( temp > 0 )
					printf( "YES\n" );
				else
					printf( "NO\n" );
			}else
				printf( "NO\n" );
		}
			
		cin >> p[ 0 ].x >> p[ 0 ].y >> p[ 0 ].z;
	} 
}
