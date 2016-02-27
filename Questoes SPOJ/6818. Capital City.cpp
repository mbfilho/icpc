#include <list>
#include <algorithm>
#include <cstdio>
using namespace std;
#define menor( a, b ) (a) < (b) ? (a) : (b);

class No{
public:
	int comp;
	int tempo, pai;
	bool excluido;
	list<int> adj;
	
	No(){
		tempo = -1;
		excluido = false;
	}
}nos[ 100101 ];

int pilha[ 100101 ], sp, tempo, componente;
bool candidata[ 100101 ];

class Componente{
public:
	list<int> comps;
}dag[ 100101 ];

void dfs( int no ){
	nos[ no ].tempo = nos[ no ].pai = tempo;
	++tempo;
	list<int>::iterator it;
	
	pilha[ sp ] = no;
	sp++;
	
	for( it = nos[ no ].adj.begin(); it != nos[ no ].adj.end(); ++it ){
		if( nos[ *it ].excluido == false ){	
			if( nos[ *it ].tempo == -1 ){
				dfs( *it );
				nos[ no ].pai = menor( nos[ no ].pai, nos[ *it ].pai );
			}else
				nos[ no ].pai = menor( nos[ no ].pai, nos[ *it ].tempo );
		}
	}
		
	if( nos[ no ].tempo == nos[ no ].pai ){
		int temp;
		do{			
			--sp;
			temp = pilha[ sp ];
			nos[ temp ].excluido = true;
			nos[ temp ].comp = componente;
			dag[ componente ].comps.push_back( temp );
		}while( temp != no );
		++componente;
	}
}

int main(){
	int n, m, a, b;
	
	scanf( "%d %d", &n, &m );
	
	for( int i = 0; i < m; ++i ){
		scanf( "%d %d", &a, &b );
		nos[ a ].adj.push_back( b );
	}
	
	tempo = componente = sp = 0;
	
	for( int i = 1; i <= n; ++i ){
		if( nos[ i ].tempo == -1 )
			dfs( i );
	}
	
	fill( candidata, candidata + componente, true );
	list<int>::iterator it;
	for( int i = 1; i <= n; ++i ){
		for( it = nos[ i ].adj.begin(); it != nos[ i ].adj.end(); ++it ){
			a = nos[ i ].comp;
			b = nos[ *it ].comp;
			
			if( a != b )
				candidata[ a ] = false;
		}
	}
	
	int k = -1;
	bool valido = true;
			
	for( int i = 0; i < componente && valido; ++i ){
		if( candidata[ i ] ){
			if( k != -1 )
				valido = false;
			
			k = i;
		}
	}
	
	if( valido == false )
		printf( "0\n" );
	else{
		int qtd = dag[ k ].comps.size();
		printf( "%d\n", qtd );
		dag[ k ].comps.sort();	
		it = dag[ k ].comps.begin();
		
		for( int i = 0; i < qtd; ++i ){
			printf( "%d%c", *it, ( i == qtd - 1 ) ? '\n' : ' ' );
			++it;
		}
	}
		
}
