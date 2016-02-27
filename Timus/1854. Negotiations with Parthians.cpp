#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;


ll raiz( ll num ){
	ll ini = 0, fim = 1000000, resp;
	
	while( ini <= fim ){
		ll meio = ( ini + fim ) / 2, temp = meio * meio * meio;
		if( temp > num )
			fim = meio - 1;
		else if( temp < num ){
			resp = meio;
			ini = meio + 1;
		}else
			return meio;
	}
	
	return resp;
}

bool quad( ll num ){
	ll ini = 0, fim = 1000000000, meio;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		ll temp = meio * meio;
		if( temp == num ) return true;
		if( temp > num ) fim = meio - 1;
		else ini = meio + 1;
	}
	
	return false;
}


int main(){
	ll n, lim;
	scanf( "%lld", &n );
	lim = raiz( n );
	ll resp = -1;
	for( ll i = 1; i <= lim; i += 2 ){
		if( n % ( i * i ) == 0 )
			resp = max( resp, i * i );
	}

	for( ll i = 1; i <= lim; i += 2 ){
		if( n % i == 0 ){
			ll temp = n / i ;
			if( quad( temp ) )
				resp = max( resp, temp );
		}
	}	
	
	printf( "%lld\n", resp );
}



