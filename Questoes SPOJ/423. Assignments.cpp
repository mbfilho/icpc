#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll pd[ 1 << 20 ];
int prefs[ 20 ];
int n;

//iterativo = 3s
ll resp(){
	pd[ 0 ] = 1;
	
	for( int i = 1; i < ( 1 << n ); ++i ){
		int cnt = 0, temp = i;
		pd[ i ] = 0;
		while( temp ){
			++cnt;
			temp -= ( temp & -temp );
		}
		
		int mask = i & prefs[ n - cnt ];
		while( mask ){
			int bit = mask & -mask;
			pd[ i ] += pd[ i - bit ];
			mask -= bit;
		}
	}
	
	return pd[ ( 1 << n ) - 1 ];
}

//Recursivo = 14s
ll memo( int pode ){
	if( !pode ) return 1;
	ll& ret = pd[ pode ];
	if( ret != -1 ) return ret;
	
	ret = 0;
	int cnt = 0, temp = pode;
	while( temp ){
		++cnt;
		temp -= ( temp & -temp );
	}
	
	int mask = pode & prefs[ n - cnt ];
	while( mask ){
		int bit = mask & -mask;
		ret += memo( pode xor bit );
		mask -= bit;
	}
	
	return ret;	
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int ca = 1; ca <= casos; ++ca ){
		scanf( "%d", &n );
		
		for( int i = 0; i < n; ++i ){
			prefs[ i ] = 0;
			int temp;
			for( int j = 0; j < n; ++j ){
				scanf( "%d", &temp );
				prefs[ i ] = prefs[ i ] * 2 + temp;
			}
		}
		
//		memset( pd, -1, sizeof( pd ) );
//		printf( "%lld\n", memo( (1 << n) - 1 ) );
		printf( "%lld\n", resp() );

	}
}






