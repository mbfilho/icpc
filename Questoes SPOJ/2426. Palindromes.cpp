#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 30100
typedef long long ull;
ull MOD = 1000000007;
char text[ N ];
int k, tam;
const ull BASE = 37;

ull expo( ull a, ull xp ){
	ull resp = 1;
	
	while( xp ){
		if( xp & 1 )
			resp = ( resp * a ) % MOD;
		a = ( a * a ) % MOD;
		xp = xp >> 1;
	}
	
	return resp;
}

ull REV = expo( BASE, MOD - 2 );

int main(){
	while( scanf( "%d", &k ) != EOF ){
		scanf( "%s", text );
		tam = strlen( text );
		int cont = 0;
		
		if( k <= tam ){
			ull ha = 0, hv = 0, pot = 1;
			
			for( int i = 0; i < k; ++i ){
				ha = ha * BASE + text[ i ];
				hv = hv * BASE + text[ k - 1 - i ];
				ha %= MOD;
				hv %= MOD;
			}
			pot = expo( BASE, k - 1 );
			
			if( ha == hv ) ++cont;
			
			for( int i = k; i < tam; ++i ){
				ha = ( ha - text[ i - k ] * pot ) * BASE + text[ i ];
				hv = ( hv - text[ i - k ] ) * REV + text[ i ] * pot;

				ha %= MOD;
				while( ha < 0 ) ha += MOD;
				
				hv %= MOD;
				while( hv < 0 ) hv += MOD;
				if( ha == hv ) ++cont;
			}
		}
		
		printf( "%d\n", cont );
	}	
}



