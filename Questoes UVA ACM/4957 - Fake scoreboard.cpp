#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define INFI 0x7fffffff
#define MAXI 400

/*
Problema modelado com bipartite matching. O detalhe é que a solução, se multipla, 
deve ser a menor lexicograficamente. Para isso, o ideal é que cada time resolva sempre
os ultimos problemas ( para os 'N' ficarem na frente da string ). Após rodar o algoritmo,
teremos um fluxo que corresponde a uma atribuição possível. Para garantir a ordem 
lexicografica, vamos excluir cada uma das arestas, tentando mudar as atribuições.
Isto é, se uma aresta é do tipo Y ( uma atribuição entre um time e um problema ),
excluimos essa aresta, restauramos o fluxo do seu caminho e verificamos se, mesmo
sem essa aresta, é possivel alcançar o fluxo máximo. Para isso, basta verificar se 
é possivel encontrar um aumenting path. Se for possivel, essa aresta passa a ser N.
Caso contrario ela é Y mesmo. 
*/
int res[ MAXI ][ MAXI ];

//Para o bfs 
int lista[ MAXI ], head, tail, pred[ MAXI ];
bool marc[ MAXI ];

int source, sink, flux, cont;

int t, p;
int times[ MAXI ], probs[ MAXI ];

struct No{
	vector<int> adj;
}nos[ MAXI ];


bool bfs( int inicio = source ){
	fill( pred, pred + cont, -1 );
	fill( marc, marc + cont, false );
	head = 0;
	tail = 1;

	lista[ 0 ] = inicio;
	marc[ inicio ] = true;
	
	int no, adj;
	
	while( head < tail ){
		no = lista[ head++ ];
		
		for( int i = nos[ no ].adj.size() - 1; i >= 0; --i ){
			adj = nos[ no ].adj[ i ];
			
			if( marc[ adj ] == false && res[ no ][ adj ] != 0 ){
				marc[ adj ] = true;
				pred[ adj ] = no;
				lista[ tail++ ] = adj;
				
				if( adj == sink )
					return true;
			}
		}
	}
	
	return false;
}

int path(){
	int retorno = INFI;
	int ant = pred[ sink ], pos = sink;

	while( ant != -1 ){
		retorno = min( retorno, res[ ant ][ pos ] );
		pos = ant;
		ant = pred[ ant ];
	}

	return retorno;
}

void atualiza(){
	int aum, ant, pos;
	
	aum = path();
	flux += aum;

	pos = sink;
	ant = pred[ sink ];
		
	while( ant != -1 ){
		res[ ant ][ pos ] -= aum;
		res[ pos ][ ant ] += aum;
		pos = ant;
		ant = pred[ ant ];
	}
}

void fluxo(){
	flux = 0;
	
	while( bfs() ){
		atualiza();
	}	
}

int main(){
	scanf( "%d %d", &t, &p );
	
	while( ( p | t ) ){
		int somaT = 0, somaP = 0;

		for( int i = 0; i < t; ++i ){
			scanf( "%d", times + i );
			somaT += times[ i ];
		}
	
		for( int i = 0; i < p; ++i ){
			scanf( "%d", probs + i );
			somaP += probs[ i ];
		}
		
		if( somaP != somaT )
			printf( "Impossible\n" );
		else{
		
			cont = t + p + 2;
			for( int i = 0; i < cont; ++i )
				nos[ i ].adj.clear();
			
			for( int i = 0; i < t; ++i ){
				for( int j = t; j < t + p; ++j ){
					res[ i ][ j ] = 1;
					res[ j ][ i ] = 0;
					nos[ i ].adj.push_back( j );
					nos[ j ].adj.push_back( i );
				}
			}
			
			source = t + p;
			sink = source + 1;
			for( int i = 0; i < t; ++i ){
				nos[ source ].adj.push_back( i );
				nos[ i ].adj.push_back( source );
				
				res[ source ][ i ] = times[ i ];
				res[ i ][ source ] = 0;
			}
			
			for( int i = t; i < t + p; ++i ){
				nos[ i ].adj.push_back( sink );
				nos[ sink ].adj.push_back( i );
				
				res[ i ][ sink ] = probs[ i - t ];
				res[ sink ][ i ] = 0;
			}
			fluxo();
			
			
			if( flux != somaT )
				printf( "Impossible\n", flux );
			else{			
				for( int i = 0; i < t; ++i ){
					for( int j = t; j < t + p; ++j ){
						if( res[ i ][ j ] == 1 ){ //Tipo N
							res[ i ][ j ] = res[ j ][ i ] = 0;//Descarta essa aresta
							printf( "N" );
						}else{ //Tipo Y
						//	printf( "Y" );
							
						//	res[ i ][ j ] = res[ j ][ i ] = 0;//Descarta essa aresta
						
							//Restaura o fluxo do caminho da aresta
							++res[ source ][ i ];
							--res[ i ][ source ];
							++res[ j ][ sink ];
							--res[ sink ][ j ];
							
							if( bfs( i ) ){ //A aresta mudou de tipo
								--res[ source ][ i ];
								++res[ i ][ source ];
								atualiza();
								printf( "N" );
							}else{ // A aresta não mudou de tipo. O fluxo deve ser refeito
								printf( "Y" );
								--res[ source ][ i ];
								++res[ i ][ source ];
								--res[ j ][ sink ];
								++res[ sink ][ j ];
							}
							
						}
					}
					
					printf( "\n" );
				}
				
			}
		
		}
		
		scanf( "%d %d", &t, &p );
		
		if( p | t )
			printf( "\n" );
	}	
}
