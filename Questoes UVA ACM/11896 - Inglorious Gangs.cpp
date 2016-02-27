#include<cstdio>
#include<algorithm>
#include <vector>
#include <cstring>
using namespace std;
#define N 5100

int marc[ N ];

bool achei;
int n, m;
vector<int> adj[ N ];

void dfs( int no ){
	marc[ no ] = 1;
	
	for( int i = adj[ no ].size() - 1; !achei && i >= 0; --i ){
		int next = adj[ no ][ i ];
		if( marc[ next ] == 2 )
			achei = true;
		else if( marc[ next ] == 0 )
			dfs( next );
		else
			marc[ next ] = 2;
	}
	
	marc[ no ] = 2;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	while( casos-- ){
		scanf( "%d %d", &n, &m );
		for( int i = 0; i <= n; ++i )
			adj[ i ].clear();
		while( m-- ){
			int a, b;
			scanf( "%d %d", &a, &b );
			adj[ a ].push_back( b );
		}
		
		achei = false;
		for( int i = 1; !achei && i <= n; ++i ){
			memset( marc, 0, sizeof( marc ) );
			dfs( i );
		}
		
		if( achei )
			printf( "Not Trapped\n" );
		else
			printf( "Trapped\n" );
	}
}










