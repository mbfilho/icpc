#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define mp make_pair
#define MAX_NO 50100
#define MOD 321555123

int pd[ MAX_NO ][ 101 ];
int n, m, cont;

void rec( vector< pair<int,int> >* adj, bool *marc, int no ){
	marc[ no ] = true;
	int tam = adj[ no ].size();
	
	int peso, next;
	for( int i = 0; i <= m; ++i )
		pd[ no ][ i ] = 0;
		
	for( int i = 0; i < tam; ++i ){
		next = adj[ no ][ i ].first;
		peso = adj[ no ][ i ].second;
		if( marc[ next ] ) continue;
		
		rec( adj, marc, next );
		
		for( int j = 0; j + peso <= m; ++j )
			cont = ( cont + pd[ no ][ m - j - peso ] * pd[ next ][ j ] ) % MOD;
		
		
		for( int j = 0; j + peso <= m; ++j )
			pd[ no ][ j + peso ] += pd[ next ][ j ];
	}
	
	pd[ no ][ 0 ] = 1;
	
}

int main(){
	scanf( "%d %d", &n, &m );
	
	vector< pair<int,int> > adj[ n + 1 ];

	bool marc[ n + 1 ];

	
	int a, b, w;
	for( int i = 1; i < n; ++i ){
		scanf( "%d %d %d", &a, &b, &w );
		adj[ a ].push_back( mp( b, w ) );
		adj[ b ].push_back( mp( a, w ) ); 
	}
	
	cont = 0;
	memset( marc, false, sizeof( marc ) );
	rec( adj, marc, 1 );
	for( int i = 1; i <= n; ++i ){
		cont = ( cont + pd[ i ][ m ] ) % MOD;
	}
	/*
	for( int i = 1; i <= n; ++i ){
		printf( "No %d:", i );
		for( int j = 0; j <= m; ++j )
			printf( " %d", pd[ i ][ j ] );
		printf( "\n" );
	}
	*/
	printf( "%d\n", cont );
}



