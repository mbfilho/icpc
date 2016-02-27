#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;

class Aresta{
public:
	int a, b;
	int peso;
	
	bool operator< ( const Aresta& e ) const{
		return peso < e.peso;
	}
}edges[ 250000 ];

class Ponto{
public:
	int x, y;
}nos[ 500 ];

int cont, qtd_aresta, satelites;

int conj[ 500 ], agpm[ 500 ];

int find( int a ){
	if( conj[ a ] != a )
		conj[ a ] = find( conj[ a ] );
		
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

void kruscal(){
	for( int i = 0; i < cont; ++i )
		conj[ i ] = i;
	
	sort( edges, edges + qtd_aresta );
	
	int ares = 0, mst = 0;
	
	const int qtd = cont - satelites;
	while( mst < qtd ){		
		if( find( edges[ ares ].a ) != find( edges[ ares ].b ) ){
			unir( edges[ ares ].a, edges[ ares ].b );
			agpm[ mst ] = edges[ ares ].peso;
			++mst;
		}
		++ares;
	}
}

int main(){
	int casos, x, y, peso;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &satelites, &cont );
		
		for( int i = 0; i < cont; ++i ){
			scanf( "%d %d", &x, &y );
			nos[ i ].x = x;
			nos[ i ].y = y;
		}
		
		qtd_aresta = 0; 
		for( int i = 0; i < cont; ++i ){
			for( int j = i + 1; j < cont; ++j ){
				peso = ( nos[ i ].x - nos[ j ].x ) * ( nos[ i ].x - nos[ j ].x );
				peso += ( nos[ i ].y - nos[ j ].y ) * ( nos[ i ].y - nos[ j ].y );
				edges[ qtd_aresta ].a = i; 
				edges[ qtd_aresta ].b = j; 
				edges[ qtd_aresta ].peso = peso;
				++qtd_aresta;
			}
		}
		
		kruscal();
		double resp = sqrt( agpm[ cont - satelites - 1 ] );
		printf( "%.2f\n", resp );
		
	}
}

