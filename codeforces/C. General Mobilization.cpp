#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;


struct No{
	vector<int> adj;
	int next;
	
	No(){
		next = 10000;
	}
}nos[ 5100 ];

struct Aresta{
	int u, v, c;
};

struct Soldier{
	int p, id;
	
	bool operator<( const Soldier& s ) const{
		return p < s.p;
	}
}sold[ 5100 ];

int cidade[ 5100 ];
int fila[ 5100 ];
int cap[ 5100 ][ 5100 ];
int dias[ 5100 ];
Aresta atual[ 5100 ];
int n;

void bfs(){
	fila[ 0 ] = 1;
	nos[ 0 ].next = -1;
	int ini = 0, fim = 1, temp, prox;
	
	while( ini < fim ){
		temp = fila[ ini++ ];
		
		for( int i = nos[ temp ].adj.size() - 1; i >= 0; --i ){
			prox = nos[ temp ].adj[ i ];
			if( nos[ prox ].next != 10000 ) continue;
			nos[ prox ].next = temp;
			
			fila[ fim++ ] = prox;
		}
	}
}

int main(){
	scanf( "%d", &n );
	fill( dias, dias + n, 0 );
	
 	for( int i = 1; i <= n; ++i ){
		scanf( "%d", &sold[ i ].p );
		sold[ i ].id = i;
		cidade[ i ] = i;
	}
	for( int i = 0; i < n - 1; ++i ){
		int u, v, c;
		scanf( "%d %d %d", &u, &v, &c );
		nos[ u ].adj.push_back( v );
		nos[ v ].adj.push_back( u );
		atual[ i ].u = u;
		atual[ i ].v = v;
		atual[ i ].c = c;
	}
	
	sort( sold + 2, sold + n + 1 );
	bfs();

	int temp;
	bool mudou = true;
	
	while( mudou ){
		for( int i = 0; i < n - 1; ++i ){
			cap[ atual[i].u ][ atual[i].v ] = atual[i].c;
			cap[ atual[i].v ][ atual[i].u ] = atual[i].c;
		}
		mudou = false;
		for( int i = 2; i <= n; ++i ){
			if( cidade[ sold[i].id ] == 1 ) continue;
			mudou = true;
			
			int p = sold[i].id;
			++dias[ p ];
			if( cap[ cidade[p] ][ nos[cidade[p]].next ] ){
				--cap[ cidade[p] ][ nos[cidade[p]].next ];
				--cap[ nos[cidade[p]].next ][ cidade[p] ];
				cidade[p] = nos[cidade[p]].next;
			}			
		}
	}
	printf( "%d", 0 );
	for( int i = 2; i <= n; ++i ){
		printf( " %d", dias[ i ] );
	}
	printf( "\n" );
	
}

