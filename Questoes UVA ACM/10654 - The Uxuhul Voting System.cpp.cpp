#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 110

int pref[ N ][ 9 ];

int pd[ N ][ 8 ], n;
const char* r[] = { "NNN", "NNY", "NYN", "NYY", "YNN", "YNY", "YYN", "YYY" };

int memo( int c, int mask ){
	if( c == n ) return mask;
	int &ret = pd[ c ][ mask ];
	if( ret != -1 ) return ret;
	
	int p = 100;
	
	for( int i = 1; i <= 4; i *= 2 ){
		int temp = memo( c + 1, mask xor i );
		if( pref[ c ][ temp ] < p ){
			ret = temp;
			p = pref[ c ][ temp ];
		}
	}
	
	return ret;	
}


int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &n );
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < 8; ++j ){
				int temp;
				scanf( "%d", &temp );
				pref[ i ][ j ] = temp;
			}
		}
		
		memset( pd, -1, sizeof pd );
		int resp = memo( 0, 0 );
		printf( "%s\n", r[ resp ] );
	}
}




