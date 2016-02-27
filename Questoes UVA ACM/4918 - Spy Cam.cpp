#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define N 60
#define oo 0x7fffffff
 
bool sobre[ N ][ N ];
int x[ N ][ 2 ], y[ N ][ 2 ];
char ma[ N ][ N ];
int r, c;
bool baixo[ N ];

int main(){
	while( scanf( "%d %d", &r, &c ) != EOF && ( r | c ) ){
		for( int i = 0; i < r; ++i )
			scanf( "%s", ma[ i ] );
		
		memset( sobre, false, sizeof( sobre ) );
		memset( baixo, false, sizeof( baixo ) );
		for( int i = 0; i < N; ++i ){
			x[ i ][ 0 ] = y[ i ][ 0 ] = oo;
			x[ i ][ 1 ] = y[ i ][ 1 ] = -1;
		}
			
		for( int i = 0; i < r; ++i ){
			for( int j = 0; j < c; ++j ){
				if( ma[ i ][ j ] == '.' ) continue;
				char c = ma[ i ][ j ] - 'a';
				x[ c ][ 0 ] = min( x[ c ][ 0 ], j );
				x[ c ][ 1 ] = max( x[ c ][ 1 ], j );
				y[ c ][ 0 ] = min( y[ c ][ 0 ], i );
				y[ c ][ 1 ] = max( y[ c ][ 1 ], i );
			}
		}
		vector<char> resp;
		for( int i = 0; i < N; ++i ){
			if( x[ i ][ 1 ] == -1 ) break;
			
			for( int lin = y[ i ][ 0 ]; lin <= y[ i ][ 1 ]; ++lin ){
				for( int col = x[ i ][ 0 ]; col <= x[ i ][ 1 ]; ++col ){
					if( ma[ lin ][ col ] == '.' ) continue;
					char c = ma[ lin ][ col ] - 'a'; 
					if( c != i ){ //c esta sobre i
						baixo[ i ] = true;// i embaixo de algm
						sobre[ c ][ i ] = true; // c sobre i
					}
				}
			}
		}
		
		//sobre(i,j) é transitiva o.o !!!!!
		for( int k = 0; k < N; ++k ){
			for( int i = 0; i < N; ++i ){
				for( int j = 0; j < N; ++j )
					sobre[ i ][ j ] |= ( sobre[ i ][ k ] && sobre[ k ][ j ] );
			}
		}
		
		for( int i = 0; i < N; ++i ){
			if( x[ i ][ 1 ] == -1 ) break;
			if( baixo[ i ] ) continue;
			
			bool dm = false;
			//linha anterior
			if( y[ i ][ 0 ] - 1 >= 0 ){
				int l = y[ i ][ 0 ] - 1;
				bool p = false;
				for( int j = x[ i ][ 0 ]; j <= x[ i ][ 1 ]; ++j ){
					char c = ma[ l ][ j ] - 'a';
					if( c + 'a' == '.' ){ p = false; break; };
					if( sobre[ i ][ c ] ){
						p = false;
						break;
					}					
					p = true; 
				}
				dm |= p;
				
			}
			
			//linha posterior
			if( y[ i ][ 1 ] + 1 < r ){
				int l = y[ i ][ 1 ] + 1;
				bool p = false;
				for( int j = x[ i ][ 0 ]; j <= x[ i ][ 1 ]; ++j ){
					char c = ma[ l ][ j ] - 'a';
					if( c + 'a' == '.' ){
						p = false;						
						break;
					}
					if( sobre[ i ][ c ] ){
						p = false;
						break;
					}
					p = true;
				}
				dm |= p;
			}
			
			//coluna anterior
			if( x[ i ][ 0 ] -1 >= 0 ){
				int cc = x[ i ][ 0 ] - 1;
				bool p = false;				
				for( int l = y[ i ][ 0 ]; l <= y[ i ][ 1 ]; ++l ){
					char c = ma[ l ][ cc ] - 'a';
					if( c + 'a' == '.' ){
						p = false;
						break;
					}
					if( sobre[ i ][ c ] ){
						p = false;
						break;
					}

					p = true;
				}
				dm |= p;
			}
			
			//coluna posterior
			if( x[ i ][ 1 ] + 1 < c ){
				int cc = x[ i ][ 1 ] + 1;
				bool p = false;
				
				for( int l = y[ i ][ 0 ]; l <= y[ i ][ 1 ]; ++l ){
					char c = ma[ l ][ cc ] - 'a';
					if( c + 'a' == '.' ){
						p = false;
						break;
					}
					if( sobre[ i ][ c ] ){
						p = false;
						break;
					}
						
					p = true;
				}
				dm |= p;
			}
			if( !dm )
				resp.push_back( i + 'a' );
		}
		
		sort( resp.begin(), resp.end() );//sei la, vai que....
		printf( "Uncovered: " );
		for( int i = 0; i < resp.size(); ++i )
			printf( "%c", resp[ i ] );
		printf( "\n" );
		
		
	}
}

