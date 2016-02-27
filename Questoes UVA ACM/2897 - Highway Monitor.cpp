#include <cstdio>
#include <list>
#include <vector>
#include <algorithm>
using namespace std;

//Vertex cover

struct No{
	vector<int> adj;
	bool marc;
	
}nos[ 2000 ];

//Guarda a resposta ( o vertex cover, se houver )
int resp[ 2000 ], tam;

//Guarda os nos sendo testados e que podem formar um conjunto valido
int temp[ 2000 ], n, h, k;
bool achou;


//Conta o numero de arestas a serem cobertas, caso o no "no" seja adcionado ao conjunto
int contar( int no ){
	int cont = 0, qtd = nos[ no ].adj.size();
	for( int i = 0; i < qtd; ++i ){
		if( nos[ nos[no].adj[i] ].marc == false )
			++cont;
	}
	
	return cont;	
}


//Vertice a ser analizado, qtd de arestas a serem cobertas, qtd de vertices na solucao atual
void rec( int vertex, int ares, int cont ){
	if( achou ) return;
	
	if( cont > k ) return;
	
	//Nenhuma aresta a ser coberta! Achou solução
	if( ares == 0 ){
		achou = true;
		tam = cont;
		copy( temp, temp + cont, resp );
		//resp = vector<int>( temp, temp + cont );
		
		return;
	}
	
	if( nos[ vertex ].marc ) //O no esta marcado, so há uma opção: passar para o proximo
		rec( vertex + 1, ares, cont );
	else{
		int novas = contar( vertex );
		if( novas == 0 )
		//Todos os adjs ao nó estao no conjunto, logo, passe para o proximo;
			rec( vertex + 1, ares, cont );
		else{
			//Dois testes
			//Primeiro, não adiciona o vertice, e adiciona todos os adjs a ele
			int aux = cont;
			int novasArestas = 0;
			int qtd = nos[vertex].adj.size(), adj;
			for( int i = 0; i < qtd; ++i ){
				adj = nos[vertex].adj[i];
				if( nos[ adj ].marc == false ){
					temp[ aux++ ] = adj;
					novasArestas += contar( adj );
					nos[ adj ].marc = true;
				}
			}
			rec( vertex + 1, ares - novasArestas, aux );
			for( int i = cont; i < aux; ++i )
				nos[ temp[i] ].marc = false;//tirar( temp[ i ] );
				
			
			//Segundo, adiciona o vertice
			nos[ vertex ].marc = true;//poe( vertex );
			temp[ cont ] = vertex;
			rec( vertex + 1, ares - novas, cont + 1 );
			//tirar( vertex );
			nos[ vertex ].marc = false;//poe( vertex );
			
		}
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	
	for( int c = 1; c <= casos; ++c ){
		scanf( "%d %d %d", &n, &h, &k );
		for( int i = 1; i <= n; ++i ){
			nos[ i ].adj.clear();
			nos[ i ].marc = false;
//			nos[ i ].qtdMarc = 0;
		}
		
		int a, b;
		for( int i = 0; i < h; ++i ){
			scanf( "%d %d", &a, &b );
			nos[ a ].adj.push_back( b );
			nos[ b ].adj.push_back( a );
		}
		
		achou = false;
	//	resp.clear();
		rec( 1, h, 0 );
		
		if( achou == false )
			printf( "Case #%d: no\n", c );
		else{
			printf( "Case #%d: yes", c );
			for( int i = 0; i < tam; ++i )
				printf( " %d", resp[ i ] );
			printf( "\n" );
		}
	}
}

