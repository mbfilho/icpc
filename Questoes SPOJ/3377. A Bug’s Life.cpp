#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 3000

vector<int> adj[ 2 * N ];
int comp[ 2 * N ], time[ 2 * N ], contador, componente;
int pilha[ 2 * N ], sp;

int dfs( int no ){
	pilha[ sp++ ] = no;
	int menor;
	menor = time[ no ] = contador++;
	
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		int nt = adj[ no ][ i ];
		if( comp[ nt ] ) continue;
		
		if( time[ nt ] ) menor = min( menor, time[ nt ] );
		else
			menor = min( menor, dfs( nt ) );
	}
	
	if( menor == time[ no ] ){
		int temp;
		do{
			temp = pilha[ --sp ];
			comp[ temp ] = componente;
		}while( temp != no );
		++componente;
	}
	
	return menor;
}

int main(){
	int casos, n, m;
	scanf( "%d", &casos );
	
	for( int ca = 1; ca <= casos; ++ca ){
		scanf( "%d%d", &n, &m );
		for( int i = 1; i <= 2 * n; ++i ) adj[ i ].clear();
		memset( comp, 0, sizeof( comp ) );
		memset( time, 0, sizeof time );
		contador = componente = 1;
		sp = 0;
		
		while( m-- ){
			int a, b;
			scanf( "%d %d", &a, &b );
			
			//(a || b)
			adj[ a + n ].push_back( b ); //!a -> b
			adj[ b + n ].push_back( a ); //!b -> a
			
			//(!a || !b)
			adj[ a ].push_back( n + b );
			adj[ b ].push_back( n + a );
		}
		
		for( int i = 1; i <= 2 * n; ++i ){
			if( !time[ i ] )
				dfs( i );
		}
		bool dm = false;
		for( int i = 1; !dm && i <= n; ++i ){
			if( comp[ i ] == comp[ n + i ] ) dm = true;
		}
		
		printf( "Scenario #%d:\n", ca );
		if( dm )
			printf( "Suspicious bugs found!\n" );
		else
			printf( "No suspicious bugs found!\n" );
	}
}



