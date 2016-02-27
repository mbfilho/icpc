#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;

int x[ 5000 ], y[ 5000 ], cont, conta, mst;
int conj[ 5000 ];

int quad( int a ){
	return a * a;
}

class Aresta{
public:
	int a, b, peso;
	
	void calc(){
		peso = quad( x[ a ] - x[ b ] ) + quad( y[ a ] - y [ b ] );
	}
	
	bool operator<( const Aresta& a ) const{
		return peso < a.peso;
	}
}edges[ 1000000 ];

int find( int a ){
	if( conj[ a ] != a )
		conj[ a ] = find( conj[ a ] );
	
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

double kruskal(){
	int prt = 0;
	double resp = 0;
	
	sort( edges, edges + conta );
	while( prt < conta ){
		//printf( "%d\n", prt );
		//printf( "%d\n", mst );
		if( find( edges[ prt ].a ) != find( edges[ prt ].b ) ){
			unir( edges[ prt ].a, edges[ prt ].b );
			resp += sqrt( edges[ prt ].peso );
			++mst;
		}
		++prt;
	}
	
	return resp;
}

int main(){
	
	while( scanf( "%d", &cont ) != EOF ){
		for( int i = 1; i <= cont; ++i ){
			conj[ i ] = i;
			scanf( "%d %d", x + i, y + i ); 
		}
		
		scanf( "%d", &conta );
		int a, b;
		for( int i = 0; i < conta; ++i ){
			scanf( "%d %d", &a, &b );
			unir( a, b ); 
		}
		mst = conta;
		
		conta = 0;
		for( int i = 1; i <= cont; ++i ){
			for( int j = i + 1; j <= cont; ++j ){
				if( find( i ) != find( j ) ){
					edges[ conta ].a = i;
					edges[ conta ].b = j;
					edges[ conta ].calc();
					++conta;
				}
			}
		}
		
		printf( "%.2lf\n", kruskal() );
	}
}
