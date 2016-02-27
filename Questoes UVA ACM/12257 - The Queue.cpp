#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
#define MOD 1000000007
#define N 1101

vector<int> adj[ N ];
int size[ N ];
ll formas[ N ];

bool crivo[ N ];
int primos[ N ], contp;
int n;

void pre(){
	memset( crivo, true, sizeof( crivo ) );
	for( int i = 4; i < N; i += 2 ) crivo[ i ] = false;
	
	for( int i = 3; i * i < N; i += 2 ){
		if( !crivo[ i ] ) continue;
		
		for( int j = i * i; j < N; j += 2 * i )
			crivo[ j ] = false;
	}
	
	contp = 1;
	primos[ 0 ] = 2;
	for( int i = 3; i < N; i += 2 ){
		if( crivo[i] )
			primos[ contp++ ] = i;
	}
}

int expo( ll base, int xp ){
	ll ret = 1;
	
	while( xp ){
		if( xp & 1 )
			ret = ( ret * base ) % MOD;
		base = ( base * base ) % MOD;
		xp = xp >> 1;
	}
	
	return int(ret);
}

int fat[ 500 ], fat2[ 500 ], fat3[ 500 ];

void fatorar( int num, int* fat ){
	for( int i = 0;i < contp; ++i ){
		int p = primos[i];
		while( p <= num ){
			fat[ i ] += num / p;
			p *= primos[ i ];
		}
	}
}

//c tomado a, a
ll comb( int c, int a ){
	for( int i = 0; i < contp; ++i )
		fat[ i ] = fat2[ i ] = fat3[ i ] = 0;
	
	fatorar( c, fat );
	fatorar( a, fat2 );
	fatorar( c - a, fat3 );
	
	ll resp = 1;
	for( int i = 0; i < contp; ++i )
		resp = ( resp * expo( primos[i], fat[i] - fat2[i] - fat3[i] ) ) % MOD;
	
	return resp;
}

void dfs( int no ){
	formas[ no ] = 1;
	size[ no ] = 1;
	
	int soma = 0;
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		int nt = adj[ no ][ i ];		
		dfs( nt );
		soma += size[ nt ];
	}
	size[ no ] += soma;
	
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		int nt = adj[ no ][ i ];
		formas[ no ] = ( ( ( formas[ no ] * comb( soma, size[ nt ] ) ) % MOD ) * formas[ nt ] ) % MOD;
		soma -= size[ nt ];
	}
}

int vin[ N ];

int main(){
	pre();
	
	int casos;
	scanf( "%d", &casos );
	for( int ca = 1; ca <= casos; ++ca ){
		scanf( "%d", &n );
		for( int i = 0; i <= n; ++i )
			adj[ i ].clear();
		memset( vin, 0, sizeof( vin ) );
		
		for( int i = 1; i < n; ++i ){
			int u, v;
			scanf( "%d %d", &u, &v );
			adj[ u ].push_back( v );
			++vin[ v ];
		}
		int root;
		for( int i = 1; i <= n; ++i ){
			if( !vin[i] ){
				root = i;
				break;
			}
		}
		dfs( root );
		
		/*
		printf( "Root %d\n", root );
		for( int i = 1; i <= n; ++i ){
			printf( ">> %d size %d for %lld\n", i, size[i], formas[i] );
		}
		*/
		
		
		printf( "Case %d: %lld\n", ca, formas[ root ] );
		
	}
}


