#include <cstdio>
#include <string>
#include <algorithm>
#include <list>
#include <map>
#include <deque>
using namespace std;
#define N 400

map<string,int> mapa;
string rev[ N ];
deque<int> lista;
int meta[ N ];
int n;
char buf[ 100 ];

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d", &n );
		gets( buf );
		mapa.clear();
		lista.clear();
		
		for( int i = 0; i < n; ++i ){
			gets( buf );
			mapa[ buf ] = i;
			rev[ i ] = buf;
			lista.push_back( i );
		}
		
		for( int i = 0; i < n; ++i ){
			gets( buf );
			meta[ i ] = mapa[ buf ];
		}
		
		int last = meta[ n - 1 ];
		for( int i = n - 2; i >= 0; --i ){
			bool dm = false;
			deque<int>::iterator it;
			//do topo -> bottom
			for( it = lista.begin(); it != lista.end(); ++it ){
				if( *it == meta[ i ] ) break;
				if( *it == last )
					dm = true;
			}
			
			if( dm ){
				lista.erase( it );
				lista.push_front( meta[ i ] );
				printf( "%s\n", rev[ meta[ i ] ].c_str() );
			}
			last = meta[ i ];
				
		}
		
		printf( "\n" );
		
	}
}
