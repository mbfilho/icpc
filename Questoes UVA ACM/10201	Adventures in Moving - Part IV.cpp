#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
#define mp make_pair
#define N 5100
#define K 1010
#define quad(x) (x) * (x)
#define oo 0x7fffffff

int dist[ N ], preco[ N ], n;
int pd[ N ][ 110 ];

struct No{
	int id, dist, gas;
	No( int a, int b, int c ){
		id = a;
		dist = b;
		gas = c;
	}
	
	bool operator<( const No& n ) const{
		return !( dist < n.dist );
	}
};

int faz(){
	priority_queue< No > heap;
	
	for( int i = 0; i <= n; ++i ){
		if( dist[ i ] <= 100 )
			heap.push( No( i, 0, 100 - dist[ i ] ) );
	}	

	for( int i = 0; i <= n; ++i ){
		for( int j = 0; j <= 200; ++j )
			pd[ i ][ j ] = oo;
	}
	
	while( !heap.empty() ){
		int atual = heap.top().id, dista = heap.top().dist, gas = heap.top().gas;
		heap.pop();
		
		if( atual == n && gas >= 100 ) return dista;
		if( pd[ atual ][ gas ] != oo ) continue;
		
		pd[ atual ][ gas ] = dista;
		
		for( int i = atual + 1; i <= n; ++i ){
			int custo = dist[ i ] - dist[ atual ];
			if( custo > 200 ) continue;
			int ini = max( 0, custo - gas );
			
			for( int c = ini; c + gas <= 200; ++c ){
				if( pd[ i ][ c + gas - custo ] > dista + c * preco[ atual ] )
					heap.push( No( i, dista + c * preco[ atual ], c + gas - custo ) );
			}			
		}
	}
	
	return oo;
}

int main(){
	int casos;
	char linha[ 1000 ];
	scanf( "%d", &casos );
	for( int caso = 1; caso <= casos; ++caso ){
		int d;
		scanf( "%d", &d );
		gets( linha ); //\n
		
		n = 0;
		while( gets( linha ) && linha[0] ){
			sscanf( linha, "%d %d", dist + n, preco + n );
		//	printf( "%d %d\n", dist[n], preco[n] );
			++n;
		}
		dist[ n ] = d;
		preco[ n ] = -1;
		if( caso != 1 )
			printf( "\n" );
		int tam = faz();
		if( tam == oo )
			printf( "Impossible\n" );
		else
			printf( "%d\n", tam );
		
	}
}





