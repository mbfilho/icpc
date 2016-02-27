#include <cstdio>
#include <list>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

typedef long long ll;
#define INF 0x7fffffffffffffffLL

ll dist[ 20000 ];

list< pair<int,int> > adj[ 20000 ];
int cont, conta, ini, fim;

void dij(){
	priority_queue< pair<int,ll> > heap;
	list< pair<int,int> >::iterator it;
	dist[ ini ] = 0;
	heap.push( make_pair( 0, ini ) );
	int id;
	ll dista;
	
	while( heap.empty() == false ){
		id = heap.top().second;
		dista = - heap.top().first;
		heap.pop();
		
		if( dist[ id ] != dista )
			continue;
		
		if( id == fim )
			break;
			
		for( it = adj[ id ].begin(); it != adj[ id ].end(); ++it ){
			if( dist[ it -> first ] > dista + it -> second ){
				dist[ it -> first ] = dista + it -> second;
				heap.push( make_pair( - dist[ it -> first ], it -> first ) );
			}
		}
	}
	
}

int main(){
	int casos, a, b, p;
	
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d %d %d %d", &cont, &conta, &ini, &fim );
		fill( dist, dist + cont, INF );
		
		for( int i = 0; i < cont; ++i )
			adj[ i ].clear();
		
		for( int i = 0; i < conta; ++i ){
			scanf( "%d %d %d", &a, &b, &p );
			adj[ a ].push_back( make_pair( b, p ) );
			adj[ b ].push_back( make_pair( a, p ) );
		}
		
		dij();
		
		if( dist[ fim ] == INF )
			printf( "Case #%d: unreachable\n", c );
		else
			printf( "Case #%d: %d\n", c, dist[ fim ] );
	}
}


