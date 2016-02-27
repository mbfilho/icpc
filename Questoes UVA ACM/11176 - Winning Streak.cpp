#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

double p;
int n;
double power[ 600 ];
double pd[ 501 ][ 501 ];

double rec( int ini, int fim, int qtd ){
	int tam = fim - ini + 1;
	if( tam < 0 ) return 1.0;
	if( qtd == 0 ) return pow( 1 - p, tam );
	
	double &soma = pd[ tam ][ qtd ];
	if( soma >= 0 ) return soma;
	soma = 0;
	
	double ls;
	for( int i = ini; i + qtd - 1 <= fim; ++i ){
		ls = 1.0;
		if( i != ini )
			ls = 1 - p;
		if( i + qtd <= fim )
			ls *= ( 1 - p );
		
		soma += rec( ini, i - 2, qtd - 1 ) * rec( i + qtd + 1, fim, qtd ) * ls * power[ qtd ]; 
	}
	
	soma += rec( ini, fim, qtd - 1 );
	
	return soma;
}

int main(){
	
	while( scanf( "%d %lf", &n, &p ) != EOF && n ){
		power[ 0 ] = 1;
		for( int i = 1; i <= n; ++i )
			power[ i ] = p * power[ i - 1 ];
		
		memset( pd, -1, sizeof( pd ) );
		double soma = 0;
		for( int i = 1; i <= n; ++i )
			soma += i * ( rec( 0, n - 1, i ) - rec( 0, n - 1, i - 1 ) );
		
		printf( "%lf\n", soma );
	}
}



