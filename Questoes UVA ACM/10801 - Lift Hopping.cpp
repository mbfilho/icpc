#include <cstdio>
#include <list>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

#define INF 999999
int elevadores, destino;

int dist[ 6 ][ 100 ];

int tempo[ 6 ];

bool parada[ 6 ][ 100 ];

list<int> adj[ 6 ];

void ql(){
	while( cin.peek() == '\n' )
		cin.ignore();
}

int mod( int a ){
	if( a < 0 )
		return -a;
	return a;
}

class noh{
public:
	int id, ele, dist;
	
	noh(){}
	
	noh( int no, int el, int d ){
		id = no;
		ele = el;
		dist = d;
	}
	
	bool operator<( const noh& a ) const{
		return !( dist < a.dist );
	}
};

int dij(){
	priority_queue<noh> heap;
	noh temp;
	int ele, andar, dista;
	list<int>::iterator it;
	
	for( int i = 1; i <= elevadores; ++i ){
		if( parada[ i ][ 0 ] ){
			heap.push( noh( 0, i, 0 ) );
			dist[ i ][ 0 ] = 0;
		}
	}
	
	while( heap.empty() == false ){
		temp = heap.top();
		heap.pop();
		
		ele = temp.ele;
		andar = temp.id;
		dista = temp.dist;
		
		if( dist[ ele ][ andar ] != dista )
			continue;
		
		int penalidade;
		for( int i = 1; i <= elevadores; ++i ){
			if( parada[ i ][ andar ] == false ) 
				continue;
				
			for( it = adj[ i ].begin(); it != adj[ i ].end(); ++it ){
				if( i == ele )
					penalidade = 0;
				else
					penalidade = 60;
					
				if( dist[ i ][ *it ] > dista + penalidade + tempo[ i ] * mod( *it - andar ) ){
					dist[ i ][ *it ] = dista + penalidade + tempo[ i ] * mod( *it - andar );
					heap.push( noh( *it, i, dist[ i ][ *it ] ) );
				}
			}
		}
	}
}

int main(){
	int temp;
	char linha[ 500 ];

	while( scanf( "%d %d", &elevadores, &destino ) != EOF ){
		for( int i = 1; i <= elevadores; ++i )
			scanf( "%d", tempo + i );
		
		for( int i = 1; i <= elevadores; ++i ){
			adj[ i ].clear();
			for( int j = 0; j < 100; ++j ){
				parada[ i ][ j ] = false;
				dist[ i ][ j ] = INF;
			}
		}
		
		ql();
		for( int i = 1; i <= elevadores; ++i ){
			gets( linha );
			int acumulado = 0, n;
			ql();
			
			while( sscanf( linha + acumulado, "%d %n", &temp, &n ) != EOF ){
				acumulado += n;
				adj[ i ].push_back( temp );
				parada[ i ][ temp ] = true;
			}
		}

		dij();
		int menor = INF;
		
		for( int i = 1; i <= elevadores; ++i ){
			menor = min( menor, dist[ i ][ destino ] ); 
			//printf( "%d\n", dist[ i ][ destino ] );
		}
			
		if( menor >= INF )
			printf( "IMPOSSIBLE\n" );
		else
			printf( "%d\n", menor );
		
	}
}




