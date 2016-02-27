#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
#define mod  100000000
int n, m;

ll pd[ 12 ][ 1 << 12 ];
int ma[ 12 ];

ll memo( int c, int pode ){
	if( c == n ) return 1;
	
	int mask = (~pode) & ma[ c ];
	ll& ret = pd[ c ][ mask ];
	if( ret != -1 ) return ret;
	ret = 0;
	
	for( int i = 0; i < (1 << m); ++i ){
		if( (i & mask) != i ) continue;
		int ant = 0, temp = i;
		bool can = true;
		
		while( temp && can ){
			if( temp & 1 ){
				can = ( ant == 0 );
				ant = 1;
			}else
				ant = 0;
			temp /= 2;
		}
		
		if( !can ) continue;
		ret = ( ret + memo( c + 1, i ) ) % mod;
	}
	
	return ret;
}

int main(){
	scanf( "%d %d", &n, &m );
	
	for( int i = 0; i < n; ++i ){
		ma[i] = 0;
		int temp;
		for( int j = 0; j < m; ++j ){
			scanf( "%d", &temp );
			ma[i] = 2 * ma[i] + temp;
		}
	}
	memset( pd, -1, sizeof pd );
	printf( "%lld\n", memo( 0, 0 ) );
}



