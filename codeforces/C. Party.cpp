#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
#define N 3000

int alt[ N ];
vector<int> adj[ N ];
int n;
queue<int> fila;

int bfs(){
	memset( alt, -1, sizeof( alt ) );
	
	for( int i = 1; i <= n; ++i ){
		if( alt[ i ] != -1 ) continue;
		
		while( !fila.empty() ) fila.pop();
		fila.push( i );
		alt[ i ] = 0;
		
		while( !fila.empty() ){
			int at = fila.front();
			fila.pop();
			
			for( int j = adj[ at ].size() - 1; j >= 0; --j ){
				alt[ adj[ at ][ j ] ] = alt[ at ] + 1;
				fila.push( adj[ at ][ j ] ); 
			}
		}
	}
	
	int maior = -1;
	for( int i = 1; i <= n; ++i )
		maior = max( maior, alt[ i ] );
	
	return maior + 1;
}

int main(){
	int temp;
	scanf( "%d", &n );
	for( int i = 1; i <= n; ++i ) adj[ i ].clear();
	for( int i = 1; i <= n; ++i ){
		scanf( "%d", &temp );
		if( temp != -1 ){
			adj[ temp ].push_back( i );
		}
	}
	
	printf( "%d\n", bfs() );
}

