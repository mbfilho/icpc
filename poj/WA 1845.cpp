#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define PR 1000000
typedef long long ll;
int primos[ PR ], contp;
bool crivo[ PR ];
pair<ll,ll> fat[ 30 ];
int n;
#define MOD 9901

void faz(){
	memset( crivo, true, sizeof( crivo ) );
	for( int i = 4; i < PR; i += 2 )
		crivo[ i ] = false;
	
	for( int i = 3; i * i < PR; i += 2 ){
		for( int j = i * i; j < PR; j += 2 * i )
			crivo[ j ] = false;
	}
	
	primos[ 0 ] = 2;
	contp = 1;
	
	for( int i = 3; i < PR; i += 2 ){
		if( crivo[ i ] )
			primos[ contp++ ] = i;
	}
}

ll expo( ll a, ll xp ){
	ll ret = 1;
	a = a % MOD;
	
	while( xp ){
		if( xp & 1 )
			ret = ( ret * a ) % MOD;
		a = ( a * a ) % MOD;
		xp = xp >> 1;
	}
	
	while( ret < 0 ) ret += MOD;
	return ret;
}

void fatorar( ll a, ll b ){
	ll temp = a;
	n = 0;
	
	for( int i = 0; i < contp && temp != 1; ++i ){
		if( temp % primos[ i ] == 0 ){
			fat[ n ].first = primos[ i ];
			fat[ n ].second = 0;
			
			do{
				temp /= primos[ i ];
				++fat[ n ].second;
			}while( temp % primos[ i ] == 0 );
			++n;
		}
	}
	
	for( int i = 0; i < n; ++i )
		fat[ i ].second *= b;
}


int main(){
	faz();
	ll a, b;
	while( cin >> a >> b ){
		if( a == 1 ){
			printf( "1\n" );
		}else if( b == 0 ){
			printf( "1\n" );
		}else if( a == 0 ){
			printf( "0\n" );
		}else{
			fatorar( a, b );
			ll soma = 1;
	
			for( int i = 0; i < n; ++i ){
				ll aux = expo( fat[ i ].first, fat[ i ].second + 1 ) - 1;
				while( aux < 0 ) aux += MOD;
				 aux *= expo( fat[ i ].first - 1, MOD - 2 );
				soma = ( soma * aux ) % MOD;
			}
			
			//while( soma < 0 ) soma += MOD;
			cout << soma << endl;
		}
	}
}


