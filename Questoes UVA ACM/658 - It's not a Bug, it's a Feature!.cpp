#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;

int pot[ 30 ];
int bugs, patch;

int dist[ 1 << 21 ];

class Estado{
public:
	int reco[ 2 ];
	int out[ 2 ];
	int peso;
	
	bool pertence( int est ){
		return ( (est & reco[ 0 ]) == 0 && (est & reco[ 1 ]) == reco[ 1 ] );
	}
	
	int format( int in ){
		int retorno = in;
		retorno = retorno & (~out[ 0 ]);
		retorno = retorno | out[ 1 ];
		
		return retorno;
	}
}est[ 30 ];

void codificar( char in[], char out[], Estado& est ){
	est.reco[ 0 ] = est.reco[ 1 ] = est.out[ 0 ] = est.out[ 1 ] = 0;
	
	int tam = strlen( in );
	for( int i = 0; i < tam; ++i ){
		if( in[ i ] == '+' )
			est.reco[ 1 ] |= pot[ i ];
		else if( in[ i ] == '-' )
			est.reco[ 0 ] |= pot[ i ];			
	}
	
	tam = strlen( out );
	for( int i = 0; i < tam; ++i ){
		if( out[ i ] == '+' )
			est.out[ 1 ] |= pot[ i ];
		else if( out[ i ] == '-' )
			est.out[ 0 ] |= pot[ i ];
	}
}

struct noh{
	int peso, id;
	
	noh( int p, int no ){
		peso = p;
		id = no;
	}
	
	bool operator<( const noh& a ) const{
		return !(peso < a.peso);
	}
};

void dij( int ini ){
	priority_queue<noh> heap;
	noh temp( 0, ini );
	heap.push( temp );
	dist[ ini ] = 0;
	int peso, adj;
	
	while( heap.empty() == false ){
		temp = heap.top();
		heap.pop();
		
		if( dist[ temp.id ] != temp.peso )
			continue;
		
		for( int i = 0; i < patch; ++i ){
			if( est[ i ].pertence( temp.id ) ){
				adj = est[ i ].format( temp.id );
				peso = temp.peso + est[ i ].peso;
				if( dist[ adj ] > peso ){
					dist[ adj ] = peso;
					heap.push( noh( dist[ adj ], adj ) );
				}
			}
			
		}
		
	}
}

int main(){
	pot[ 0 ] = 1;
	for( int i = 1; i < 30; ++i )
		pot[ i ] = pot[ i - 1 ] * 2;
		
	char in[ 80 ], out[ 80 ];
	int cont = 1;
	const int inf = 0x7fffffff;
	
	while( scanf( "%d %d", &bugs, &patch ) && ( bugs | patch ) ){
		
		for( int i = 0; i < patch; ++i ){
			scanf( "%d %s %s", &est[ i ].peso, in, out );
			codificar( in, out, est[ i ] );
		}
		
		fill( dist, dist + pot[ bugs ], inf );
		
		dij( pot[ bugs ] - 1 );
		
		printf( "Product %d\n", cont++ );
		if( dist[ 0 ] == inf )
			printf( "Bugs cannot be fixed.\n\n" );
		else
			printf( "Fastest sequence takes %d seconds.\n\n", dist[ 0 ] );
	}
}
