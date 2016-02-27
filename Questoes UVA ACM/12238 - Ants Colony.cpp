#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
#define N 100100
#define mp make_pair
typedef long long ll;

vector< pair<int,int> > adj[ N ];
int pd[ N ][ 18 ];
ll dist[ N ];
int alt[ N ];
int n;

queue<int> fila;

void bfs( int no = 0 ){	
	for( int i = 0; i < n; ++i ){
		dist[ i ] = -1;
		for( int j = 0; ( 1 << j ) <= n; ++j )
			pd[ i ][ j ] = -1; 
	}
	while( !fila.empty() ) fila.pop();
	
	dist[ no ] = 0;
	alt[ no ] = 0;
	fila.push( no );
	
	while( fila.empty() == false ){
		int at = fila.front(), d = dist[ at ];
		fila.pop();
		
		for( int i = adj[ at ].size() - 1; i >= 0; --i ){
			int nt = adj[ at ][ i ].first, peso = adj[ at ][ i ].second;
			
			if( dist[ nt ] == -1 ){
				alt[ nt ] = 1 + alt[ at ];
				dist[ nt ] = dist[ at ] + ll( peso );
				fila.push( nt );
				pd[ nt ][ 0 ] = at;
			}
		}
	}
}

void pre(){
	for( int i = 1; ( 1 << i ) <= n; ++i ){
		for( int j = 0; j < n; ++j ){
			if( pd[ j ][ i - 1 ] != -1 )
				pd[ j ][ i ] = pd[ pd[j][i - 1] ][ i - 1 ];
		}
	}
}

ll query( int a, int b ){
	if( alt[ b ] < alt[ a ] ) swap( a, b );
	ll ret = dist[ a ] + dist[ b ];
	
	int dif = 0;
	while( ( 1 << dif ) <= n ) ++dif;
	
	for( int i = dif - 1; i >= 0; --i ){
		if( alt[ b ] - ( 1 << i ) >= alt[ a ] )
			b = pd[ b ][ i ];
	}
	
	if( a != b ){
		dif = 0;
		while( ( 1 << dif ) <= alt[ a ] ) ++dif;
		for( int i = dif - 1; i >= 0; --i ){
			if( pd[ a ][ i ] != pd[ b ][ i ] ){
				a = pd[ a ][ i ];
				b = pd[ b ][ i ];
			}
		}
		
		int lca = pd[ a ][ 0 ];
		return ret - 2 * dist[ lca ];
	}else{
		return ret - 2 * dist[ a ];
	}
}

int main(){
	
	while( scanf( "%d", &n ) != EOF && n ){
		for( int i = 0; i < n; ++i )
			adj[ i ].clear();
		
		for( int i = 1; i < n; ++i ){
			int u, p;
			scanf( "%d%d", &u, &p );
			adj[ i ].push_back( mp( u, p ) );
			adj[ u ].push_back( mp( i, p ) );
		}
		
		bfs();
		pre();
		
		int q;
		scanf( "%d", &q );
		
		while( q-- ){
			int u, v;
			scanf( "%d%d", &u, &v );
			printf( "%lld", query( u, v ) );
			if( q ) printf( " " );
			else printf( "\n" );
			
		}
	}
}


