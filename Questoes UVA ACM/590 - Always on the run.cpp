#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define mp make_pair
#define N 11
#define K 1001
#define oo 0x7fffffff

int adj[ N ][ N ][ 31 ], cont[ N ][ N ];
int n, k;

int dist[ N ][ K ];

struct No{
	int dist, id, dia;
	
	No( int a, int b, int c ){
		dist = a;
		id = b;
		dia = c;
	}

	bool operator<( const No& n ) const{
		return !( dist < n.dist );
	}
};


int faz(){
	for( int i = 0; i < n; ++i ){
		for( int j = 0; j <= k; ++j )
			dist[ i ][ j ] = oo;
	}
	
	
	priority_queue< No > heap;
	heap.push( No( 0, 0, 0 ) );
	
	while( !heap.empty() ){
		int dista = heap.top().dist, atual = heap.top().id, dia = heap.top().dia;
		heap.pop();
		if( dist[ atual ][ dia ] != oo ) continue;
		
		dist[ atual ][ dia ] = dista;
		
		for( int i = 0; i < n; ++i ){
			if( i == atual ) continue;
			int custo = adj[ atual ][ i ][ dia % cont[ atual ][ i ] ];
			if( custo == 0 ) continue;
			
			if( custo + dista < dist[ i ][ dia + 1 ] )
				heap.push( No( custo + dista, i, dia + 1 ) );
		}
	}
	
	return dist[ n - 1 ][ k ];
}

int main(){
	int caso = 1;
	while( scanf( "%d %d", &n, &k ) && ( n | k ) ){
		for( int i = 0; i < n; ++i ){
			for( int j = 0; j < n; ++j ){
				if( i == j ) continue;
				scanf( "%d", &cont[ i ][ j ] );
				for( int k = 0; k < cont[ i ][ j ]; ++k )
					scanf( "%d", &adj[ i ][ j ][ k ] );
			}
		}
		
		
		int d = faz();
		printf( "Scenario #%d\n", caso++ );
		if( d == oo ){
			printf( "No flight possible.\n\n" );
		}else
			printf( "The best flight costs %d.\n\n", d );
	}
}



