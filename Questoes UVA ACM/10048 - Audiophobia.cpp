#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;

const int MAX_EDGES = 1700, MAX_VERTICES = 200;
int conj[ MAX_VERTICES ], pilha[ MAX_VERTICES ];
int nos, ares, cont;

class Edge{
public:
	int u, v, peso;
	
	Edge( int a, int b, int p ){
		u = a;
		v = b;
		peso = p;
	}
	
	Edge(){}
	
	bool operator<( const Edge& e ) const{
		return peso < e.peso;
	}
}arestas[ MAX_EDGES ];


class Are{
public:
	int no, peso;
	
	Are( int v, int p ){
		no = v;
		peso = p;
	}
};

class No{
public:
	list<Are> adj;
	bool marcado;
	int maior;
}agpm[ MAX_VERTICES ];

int maior( int a, int b ){
	if( a > b )
		return a;
	return b;
}

int find( int a ){
	if( conj[ a ] != a )
		conj[ a ] = find( conj[ a ] );
	
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

void kruscal(){
	cont = 0;
	int u, v;
	sort( arestas, arestas + ares );
	
	for( int i = 1; i <= nos; ++i )
		conj[ i ] = i;
		
	for( int i = 0; i < ares; ++i ){
		if( cont == nos - 1 )
			break;
		u = arestas[ i ].u;
		v = arestas[ i ].v;
		if( find( u ) != find( v ) ){
			unir( u, v );
			++cont;
			agpm[ u ].adj.push_back( Are( v, arestas[ i ].peso ) );
			agpm[ v ].adj.push_back( Are( u, arestas[ i ].peso ) );
		}
	}
}

void busca( int ini ){
	int sp = 1, temp;
	list<Are>::iterator it;
	pilha[ 0 ] = ini;
	
	for( int i = 1; i <= nos; ++i ){
		agpm[ i ].marcado = false;
		agpm[ i ].maior = -1;
	}
	
	agpm[ ini ].marcado = true;
	while( sp ){
		temp = pilha[ --sp ];
		
		for( it = agpm[ temp ].adj.begin(); it != agpm[ temp ].adj.end(); ++it ){
			if( agpm[ it -> no ].marcado == false ){
				agpm[ it -> no ].marcado = true;
				agpm[ it -> no ].maior = maior( agpm[ temp ].maior, it -> peso );
				pilha[ sp++ ] = it -> no;
			}
		}
	}
}

int main(){
	int q, caso = 1;
	bool primeiro = true;
	
	while( scanf( "%d %d %d", &nos, &ares, &q ) && ( nos | ares | q ) ){
		if( primeiro )
			primeiro = false;
		else
			printf( "\n" );
			
		for( int i = 1; i <= nos; ++i )
			agpm[ i ].adj.clear();
			
		int u, v, p;
		for( int i = 0; i < ares; ++i ){
			scanf( "%d %d %d", &u, &v, &p );
			arestas[ i ] = Edge( u, v, p );
		}
		
		kruscal();
		printf( "Case #%d\n", caso );
		++caso;
		
		for( int i = 0; i < q; ++i ){
			scanf( "%d %d", &u, &v );
			busca( u );
			
			
			if( agpm[ v ].maior == -1 )
				printf( "no path\n" );
			else 
				printf( "%d\n", agpm[ v ].maior );
		}
		
	}
}

