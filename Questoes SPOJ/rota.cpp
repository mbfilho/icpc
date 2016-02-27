#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
#include <string>
using namespace std;

#define N 200
#define M 10100
map<string,int> mapa;
string rev[ M ];

int ft[ M ], adj[ M ], last[ N ], pred[ M ], cont;
bool me[ M ], mv[ N ];
int n, m;
int resp[ M ], prt;

void add( int u, int v ){
	ft[ cont ] = u;
	adj[ cont ] = v;
	pred[ cont ] = last[ u ];
	last[ u ] = cont++;
}

bool dfs( int no ){
	mv[ no ] = true;
	if( no == 0 ) return true;
	
	for( int ed = last[ no ]; ed != -1; ed = pred[ ed ] ){
		if( mv[ adj[ed] ] || me[ ed ] ) continue;
		if( dfs( adj[ ed ] ) ) return true;
	} 
	
	return false;
}

char c1[ 100 ], c2[ 100 ];

int main(){
	while( scanf( "%d %d", &n, &m ) != EOF && ( n | m ) ){
		mapa.clear();
		memset( me, false, sizeof me ); 

		memset( last, -1, sizeof last );
				
		cont = prt = 0;
		
		for( int i = 0; i < n; ++i ){
			scanf( "%s", c1 );
			mapa[ c1 ] = i;
			rev[ i ] = c1;
		}
		
		for( int i = 0; i < m; ++i ){
			int u, v;
			scanf( "%s %s", c1, c2 );
			u = mapa[ c1 ];
			v = mapa[ c2 ];
			add( u, v );
		}
				
		for( int i = 0; i < n; ++i ){
			for( int ed = last[ i ]; ed != -1; ed = pred[ ed ] ){
				memset( mv, false, sizeof mv ); 
				me[ ed ] = true;
				if( !dfs( i ) ){
					resp[ prt++ ] = ed;
					me[ ed ] = false;
					break;
				}
				me[ ed ] = false;
			}
		}
		
		if( prt ){
			sort( resp, resp + prt );
			for( int i = 0; i < prt; ++i ){
				int ed = resp[ i ];
				printf( "%s %s\n", rev[ ft[ed] ].c_str(), rev[ adj[ed] ].c_str() );
			}
		}else
			printf( "Nenhuma\n" );
		printf( "\n" );	
	}	
}

