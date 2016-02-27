#include <cstdio>
#include <list>
#include <algorithm>
using namespace std;

int conj[ 101 ];

class Aresta{
public:
	int a, b, peso;
	
	bool operator<( const Aresta& a ) const{
		return peso > a.peso;
	}
}edges[ 100000 ];	

int contn, conta, mst;
int pilha[ 200 ];

class are{
public:
	int b, peso;
	
	are( int a, int p ){
		b = a;
		peso = p;
	}
};

class No{
public:
	list<are> adj;
	int menor;
}agpm[ 200 ];

int find( int a ){
	if( a != conj[ a ] )
		conj[ a ] = find( conj[ a ] );
		
	return conj[ a ];
}

void unir( int a, int b ){
	conj[ find( a ) ] = find( b );
}

void kruskal(){
	mst = 0;
	int prt = 0;
	
	sort( edges, edges + conta );
	for( int i = 1; i <= contn; ++i )
		conj[ i ] = i;
		
	while( mst < contn - 1 ){
		if( find( edges[ prt ].a ) != find( edges[ prt ].b ) ){
			unir( edges[ prt ].a, edges[ prt ].b );
			agpm[ edges[ prt ].a ].adj.push_back( are( edges[ prt ].b, edges[ prt ].peso ) );
			agpm[ edges[ prt ].b ].adj.push_back( are( edges[ prt ].a, edges[ prt ].peso ) );
			++mst;
		}
		++prt;
	}
}

int busca( int ini, int fim ){
	int sp = 1, temp;
	pilha[ 0 ] = ini;
	
	for( int i = 1; i <= contn; ++i )
		agpm[ i ].menor = -1;
		
	agpm[ ini ].menor = 0x7fffffff;
	
	while( sp ){
		temp = pilha[ --sp ];
		for( list<are>::iterator it = agpm[ temp ].adj.begin(); it != agpm[ temp ].adj.end(); ++it ){
			if( agpm[ it -> b ].menor != -1 )
				continue;
			agpm[ it -> b ].menor = min( agpm[ temp ].menor, it -> peso );
			pilha[ sp++ ] = it -> b;
		}
	}
	
	return agpm[ fim ].menor;
}

int main(){
	int casos = 1;
	int a, b, peso;
	int ini, fim, passageiros;
	
	while( scanf( "%d %d", &contn, &conta ) && ( contn | conta ) ){
		for( int i = 0; i < conta; ++i ){
			scanf( "%d %d %d", &a, &b, &peso );
			edges[ i ].a = a;
			edges[ i ].b = b;
			edges[ i ].peso = peso;
		}
		
		for( int i = 1; i <= contn; ++i )
			agpm[ i ].adj.clear();
			
		scanf( "%d %d %d", &ini, &fim, &passageiros );
	
		kruskal();
		
		printf( "Scenario #%d\n", casos++ );
		
		int menor = busca( ini, fim ) - 1;
		printf( "Minimum Number of Trips = " );
		if( passageiros % menor == 0 )
			printf( "%d\n\n", passageiros / menor );
		else
			printf( "%d\n\n", 1 + passageiros / menor );
	}
}


