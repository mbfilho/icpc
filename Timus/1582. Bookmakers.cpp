#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;


double k[ 3 ];
double melhor;

double round1( double value ){	
	return floor( value + 0.5 );
}

int main(){
	while( scanf( "%lf %lf %lf", k, k + 1, k + 2 ) != EOF ){
		melhor = -1;
		sort( k, k + 3 );
		
		double ini = 0, fim = 1000;
		for( int i = 0; i < 300; ++i ){
			double meio = ( ini + fim ) / 2;
			double temp = k[ 0 ] * meio;
			
			double a = temp / k[ 1 ], b = temp / k[ 2 ];
			
			if( a + b + meio > 1000 )
				fim = meio;
			else{
				melhor = max( melhor, temp );
				ini = meio;
			}
		}
		
		printf( "%d\n", int( round1( melhor ) ) );
	}
}

 