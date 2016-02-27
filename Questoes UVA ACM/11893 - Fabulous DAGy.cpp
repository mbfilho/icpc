#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define N 410
#define mp make_pair

/*
Suponha VinX como "vértice com grau de entrada X"
 Suponha VoutX como "vértice com grau de saída X"

Propriedades relevantes de DAGs: 
Existe pelo menos um Vin0.
Existe pelo menos um Vout0.
Suponha que o DAG tenha dois ou mais Vin0, logo não importa onde coloquemos a nova aresta, o grafo continuará com pelo menos um Vin0, impossibilitando a existencia de um circuito.
 Suponha que o DAG tenha dois ou mais Vout0, logo não importa onde coloquemos a nova aresta, o grafo continuará com pelo menos um Vout0, impossibilitando a existência de um circuito.

Logo, para que um DAG + Aresta possa ter um circuito hamiltoniano, o DAG obrigatoriamente tem que ter exatemente um Vin0 e exatamente um Vout0.
 A nova aresta obrigatoriamente deve ser entre o Vout0 e o Vin0, porque se não for, o grafo continuará tendo um Vout0 ou um Vin0, o que impossibilitaria a existência de um circuito.

Suponha que sabemos a priori que a aresta foi colocada entre o vértice A e o vértice B e o DAG possui as propriedade satisfatorias acima (A é o único Vout0 e B é o único Vin0).
 Logo para verificar se o grafo tem um circuito hamiltoniano é só verificar se existe um caminho de A até B que passe por todos os vértices. Como a única aresta que pode gerar ciclos no grafo é a aresta que liga A a B, basta rodar o algoritmo de longest path de B até A e verificar se a longest path passa por todos os N vértices.

Como não sabemos onde a aresta foi adicionada, precisamos testar o algoritmo acima para todas as tuplas (A,B) tal que A e B sejam Vin1 e Vout1.

***ddp***
*/
int marc[ N ];
vector<int> adj[ N ];
int ord[ N ], prt;
int vin[ N ], vout[ N ], dist[ N ];
int n, m;

bool dfs( int no, pair<int,int> ed ){
	marc[ no ] = 1;
	
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		int next = adj[ no ][ i ];
		if( ( ed.first == no && ed.second == next ) || ( marc[ next ] == 2 ) ) continue;
		if( marc[ next ] == 1 ) return false;
		
		if( !dfs( next, ed ) ) return false;
	}
	
	marc[ no ] = 2;
	ord[ prt++ ] = no;
	
	return true;
}

bool path( pair<int,int> ed ){
	memset( dist, -1, sizeof( dist ) );
	dist[ ord[ prt - 1 ] ] = 0;
	
	for( int i = prt - 1; i >= 0; --i ){
		int atual = ord[ i ];
		
		for( int j = adj[ atual ].size() - 1; j >= 0; --j ){
			int next = adj[ atual ][ j ];
			if( atual == ed.first && next == ed.second ) continue;
			
			if( dist[ atual ] + 1 > dist[ next ] )
				dist[ next ] = dist[ atual ] + 1;
		}
	}
	
//	printf( "Prt %d >>> %d\n",prt, dist[ ed.first ] );
	return dist[ ed.first ] == n - 1;
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d", &n, &m );
		for( int i = 0; i < n; ++i ){
			adj[ i ].clear();
			vin[ i ] = 0;
			vout[ i ] = 0;
		}
		
		for( int i = 0; i < m; ++i ){
			int u, v;
			scanf( "%d %d", &u, &v );
			
			++vout[ u ];
			++vin[ v ];
			adj[ u ].push_back( v );
		}
		
		bool achei = false;
		
		for( int i = 0; !achei && i < n; ++i ){
			if( vout[ i ] != 1 ) continue;
			
			for( int j = 0; !achei && j < n; ++j ){
				if( vin[ j ] != 1 || i == j ) continue;
				
//				printf( "Testing %d, %d\n", i, j );
				memset( marc, 0, sizeof( marc ) );
				prt = 0;
				if( dfs( j, mp( i, j ) ) ){
//					printf( "sim\n" );
					if( path( mp( i, j ) ) )
						achei = true; 
				}
//				else
//					printf( "no\n" );
			}
		}
		
		if( achei )
			printf( "Yeah, I'm superman\n" );
		else
			printf( "Your DAGy was initially defected!\n" );
		
	}
}





