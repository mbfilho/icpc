#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
#include <string>
#include <cmath>
using namespace std;

char n[ 100100 ];
int ar[ 2 ][ 200100 ];
int t, t2;


struct S{
	int s, p, ind;
	
	bool operator<( const S& a ) const{
		if( p == a.p )
			return s < a.s;
		
		return p < a.p;
	}
}aux[ 200010 ];

int build(){
	int tam = 1;
	int atual;
	for( int i = 0; i < t; ++i )
		ar[ 0 ][ i ] = n[ i ] - 'a';
	for( int i = t; i < t2; ++i )
		ar[ 0 ][ i ] = ar[ 0 ][ i - t ];
	
	int l = int ( ceil( log( t2 ) / log( 2 ) ) );

	for( int i = 1; i <= l; ++i ){
		for( int j = 0; j < t2; ++j ){
			aux[ j ].p = ar[ ( i - 1 ) % 2 ][ j ];
			
			if( j + tam >= t2 )
				aux[ j ].s = 0x7fffffff;
			else
				aux[ j ].s = ar[ ( i - 1 ) % 2 ][ j + tam ];
/*			
			if( i == 3 )
				cout << j << " " << aux[ j ].p << " " << aux[ j ].s << endl;
*/
			aux[ j ].ind = j;
		}
		
		sort( aux, aux + t2 );
		
		atual = 0;
		for( int j = 0; j < t2; ++j ){
			if( j == 0 )
				ar[ i % 2 ][ aux[ j ].ind ] = 0;
			else{
				if( aux[ j ].p == aux[ j - 1 ].p && aux[ j ].s == aux[ j - 1 ].s )
					ar[ i % 2 ][ aux[ j ].ind ] = ar[ i % 2 ][ aux[ j - 1 ].ind ];
				else{
					++atual;
					ar[ i % 2 ][ aux[ j ].ind ] = atual;
				}
			}
		}

		tam = tam * 2;
	}		
	
	int retorno, menor = 10000000;
	
	int k = l % 2;

	for( int i = 0; i < t; ++i ){
		if( ar[ k ][ i ] < menor ){
			retorno = i;
			menor = ar[ k ][ i ];
		}
	}

	return retorno;
}


int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %s", &t, n );
		t2 = t * 2;
		
		cout << build() << endl;
	}
	
	
}

