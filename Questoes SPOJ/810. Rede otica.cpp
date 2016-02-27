#include <cstdio>
#include <algorithm>
using namespace std;

struct Aresta{
	int a, b, p;
	
	bool operator<( const Aresta& a ) const{
		return p < a.p;
	}
}are[100000];

int n, m, conj[ 100000 ];

int find( int a ){
	if( conj[ a ] == a )
		return a;
	return conj[ a ] = find( conj[ a ] );
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

void kru(){
	for( int i = 1; i <= n; ++i )
		conj[ i ] = i;
		
	sort( are, are + m );
	int cont = 0, ind = 0;
	
	while( cont < n - 1 ){
		if( find( are[ ind ].a ) != find( are[ ind ].b ) ){
			unir( are[ ind ].a, are[ ind ].b );
			printf( "%d %d\n", min(are[ind].a,are[ind].b), max(are[ind].a,are[ind].b) );
			++cont;
		}
		++ind;
	}
}

int main(){
	int teste = 1;
	
	while( scanf( "%d %d", &n, &m ) && n ){
		for( int i = 0; i < m; ++i )
			scanf( "%d %d %d", &are[ i ].a, &are[ i ].b, &are[ i ].p );
		
		printf( "Teste %d\n", teste++ );
		kru();
		printf( "\n" );
	}
}


