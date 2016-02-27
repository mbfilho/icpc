#include <cstdio>
typedef long long ll;

int main(){
	ll n;
	
	while( scanf( "%lld", &n ) && n ){
		ll a = 0, b = 0;
		int cont = 0;
		
		for( int i = 0; i < 32; ++i ){
			if( ( 1LL << i ) & n ){
				++cont;
				if( cont % 2 )
					a |= ( 1LL << i );
				else
					b |= ( 1LL << i );
			}
		}
		
		printf( "%lld %lld\n", a, b );	
		
	}
}

