#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

ll gcd( ll a, ll b ){
	ll temp;
	
	while( b ){
		temp = a % b;
		a = b;
		b = temp;
	}
	
	return a;
}

int dig( ll a ){
	int resp = 0;
	while( a ){
		++resp;
		a /= 10;
	}
	
	return resp;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		ll num;
		scanf( "%lld", &num );
		
		int s = dig( num );
		ll resp = -1;
		
		for( int d = 1; d <= s; ++d ){
			for( int n = 2; n * d <= 2 * s; ++n ){
				if( d * n < s ) continue;
				
				ll soma = 0, pot = 1, passo = 1;
				for( int i = 1; i <= d; ++i )
					passo *= 10;
					
				for( int i = 0; i < n; ++i ){
					soma += pot;
					pot *= passo;
				}
				
				ll k = num / gcd( num, soma );
				
				if( dig( k ) > d ) continue;
				
				ll temp = k;
				while( dig( k ) != d )
					k += temp;
				
				if( resp == -1 || resp > k * soma )
					resp = k * soma;
			}
		}
		
		printf( "%lld\n", resp );
		
	}
}




