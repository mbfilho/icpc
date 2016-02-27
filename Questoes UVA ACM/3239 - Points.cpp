#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;
#define MAX 600

class wrap{
public:
	list<int> ig[ MAX ], men[ MAX ];
	int igual[ MAX ], menor[ MAX ];
}X, Y;

bool dfs( list<int> adj[], int marc[], int marc2[], int no ){
	if( marc2[ no ] != 0 )
		return false;
		
	marc[ no ] = 1;
	list<int>::iterator it;
	for( it = adj[ no ].begin(); it != adj[ no ].end(); ++it ){
		if( marc[ *it ] == 0 && dfs( adj, marc, marc2, *it ) == false )
			return false;
	}
	
	//marc[ no ] = 2;
	return true;
}

bool ciclo( list<int> adj[], int marc[], int no ){
	marc[ no ] = 1;
	list<int>::iterator it;
	
	for( it = adj[ no ].begin(); it != adj[ no ].end(); ++it ){
		if( marc[ *it ] == 1 )
			return true;
		
		if( marc[ *it ] == 0 && ciclo( adj, marc, *it ) )
			return true;
	}
	
	marc[ no ] = 2;
	return false;
}

int main(){
	int casos, cont, regras, a, b;
	char r[ 80 ];
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &cont, &regras );
		for( int i = 1; i <= cont; ++i ){
			X.ig[ i ].clear();
			X.men[ i ].clear();
			Y.ig[ i ].clear();
			Y.men[ i ].clear();
		}
		
		for( int i = 0; i < regras; ++i ){
			scanf( "%d %s %d", &a, r, &b );
			if( strcmp( r, "N" ) == 0 ){
				X.ig[ a ].push_back( b );
				X.ig[ b ].push_back( a );
				Y.men[ a ].push_back( b );
			}else if( strcmp( r, "S" ) == 0 ){
				X.ig[ a ].push_back( b );
				X.ig[ b ].push_back( a );
				Y.men[ b ].push_back( a );
			}else if( strcmp( r, "E" ) == 0 ){
				Y.ig[ a ].push_back( b );
				Y.ig[ b ].push_back( a );
				X.men[ a ].push_back( b );
			}else if( strcmp( r, "W" ) == 0 ){
				Y.ig[ a ].push_back( b );
				Y.ig[ b ].push_back( a );
				X.men[ b ].push_back( a );
			}else if( strcmp( r, "NE" ) == 0 ){
				Y.men[ a ].push_back( b );
				X.men[ a ].push_back( b );
			}else if( strcmp( r, "NW" ) == 0 ){
				Y.men[ a ].push_back( b );
				X.men[ b ].push_back( a );
			}else if( strcmp( r, "SE" ) == 0 ){
				Y.men[ b ].push_back( a );
				X.men[ a ].push_back( b );
			}else if( strcmp( r, "SW" ) == 0 ){
				Y.men[ b ].push_back( a );
				X.men[ b ].push_back( a );
			}
		}
		
		fill( X.menor, X.menor + cont + 1, 0 );
		fill( X.igual, X.igual + cont + 1, 0 );
		bool dm = false;
		for( int i = 1; i <= cont && !dm; ++i ){
			if( X.menor[ i ] == 0 )
				dm = dm || ciclo( X.men, X.menor, i );
		}
		
		fill( Y.menor, Y.menor + cont + 1, 0 );
		fill( Y.igual, Y.igual + cont + 1, 0 );
		for( int i = 1; i <= cont && !dm; ++i ){
			if( Y.menor[ i ] == 0 )
				dm = dm || ciclo( Y.men, Y.menor, i );
		}
				
		for( int i = 1; i <= cont && !dm; ++i ){
			fill( X.menor, X.menor + cont + 1, 0 );
			fill( X.igual, X.igual + cont + 1, 0 );
			dm = dm || !dfs( X.men, X.menor, X.igual, i );
			X.menor[ i ] = 0;
			dm = dm || !dfs( X.ig, X.igual, X.menor, i );
		}
		
		for( int i = 1; i <= cont && !dm; ++i ){
			fill( Y.menor, Y.menor + cont + 1, 0 );
			fill( Y.igual, Y.igual + cont + 1, 0 );
			
			dm = dm || !dfs( Y.men, Y.menor, Y.igual, i );
			Y.menor[ i ] = 0;
			dm = dm || !dfs( Y.ig, Y.igual, Y.menor, i );
		}
		
		if( dm )
			printf( "IMPOSSIBLE\n" );
		else
			printf( "POSSIBLE\n" );
	}
}
