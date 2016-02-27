#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
using namespace std;
/*
Basta seguir as instruções da questão.
Verifique:
	* se existe exatamente 1 vértice sem arestas de entrada
	* se existe exatamente 1 caminho entre esse vertice e todos os outros ( faça uma busca, dfs por exemplo )
	* lembre que o grafo pode ser vazio
Para facilitar, faça um mapeamento dos numeros da entrada ( porque se o maior vertice, por exemplo, 
é N, não é garantido que todos os vertices 1..N-1 apareçam ).
*/
#define N 50000

vector<int> adj[ N ];
bool marc[ N ];
int qtd[ N ];
int mapa[ N ];
int prt;
bool ehArv;

void dfs( int no ){
	marc[ no ] = true;
	
	for( int i = adj[ no ].size() - 1; i >= 0; --i ){
		if( marc[ adj[no][i] ] )
			ehArv = false;
		else
			dfs( adj[no][i] );
	}
}

int main(){
	int u, v;
	int caso = 1;
	
	while( scanf( "%d %d", &u, &v ) != EOF && ( u >= 0 && v >= 0 ) ){
		prt = 0;
		for( int i = 0; i < N; ++i ) adj[ i ].clear();
		memset( mapa, -1, sizeof( mapa ) );
		memset( qtd, 0, sizeof( qtd ) );
		
		while( u > 0 && v > 0 ){
			if( mapa[ u ] == -1  )
				mapa[ u ] = prt++;
			if( mapa[ v ] == -1 )
				mapa[ v ] = prt++;
			++qtd[ mapa[ v ] ];
			adj[ mapa[ u ] ].push_back( mapa[ v ] );
			scanf( "%d %d", &u, &v );
		}
		ehArv = true;
		int root = -1;
		for( int i = 0; ehArv && i < prt; ++i ){
			if( qtd[ i ] == 0 ){
				if( root == -1 )
					root = i;
				else{
					ehArv = false;
				}
			}
		}
		if( root == -1 && prt ) ehArv = false;
		
		if( ehArv ){
			memset( marc, false, sizeof( marc ) );
			dfs( root );
			for( int i = 0; i < prt && ehArv; ++i ){
				if( !marc[ i ] ) ehArv = false;
			}
		}
		if( ehArv )
			printf( "Case %d is a tree.\n", caso++ );
		else
			printf( "Case %d is not a tree.\n", caso++ );
		
	}
}



