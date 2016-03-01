#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 200

ll bit[N][N][N];
int n;

void update( int x, int y, int z, int val ){
	for( int i = x; i <= n; i += ( i & (-i) ) ){
		for( int j = y; j <= n; j += ( j & (-j) ) ){
			for( int k = z; k <= n; k += ( k & (-k) ) )
				bit[ i ][ j ][ k ] += val;
		}
	}
}

ll query( int x, int y, int z ){
	ll soma = 0;
	for( int i = x; i > 0; i -= ( i & (-i) ) ){
		for( int j = y; j > 0; j -= ( j & (-j) ) ){
			for( int k = z; k > 0; k -= ( k & (-k) ) )
				soma += bit[ i ][ j ][ k ];
		}
	}
	
	return soma;
}

int main(){
	freopen( "stars.in", "r", stdin );
	freopen( "stars.out", "w", stdout );
	
	scanf( "%d", &n );
	++n;
	memset( bit, 0, sizeof bit );
	int m;
	
	while( scanf( "%d", &m ) && m != 3 ){
		if( m == 1 ){
			int x, y, z, k;
			scanf( "%d %d %d %d", &x, &y, &z, &k );
			update( x+1, y+1, z+1, k );
		}else{
			int x[2], y[2], z[2];
			
			scanf( "%d%d%d%d%d%d", &x[0], &y[0], &z[0], &x[1], &y[1], &z[1] );
			x[1]++; y[1]++; z[1]++;
			ll soma = 0;

			for( int i = 0; i < 2; ++i ){
				for( int j = 0; j < 2; ++j ){
					for( int k = 0; k < 2; ++k ){
						int cont = 0;
						if(i) ++cont;
						if(j) ++cont;
						if(k) ++cont;
						
						ll q = query( x[i], y[j], z[k] );
						if( cont & 1 ) soma -= q;
						else soma += q;
					}
				}
			}
			
			printf( "%I64d\n", max( soma, -soma ) );
		}
	}
		
}







