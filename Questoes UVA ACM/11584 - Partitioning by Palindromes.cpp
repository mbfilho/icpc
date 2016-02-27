#include <cstdio>
#include <cstring>
#include <list>
#include <queue>
using namespace std;
/*
*******************************************
*Atenção em caso de resubmissao!
*A matriz de booleano deve ser 1001x1001 !!!!!!!!!!
Legal esse problema. 
Primeiro construa uma matriz com as dimensões maximas para responder em O(1) se uma
substring sub(i,j) é palindromo ou não. O preenchimento da matriz, obvio, leva O(n²).
Uma string é palindromo se as extremidades são iguais e o meio for um palindromo.
Ou seja:
string[ i ] == string[ j ] AND sub( i - 1, j - 1 ) == true
Depois de preencher essa tabela, faça uma busca em largura para determinar a divisao
que contem o menor numero de palindromos. O grafo é construído em conjunto com o
preenchimento da tabela. Se a substring sub(i,j) é um palindromo de tamanho 'k',
então o nó "i" do grafo tem uma aresta que o liga ao nó 'j'. Se a substring sub(i,h)
é um palindromo de tamanho 'p', então o nó "i" também tem uma aresta para o nó "h"
Após construir toda a adjacência, basta fazer uma Busca em Largura 
( ou um Dij, se quiser ) para calcular a distancia até o final da string.
*/

int tam;
class No{
	public:
		bool marcado;
		int indice;
		int dist;
		list<int> adj;
};

int busca( No *nos ){
	queue<int> fila;
	fila.push( 0 );
	nos[ 0 ].marcado = true;
	nos[ 0 ].dist = 1;
	list<int>::iterator it;

	No *aux;
	while( fila.size() ){

		aux = &nos[ fila.front() ];
		fila.pop();

		for( it = aux -> adj.begin(); it != aux -> adj.end(); ++it ){
			if( *it >= tam ){
				return aux -> dist;
			}else if( nos[ *it ].marcado == false ){
				fila.push( *it );
				nos[ *it ].marcado = true;
				nos[ *it ].dist = aux -> dist + 1;
			}
		}
	}

}

int main(){
	bool matriz[ 100 ][ 100 ];
	int casos;
	char nome[ 2000 ];
	No nos[ 2000 ];

	freopen( "in.txt", "r", stdin );
	scanf( "%d", &casos );

	while( casos-- ){
		scanf( "%s", nome );
		tam = strlen( nome );

		for( int k = 0; k < tam; ++k ){
			for( int i = 0; i < tam - k; ++i )
				matriz[ i ][ i + k ] = false;
		}

		for( int i = 0; i < tam; ++i ){
			nos[ i ].marcado = false;
			nos[ i ].adj.clear();
		}

		//Palindromos de uma letra
		for( int i = 0; i < tam; ++i ){
			matriz[ i ][ i ] = true;
			nos[ i ].adj.push_back( i + 1 );
		}

		//Palindromos de 2 letras
		for( int i = 0; i < tam - 1; ++i ){
			if( nome[ i ] == nome[ i + 1 ] ){
				matriz[ i ][ i + 1 ] = true;
				nos[ i ].adj.push_back( i + 2 ) ;
			}
		}

		//Palindromos de k + 1 letras
		for( int k = 2; k < tam; ++k ){
			for( int i = 0; i < tam - k; ++i ){
				if( nome[ i ] == nome[ i + k ] && matriz[ i + 1 ][ i + k - 1 ] ){
					matriz[ i ][ i + k ] = true;
					nos[ i ].adj.push_back( (i + k + 1) );
				}else
					matriz[ i ][ i + k ] = false;
			}
		}

		printf( "%d\n", busca( nos ) );
	}
}
