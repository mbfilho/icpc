#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int conj[ 100 ];

double x[ 100 ], y[ 100 ];
int cont;

class Aresta{
public:
	int a, b;
	double peso;
	
	void calc(){
		peso = ( x[ a ] - x[ b ] ) * ( x[ a ] - x[ b ] ) + ( y[ a ] - y[ b ] ) * ( y[ a ] - y[ b ] );
	}
	
	bool operator<( const Aresta& a ) const{
		return peso < a.peso;
	}
}edges[ 10001 ]; 

int find( int a ){
	if( conj[ a ] != a )
		conj[ a ] = find( conj[ a ] );
	
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

double kruskal(){
	for( int i = 0; i < cont; ++i )
		conj[ i ] = i;
		
	double peso = 0;
	sort( edges, edges + cont * ( cont - 1 ) );
	int mst = 0, prt = 0;
	
	while( mst != cont - 1 ){
		if( find( edges[ prt ].a ) != find( edges[ prt ].b ) ){
			unir( edges[ prt ].a, edges[ prt ].b );
			peso += sqrt( edges[ prt ].peso );
			++mst;
		}		
		
		++prt;
	}
	
	return peso;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &cont );
		
		for( int i = 0; i < cont; ++i )
			scanf( "%lf %lf", x + i, y + i );
		
		int prt = 0;
		for( int i = 0; i < cont; ++i ){
			for( int j = i + 1; j < cont; ++j ){
				edges[ prt ].a = i;
				edges[ prt ].b = j;
				edges[ prt ].calc();
				++prt;
			}
		}
		
		printf( "%.2lf\n", kruskal() );
		
		if( casos )
			printf( "\n" );
		
			
	}
}
