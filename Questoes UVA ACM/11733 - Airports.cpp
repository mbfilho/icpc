/*
A id�ia aqui � adicionar um n� extra, representando a liga��o dos outros n�s ao
aeroporto. Desse n� sai uma aresta para cada um dos outros n�s. Da� basta usar o
kruskal para selecionar as arestas da MST desse grafo modificado. Essa � s� a ideia, 
fazer isso d� TLE. Imagine o grafo modificado, veja que, para cada aresta que � inserida
pelo kruskal, uma aresta do vertice especial ( dos aeroportos ) � removida. No entanto,
uma aresta de avi�o s� deve ser removida por uma aresta do kruskal se essa aresta da MST
tiver peso maior ou igual ao custo de se construir um aeroporto. No final do kruskal, s�o
esperadas a = n - 1 arestas. Se essa quantidade n�o foi atingida, deve-se conectar o grafo
modificado utilizando {(n - 1) - a } arestas. Al�m dessas arestas que possivelmente s�o
inseridas, deve ser inserida uma aresta para conectar o vertice especial aos demais.
*/

#include <algorithm>
#include <cstdio>
using namespace std;
const int MAX_NOS = 10001;
const int MAX_ARESTAS = 100000;

int nos[ MAX_NOS ];
int m, n, PESO;

int pesoTotal;
int construidos;

class Aresta{
public:
	int a, b, peso;

	bool operator<( const Aresta& outra ) const{
		return peso < outra.peso;
	}

}arestas[ MAX_ARESTAS ];
Aresta *krusk[ MAX_NOS ];
int contK;

int find( int a ){
	if( nos[ a ] != a )
		nos[ a ] = find( nos[ a ] );

	return nos[ a ];
}

void unir( int a, int b ){
	nos[ find( a ) ] = find( b );
}

void responder(){
	pesoTotal = PESO;
	construidos = 1;

	for( int i = 0; i < contK; ++i ){
		if( (krusk[ i ] -> peso) >= PESO ){
			++construidos;
			pesoTotal += PESO;
		}else
			pesoTotal += (krusk[ i ] -> peso);
	}

	if( contK != n - 1 ){
		construidos += ( n - 1 - contK );
		pesoTotal += ( n - 1 - contK ) * PESO;
	}
}

void kruscal(){
	sort( arestas, arestas + m );
	contK = 0;

	for( int i = 0; i < m; ++i ){
		if( find( arestas[i].a ) == find( arestas[i].b ) )
			continue;

		unir( arestas[i].a, arestas[i].b );
		krusk[ contK++ ] = &arestas[ i ];

		if( contK == n - 1 )
			break;
	}

}

void carregar(){
	scanf( "%d %d %d", &n, &m, &PESO );
	
	for( int i = 0; i < m; ++i )
		scanf( "%d %d %d", &arestas[ i ].a, &arestas[ i ].b, &arestas[ i ].peso );


	for( int i = 1; i <= n; ++i )
		nos[ i ] = i;
}

int main(){
	int casos;

	freopen( "in.txt", "r", stdin );
	scanf( "%d", &casos );

	for( int i = 1; i <= casos; ++i ){
		carregar();
		kruscal();
		responder();
		printf( "Case #%d: %d %d\n", i, pesoTotal, construidos );
	}

}
