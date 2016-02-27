#include <cstdio>
#include <cstring>

#include <algorithm>
using namespace std;
#define N 200
#define M 200

int n, m;
int dist[ N ];
int peso[ M ], cont, ft[ M ], sd[ M ];

void add( int u, int v, int p ){
	peso[ cont ] = p;
	ft[ cont ] = u;
	sd[ cont ]= v;
	++cont;
}

bool ford(){
	for( int i = 0; i < n; ++i ){
		for( int e = 0; e < cont; ++e )
			dist[ sd[e] ] = min( dist[ sd[e] ], dist[ ft[e] ] + peso[ e ] );
	}
	
	for( int e = 0; e < cont; ++e ){
		if( dist[ sd[e] ] > dist[ ft[e] ] + peso[ e ] )
			return true;
	}
	
	return false;
}

char op[ 10 ];
int main(){
	
	while( scanf( "%d", &n ) != EOF && n ){
		scanf( "%d", &m );
		cont = 0;
		
		for( int i = 0; i < m; ++i ){
			int ini, tam, k;
			scanf( "%d %d %s %d", &ini, &tam, op, &k );
			if( op[ 0 ] == 'l' )
				add( ini - 1, ini + tam, k - 1 );
			else
				add( ini + tam, ini - 1, - k - 1 );
			
		}
		
		memset( dist, 0, sizeof( dist ) );
		
		if( ford() )
			printf( "successful conspiracy\n" );
		else
			printf( "lamentable kingdom\n" );		
		
			
	}
}




