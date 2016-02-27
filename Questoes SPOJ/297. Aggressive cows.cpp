#include <cstdio>
#include <algorithm>
using namespace std;

/*
	Complexidade O( estabulos * log(distMax) ) = O( 100.000 * log( 1000.000.000).
A idéia é utilizar busca binária para determinar o tamanho que o problema pede.
Serão log(n) distancias geradas. A cada uma destas distancias, deve-se verificar se
existe uma arrumação de vacas que respeita a distancia estipulada. Para isso, basta
colocar as vacas o mais proximo possivel uma das outras, desde que nenhuma esteja a
uma distancia menor que a estipulada. Se com essas limitações for possivel organizar
as vacas, então essa é uma distancia candidata e deve-se testar distancias menores.
Senao, deve-se testar distancias maiores.
*/

int n, c;
int pos[ 200000 ];

bool verificar( int tam ){
	int cont = 1, ult = pos[ 0 ];
	
	for( int i = 1; i < n && cont < c; ++i ){
		if( pos[ i ] - ult >= tam ){
			ult = pos[ i ];
			++cont;
		}
	}
	
	return cont == c;
}

int main(){
	int casos, dist;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &c );
		
		for( int i = 0; i < n; ++i )
			scanf( "%d", pos + i );
		sort( pos, pos + n );
		
		int mini = 0, maxi = pos[ n - 1 ] - pos[ 0 ], k;

		while( mini <= maxi ){
			k = ( mini + maxi ) / 2;
			if( verificar( k ) ){
				dist = k;
				mini = k + 1;
			}else
				maxi = k - 1;			
		}
		
		printf( "%d\n", dist );
	}
}
