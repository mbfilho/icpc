#include <cstdio>
#include <algorithm>
using namespace std;

const int soma_max = 1 + 500 * 100;

int bag[101];
bool dp[ soma_max ];
int moedas, soma, minimo;

int abs( int a ){
	if( a < 0 )
		return -a;
	return a;
}

int resolver(){
	minimo = 0x7fffffff;
	fill( dp, dp + soma + 1, false );
	dp[0] = true;
	
	for( int i = 0; i < moedas; ++i ){
		for( int sum = soma - bag[i]; sum >= 0; --sum ){
			if( dp[sum] ){
				dp[sum + bag[i]] = true;
				if( abs( soma - 2 * sum ) < minimo )
					minimo = abs( soma - 2 * sum );
			}
		}
	}

	return minimo;
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &moedas );
		soma = 0;
		
		for( int i = 0; i < moedas; ++i ){
			scanf( "%d", bag + i );
			soma += bag[i];
		}
			
		if( moedas == 0 )
			printf( "0\n" );
		else
			printf( "%d\n", resolver() );
	}
}
