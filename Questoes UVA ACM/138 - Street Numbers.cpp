#include <cstdio>
#include <cmath>
typedef long long ll;

int main(){
	int cont = 0;
	
	ll n = 2;
	while( cont < 10 ){
		ll a = n * n + n;
		if( a % 2 == 0 ){
			a /= 2;
			ll root = ll( sqrt( double( a ) ) );
			if( root * root == a ){
				++cont;
				printf( "%10lld%10lld\n", root, n );
			}
		}
		
		++n;
	}
}
//      7742    131528
