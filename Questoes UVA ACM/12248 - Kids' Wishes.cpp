#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
using namespace std;
#define N 100100
#define mp make_pair

bool marc[ N ];
set<int> adj[ N ];
map<int,int> mapa;
int cont;
int w, k;

bool busca( int pai, int no ){
	marc[ no ] = true;
	
	for( set<int>::iterator it = adj[ no ].begin(); it != adj[ no ].end(); ++it ){
		int nt = *it;
		if( nt == pai ) continue;
		
		if( !marc[ nt ] ){
			bool ret = busca( no, nt );
			if( !ret ) return false;
		}else
			return false;
	}
	
	return true;
}

int main(){
	while( scanf( "%d %d", &k, &w ) == 2 && ( w | k ) ){
		mapa.clear();
		for( int i = 1; i <= w + 50; ++i ) adj[ i ].clear();
		memset( marc, false, sizeof marc );
		cont = 0;
		
		for( int i = 0; i < w; ++i ){
			int a, b;
			scanf( "%d %d", &a, &b );
			if( !mapa[ a ] ) mapa[ a ] = ++cont;
			if( !mapa[ b ] ) mapa[ b ] = ++cont;
			
			adj[ mapa[a] ].insert( mapa[b] );
			adj[ mapa[b] ].insert( mapa[a] );
		}
		
		bool dm = false;
		for( int i = 1; i <= cont && !dm; ++i ){
			if( adj[ i ].size() > 2 ) dm = true;
		}
		
		bool ciclo = false;
		
		for( int i = 1; i <= cont; ++i ){
			if( marc[ i ] ) continue;
			if( !busca( -1, i ) ){
				ciclo = true;
				if( i != 1 ) dm = true;
				break;
			}
		}
		
		if( dm )
			printf( "N\n" );
		else if( ciclo ){
			if( k == cont ){
				//deve conter todo mundo
				bool td = true;
				for( int i = 1; i <= cont && td; ++i ){
					if( !marc[ i ] ) td = false;
				}
				
				if( td )
					printf( "Y\n" );
				else
					printf( "N\n" );
			}
			else printf( "N\n" );
		}else if( !ciclo ){
			printf( "Y\n" );
		}
	}
}

