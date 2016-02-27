#include <cstdio>
#include <algorithm>
using namespace std;
#define N 100100
typedef long long ll;
//Poj
int num[ N ];
ll n;

ll com( ll k ){
	int pf = n - 1, pi = n - 2;
	ll total = 0;
	
	while( pi >= 0 ){
		while( pi >= 0 && num[ pf ] - num[ pi ] <= k ){
			total += pf - pi;
			--pi;
		}
	
		if( pi < 0 ) return total;
		
		while( pf > pi && num[ pf ] - num[ pi ] > k ) --pf;
	
		if( pf == pi ) --pi;
	}
	
	return total;
}

ll sem( ll k ){
	int pf = n - 1, pi = n - 2;
	ll total = 0;
	
	while( pi >= 0 ){
		while( pi >= 0 && num[ pf ] - num[ pi ] < k ){
			total += pf - pi;
			--pi;
		}
	
		if( pi < 0 ) return total;
		
		while( pf > pi && num[ pf ] - num[ pi ] >= k ) --pf;
	
		if( pf == pi ) --pi;
	}
	
	return total;
}


int main(){
	while( scanf( "%lld", &n ) == 1 ){
		for( int i = 0; i < n; ++i )
			scanf( "%d", num + i );
		sort( num, num + n );
		if( num[0] < 0 ) throw 1;
		ll med = n * ( n - 1 ) / 2;
		if( med & 1 ) med = 1 + med / 2;
		else med /= 2;
		
		ll ini = 0, fim = num[ n - 1 ] - num[ 0 ];
		ll resp = -1;
		bool ig = false;
		
		while( ini <= fim ){
			ll meio = ( ini + fim ) / 2;
			ll valsem = sem( meio ), valcom = com( meio );
			if( med > valsem && med <= valcom ){
				resp = meio;
				if( valsem != valcom ) break;
				ini = meio + 1;
			}else if( med > valcom )
				ini = meio + 1;
			else if( med <= valsem )
				fim = meio - 1;
		}
		
		if( resp == -1 ) throw 1;
		printf( "%lld\n", resp );
		
	}	
}







