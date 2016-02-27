#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
/*
	A idéia: pegar as arestas em ordem decrescente de preferência. Isto é
a favorita, depois a segunda favorita etc. Também pegando primeiro todas as
opção do 1º candidato, depois do 2º... Se o fluxo foi calculado e existe a
atribuição do trabalhador i para a vaga j, então o par (i,j) faz parte da resposta. Devemos marcar essa atribuição de modo que um recalculo do fluxo
não "desmanche" essa aresta. O nó 'i' é excluido do grafo e a capacidade
do no 'j' é decrementada. Caso o fluxo na aresta (i,j) seja 0, devemos recalcular
o fluxo, mas dessa vez, fazendo a ligação direta da aresta (i,j). Caso o fluxo
maximo com essa configuração seja "fluxo anterior - 1", então essa atribuição
faz parte da configuração otima e temos que proceder como descrito acima para
que essa aresta não seja desmanchada em outro recalculo de fluxo. Caso o fluxo
obtido seja menor, então essa aresta não deve fazer parte da solução otima. 
Partimos para a proxima. É custoso mas passa =P.
*/

int n, m, flux[ 102 ][ 102 ], qtd, sink, source, caps[ 100 ];
int fila[ 102 ], pred[ 102 ], head, tail;
bool marc[ 102 ];
vector<int> adj[ 102 ];
bool excl[ 102 ];

void limpar(){
	for( int i = adj[ source ].size() - 1; i >= 0; --i ){
		flux[ source ][ adj[ source ][ i ] ] = 1;
		flux[ adj[ source ][ i ] ][ source ] = 0;
	}

	int origem;
	for( int i = adj[ sink ].size() - 1; i >= 0; --i ){
		origem = adj[ sink ][ i ];
		flux[ origem ][ sink ] = caps[ origem ];
		flux[ sink ][ origem ] = 0;
	}

	
	for( int i = m; i < m + n; ++i ){
		for( int j = adj[ i ].size() - 1; j > 0; --j ){
			flux[ i ][ adj[ i ][ j ] ] = 1;
			flux[ adj[ i ][ j ] ][ i ] = 0;
		}
	}

}

int bfs( int no ){
	for( int i = 0; i <= sink; ++i )
		marc[ i ] = false;
		
	head = tail = 0;
	
	fila[ tail++ ] = no;
	marc[ no ] = true;
	pred[ no ] = -1;
	
	int temp;
	
	while( head < tail && marc[ sink ] == false ){
		temp = fila[ head++ ];
		
		for( int i = adj[ temp ].size() - 1; i >= 0; --i ){
			if( !excl[ adj[ temp ][ i ] ] && marc[ adj[ temp ][ i ] ] == false && flux[ temp ][ adj[ temp ][ i ] ] ){
				pred[ adj[ temp ][ i ] ] = temp;
				fila[ tail++ ] = adj[ temp ][ i ];
				marc[ adj[ temp ][ i ] ] = true;
			}
		}
	}
	
	if( marc[ sink ] ){
		int menor = 0x7fffffff, atual = sink;

		while( pred[ atual ] != -1 ){
			menor = min( menor, flux[ pred[ atual ] ][ atual ] );
			atual = pred[ atual ];
		}

		atual = sink;
		while( pred[ atual ] != -1 ){
			flux[ pred[ atual ] ][ atual ] -= menor;
			flux[ atual ][ pred[ atual ] ] += menor;
			atual = pred[ atual ];
		}
		
		return menor;
	}
	
	return 0;
}

void liberar( int i, int j ){
	++flux[ i ][ j ];
	--flux[ j ][ i ];
}

void religar( int i, int j ){
	liberar( j, i );
}


//Faz o calculo do fluxo máximo do grafo
int maxflow(){
	int ret = 0, incr;
	while( ( incr = bfs( source ) ) )
		ret += incr;
	
	return ret;
}

int main(){
	int casos;
	
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d %d", &n, &m );
		source = n + m;
		sink = source + 1;
		
		for( int i = 0; i <= sink; ++i ){
			adj[ i ].clear();
		}
		
		for( int i = 0; i < m; ++i ){
			adj[ i ].push_back( sink );
			adj[ sink ].push_back( i );
			
			scanf( "%d", caps + i );
		}
		
		for( int i = 0; i < n; ++i ){
			adj[ source ].push_back( i + m );
			adj[ i + m ].push_back( source );
					
			int k, temp;
			scanf( "%d", &k );
			
			while( k-- ){
				scanf( "%d", &temp );
				--temp;
				adj[ i + m ].push_back( temp );
				adj[ temp ].push_back( i + m );
			}
		}
		
		fill( excl, excl + 102, false );
		limpar();
		qtd = maxflow();
		
		printf( "Case #%d:\n", c ); 
		printf( "%d applicant(s) can be hired.\n", qtd );
		
		int opcao;
		for( int i = m; i < m + n; ++i ){ //Para cada candidato
			for( int j = 1; j < adj[ i ].size(); ++j ){ //Para cada opcao daquele candidato
				opcao = adj[ i ][ j ];			
			
				if( flux[ i ][ opcao ] ){ //Aresta n utilizada	
					if( caps[ opcao ] <= 0 ) continue;
					limpar();
					flux[ source ][ i ] = flux[ source ][ i ] = 0;
					
					flux[ i ][ opcao ] = flux[ opcao ][ i ] = 0;
			
					--flux[ opcao ][ sink ];
					//+flux[ sink ][ opcao ];
					

					if( maxflow() == qtd - 1 ){
						printf( "%d %d\n", i - m + 1, opcao + 1 );
						--caps[ opcao ];
					//	aux.push_back( i );
						--qtd;
						break;
					}
				}else{
					printf( "%d %d\n", i - m + 1, opcao + 1 );
					--qtd;
					--caps[ opcao ];
				//	aux.push_back( i );
					break;
				}
			}
			excl[ i ] = true;
		}
		
	}
}
