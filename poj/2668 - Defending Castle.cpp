#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

//Poj

ll raiz( ll num ){
	ll ini = 0, fim = num, meio, ret;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		if( meio * meio > num )
			fim = meio - 1;
		else if( meio * meio == num ){
			ret = meio;
			break;
		}else{
			ret = meio;
			ini = meio + 1;
		}
	}
	
	return ret;
}

ll d, n;
int main(){
	while( scanf( "%lld %lld", &d, &n ) == 2 && ( n | d ) ){
		ll root = raiz( d );
		ll soma = 0;
		
		for( int i = 1; i <= min( root, n ); ++i )
			soma += ( d + i - 1 ) / i;
		ll x0 = root + 1, xf;
		
		while( x0 <= n ){
			ll val = ( d + x0 - 1 ) / x0;
			if( val == 1 )
				xf = n + 1;
			else{
				ll aux = val - 1;
				xf = ( d + aux - 1 ) / aux;
			}
			xf = min( xf, n + 1 );
			soma += ( xf - x0 ) * val;
			x0 = xf;
		}
		
		printf( "%lld\n", soma );
		
	}
}


