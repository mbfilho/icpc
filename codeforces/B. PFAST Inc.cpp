#include <cstdio>
#include <string>
#include <cstring>
#include <map>
#include <algorithm>
#include <vector>
using namespace std;

map<string,int> mapa;
string rev[ 17 ];
bool adj[ 17 ][ 17 ];
char buf[ 10000 ], buf2[ 10000 ];

int main(){
	memset( adj, false, sizeof( adj ) );
	int n, m;
	scanf( "%d %d", &n, &m );
	
	for( int i = 0; i < n; ++i ){
		scanf( "%s", buf );
		mapa[ buf ] = i;
		rev[ i ] = buf;
	}
	
	for( int i = 0; i < m; ++i ){
		scanf( "%s %s", buf, buf2 );
		adj[ mapa[ buf ] ][ mapa[ buf2 ] ] = true;
		adj[ mapa[ buf2 ] ][ mapa[ buf ] ] = true;
	}
	
	int mask = 0, qtd = 0;
	for( int i = 1; i < ( 1 << n ); ++i ){
		bool dm = false;
		int c = 0;
		for( int j = 0; !dm && j < n; ++j ){
			if( i & ( 1 << j ) ){
				++c;
				for( int k = j + 1; !dm && k < n; ++k ){
					if( i & ( 1 << k ) )
						dm = dm || adj[ j ][ k ];
				}
			}
		}
		if( !dm && c > qtd ){
			qtd = c;
			mask = i;
		}
	}
	
	vector<string> resp;
	for( int i = 0; i < n; ++i ){
		if( mask & ( 1 << i ) )
			resp.push_back( rev[ i ] );
	}
	
	printf( "%d\n", qtd );
	sort( resp.begin(), resp.end() );
	for( int i = 0; i < qtd; ++i )
		printf( "%s\n", resp[ i ].c_str() );
}
