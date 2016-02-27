#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <bitset>
using namespace std;
#define N 10010
#define MOD 1000000
typedef long long ll;

pair<int,int> pts[ N ];
map<int,int> mapa;
int pd[ N ][ 51 ][ 3 ];
//Accc!!!!!!!! Ah!!!!

int n, k, aux;

bool prim( const pair<int,int>& a, const pair<int,int>& b ){
	return a.first < b.first;
}

bool segu( const pair<int,int>& a, const pair<int,int>& b ){
	return a.second < b.second;
}

int bit0[ 51 ][ N ], bit1[ 51 ][ N ];

void update( int* bit, int ind, int val ){
	for( int i = ind; i <= aux; i += ( i & -i ) ){
		bit[ i ] = ( bit[ i ] + val + MOD ) % MOD;
	}
}

int query( int* bit, int ind ){
	int soma = 0;
	
	for( int i = ind; i; i -= ( i & -i ) ){
		soma = ( soma + bit[ i ] ) % MOD;
	}
	
	return soma;
}
 

int main(){
	int casos;
	scanf( "%d", &casos );
	for( int ca = 1; ca <= casos; ++ca ){
		scanf( "%d %d", &n, &k );
		mapa.clear();
		
		for( int i = 0; i < n; ++i ){
			scanf( "%d %d", &pts[ i ].first, &pts[ i ].second );
		}
		
		sort( pts, pts + n, segu );
		aux = 0;
		for( int i = 0; i < n; ++i ){
			if( !mapa[ pts[i].second ] ) mapa[ pts[i].second ] = ++aux;
			pts[i].second = mapa[ pts[i].second ]; 
		}
		
		sort( pts, pts + n, prim );
				
		memset( pd, 0, sizeof pd );
		memset( bit0, 0, sizeof bit0 );
		memset( bit1, 0, sizeof bit1 );		
		
		for( int i = 0; i < n; ++i ){
			for( int q = 0; q < 3; ++q )
				pd[ i ][ 0 ][ q ] = 1;
		}
		
		update( bit0[ 0 ], pts[ n - 1 ].second, 1 );
		update( bit1[ 0 ], pts[ n - 1 ].second, 1 );

		for( int ind = n - 2; ind >= 0; --ind ){
			for( int j = 0; j <= k; ++j ){
				
				if( j )
					pd[ ind ][ j ][ 0 ] += query( bit1[ j - 1 ], pts[ind].second - 1 ); 
				pd[ ind ][ j ][ 0 ] += query( bit0[ j ], aux ) - query( bit0[ j ], pts[ind].second );
				pd[ ind ][ j ][ 0 ] += MOD;
				
				while( pd[ ind ][ j ][ 0 ] >= MOD ) pd[ ind ][ j ][ 0 ] -= MOD;
				
				
				pd[ ind ][ j ][ 1 ] += query( bit1[ j ], pts[ind].second - 1 );
				if( j )
					pd[ ind ][ j ][ 1 ] += query( bit0[ j - 1 ], aux ) - query( bit0[ j - 1 ], pts[ind].second );
				pd[ ind ][ j ][ 1 ] += MOD;
				
				while( pd[ ind ][ j ][ 1 ] >= MOD ) pd[ ind ][ j ][ 1 ] -= MOD;
				
				pd[ ind ][ j ][ 2 ] += query( bit1[ j ], pts[ind].second - 1 );
				pd[ ind ][ j ][ 2 ] += query( bit0[ j ], aux ) - query( bit0[ j ], pts[ind].second );

				pd[ ind ][ j ][ 2 ] += MOD;
				while( pd[ ind ][ j ][ 2 ] >= MOD ) pd[ ind ][ j ][ 2 ] -= MOD;
				
			}
			for( int j = 0; j <= k; ++j ){
				int val0 = query( bit0[ j ], pts[ind].second ) - query( bit0[ j ], pts[ind].second - 1 );
				update( bit0[ j ], pts[ind].second, -val0 );
				update( bit0[ j ], pts[ind].second, pd[ ind ][ j ][ 0 ] );

				int val1 = query( bit1[ j ], pts[ind].second ) - query( bit1[ j ], pts[ind].second - 1 );
				update( bit1[ j ], pts[ind].second, -val1 );
				update( bit1[ j ], pts[ind].second, pd[ ind ][ j ][ 1 ] );

			}				
		}
				
		int resp = 0;
		if( !k ) resp = 1;
		set<int> pode;
		for( int i = 0; i < n; ++i ){
			if( !pode.insert( pts[i].second ).second ) continue;
//			printf( ">> %d, %d\n", pts[i].second, pd[i][k][2] );
			resp = ( resp + pd[ i ][ k ][ 2 ] ) % MOD;
			if( pd[ i ][ k ][ 2 ] < 0 ) throw 2;
		}
		if( resp < 0 ) throw 1;
		
		printf( "Case %d: %d\n", ca, resp );
	}
}






