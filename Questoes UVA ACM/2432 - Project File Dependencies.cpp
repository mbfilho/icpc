#include <cstdio>
#include <list>
#include <queue>
using namespace std;


/*
	Monte o grafo da seguinte maneira: existe uma aresta direcionada (t1, t2) se
a tarefa t2 depende de t1. Isto é, toda vez que uma tarefa depende de uma outra,
ela recebe uma aresta e seu grau de entrada aumenta. Feito isso, "executando" as 
tarefas da seguinte forma: escolha primeiro a tarefa que não dependende de ninguem,
ou seja, tem grau = 0. Cada vez que uma tarefa é escolhida, decremente os graus das 
tarefas adjacentes, ou seja, das tarefas que dependem dela. Uma vez atualizados os
graus, retome o processo.
*/

class No{
public:
	list<int> adj;
	int grau, id;
	
	bool operator<( const No& a ) const{
		bool retorno;
		
		if( grau == a.grau )
			retorno = ( id < a.id );
		else 
			retorno = ( grau < a.grau );
		
		return !retorno;			
	}
	
}nos[ 200 ];

int main(){
	int casos, cont, regras;
	for( int i = 1; i <= 200; ++i )
		nos[ i ].id = i;
		
	scanf( "%d", &casos );
	
	for( int m = 1; m <= casos; ++m ){
		scanf( "%d %d", &cont, &regras );
		
		for( int i = 1; i <= cont; ++i ){
			nos[ i ].adj.clear();
			nos[ i ].grau = 0;
		}
		
		int a, b, k;
		for( int i = 1; i <= regras; ++i ){
			scanf( "%d %d", &a, &k );
			for( int j = 0; j < k; ++j ){
				scanf( "%d", &b );
				nos[ b ].adj.push_back( a );
				++nos[ a ].grau;
			}
		}
		
		priority_queue<No> heap;
		
		for( int i = 1; i <= cont; ++i ){
			if( nos[ i ].grau == 0 )
				heap.push( nos[ i ] );
		}
			
		list<int>::iterator it;
		int id;
		for( int i = 1; i <= cont; ++i ){
			id = heap.top().id;
			heap.pop();
			printf( "%d%c", id, ( i == cont ) ? '\n' : ' ' );
			for( it = nos[ id ].adj.begin(); it != nos[ id ].adj.end(); ++it ){
				--nos[ *it ].grau;
				if( nos[ *it ].grau == 0 )
					heap.push( nos[ *it ] );
			}
		}
		
		if( m != casos )
			printf( "\n" );
		
	}

}
