#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 20000
#define MOD 10001
typedef long long ll;

int n;
ll x[ N ];

ll inv( ll a ){
	ll x2 = 1, y2 = 0;
	ll x1 = 0, y1 = 1;
	ll maior = MOD;
	ll menor = a;
	ll quo, mod;
	
	while( menor ){
		quo = maior / menor;
		mod =  maior % menor;
		ll atx = x2 - quo * x1;
		ll aty = y2 - quo * y1;
		
		x2 = x1;
		x1 = atx;
		
		y2 = y1;
		y1 = aty;
		
		maior = menor;
		menor = mod;
	}
	
	return y2;
}

int main(){
	scanf( "%d", &n );
	
	for( int i = 0; i < n; ++i )
		scanf( "%lld", x + 2 * i + 1 );

	bool achou = false;

	ll a = 0, b;
	while( a < MOD && !achou ){
		ll prod = ( ( a + 1 ) * inv( a + 1 ) ) % MOD;
		while( prod < 0 ) prod += MOD; 
		if( prod != 1 ){
			++a;
			continue;
		}
		
		b = ( x[ 3 ] - a * a * x[ 1 ] ) % MOD;
		b *= inv( 1 + a );
		b %= MOD;	
		while( b < 0 ) b += MOD;

		bool dm = false;
		for( int i = 2; !dm && i < n; ++i ){
			ll h1 = ( x[ 2 * ( i - 1 ) + 1 ] * a * a + a * b + b ) % MOD;
			if( h1 != x[ 2 * i + 1 ] ) dm = true;
		}
		
		if( !dm ) achou = true;
		else ++a;
	}
	
	//if( !achou ) throw 1;
	for( int i = 2; i <= 2 * n; i += 2 ){
		printf( "%lld\n", ( x[ i - 1 ] * a + b ) % MOD ); 
	}
}


