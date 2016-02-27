#include <cstdio>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;

int n, k, raiz;
ll soma;

ll pa( int a1, int an ){
	ll qtd = an - a1 + 1;
	return ( ( an + a1 ) * qtd ) / 2;
}

int main(){	
	while( scanf( "%d %d", &n, &k ) != EOF ){
		if( n == 1 )
			printf( "0\n" );
		else{
			raiz = (int) sqrt( k );
			soma = 0;
			
			for( int i = 1; i <= min( n, raiz ); ++i )
				soma += ( i * ( k / i ) ); 
			
			int ini, fim, val;
			
			ini = raiz + 1;
			val = k / ini;
						
			while( ini <= n && val != 0 ){
				fim = min( n, ( k / val ) );
		//		printf( "%d %d %d\n", ini, fim, val );
				soma += val * pa( ini, fim ); 
				ini = fim + 1;
				val = k / ini;
			}		
			
			soma = ll( n ) * k - soma;
			printf( "%lld\n", soma );
			//cout << soma << endl;
		}
	}
}


