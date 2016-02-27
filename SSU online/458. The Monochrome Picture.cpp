#include <cstdio>
#include <algorithm>
using namespace std;
#define mp make_pair
#define N 100100
#define TREE 5000000
#define length first
#define index second 

int pd[ N ], next[ N ], seq[ N ];
pair<int,int> nos[ TREE ];

void build( int no, int a, int b ){
	if( a == b ){
		nos[ no ].length = -1;
		nos[ no ].index = -1;
	}else{
		int meio = ( a + b ) / 2;
		build( no * 2, a, meio );
		build( no * 2 + 1, meio + 1, b );
	}
}

pair<int,int> query( int no, int ini, int fim, int a, int b ){
	if( b < a ) return mp( -1, -1 );
	
	int meio = ( ini + fim ) / 2;
	if( a == ini && b == fim )
		return nos[ no ];
	else if( b <= meio ){
		return query( no * 2, ini, meio, a, b );
	}else if( a > meio )
		return query( no * 2 + 1, meio + 1, fim, a, b );
	else{
		pair<int,int> esq = query( no * 2, ini, meio, a, meio ), dir = query( no * 2 + 1, meio + 1, fim, meio + 1, b );
		if( esq.length > dir.length ) return esq;
		return dir;
	}
}

void insert( int no, int ini, int fim, int a, pair<int,int> val ){
	if( a < ini || a > fim ) return;
	
	if( a == ini && ini == fim ){
		nos[ no ] = val;
	}else{
		int meio = ( ini + fim ) / 2;
		insert( 2 * no, ini, meio, a, val );
		insert( 2 * no + 1, meio + 1, fim, a, val );
		
		if( nos[ 2 * no ].length > nos[ 2 * no + 1 ].length )
			nos[ no ] = nos[ 2 * no ];
		else
			nos[ no ] = nos[ 2 * no + 1 ];
	}
}

int tam, ind, n;
void faz(){
	build( 1, 0, 1000000 );
	pd[ n - 1 ] = 1;
	next[ n - 1 ] = -1;
	insert( 1, 0, 1000000, seq[n-1], mp( 1, n - 1 ) );
	tam = 1;
	ind = n - 1;
	
	pair<int,int> best, aux;
	for( int i = n - 2; i >= 0; --i ){
		best = query( 1, 0, 1000000, seq[ i ] + 2, 1000000 );
		aux = query( 1, 0, 1000000, 0, seq[ i ] - 2 );
		if( aux.length > best.length )
			best = aux;
		aux = query( 1, 0, 1000000, seq[ i ], seq[ i ] );
		if( aux.length > best.length )
			best = aux;
			
		if( best.length == -1 ){
			pd[ i ] = 1;
			next[ i ] = -1;
		}else{
			pd[ i ] = 1 + best.length;
			next[ i ] = best.index;
			if( pd[ i ] > tam ){
				tam = pd[ i ];
				ind = i;
			}
		}

		insert( 1, 0, 1000000, seq[i], mp( pd[ i ], i ) );
	}
}
int resp[ N ];

int main(){
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i )
		scanf( "%d", seq + i );
	faz();
	printf( "%d\n", n - tam );

	for( int i = 0; i < tam; ++i ){
		resp[ i ] = seq[ ind ];
		ind = next[ ind ];
	}
	
	printf( "%d", resp[0] );
	for( int i = 1; i < tam; ++i )
		printf( " %d", resp[i] );
	printf( "\n" );
}


