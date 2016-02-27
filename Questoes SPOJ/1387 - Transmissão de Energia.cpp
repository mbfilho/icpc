#include <iostream>
#include <list>
using namespace std;

int vertices;

class No{
	public:
		bool marcado;
		list<int> adj;
	No(){
		marcado = false;
	}
};

bool busca( No* nos ){
	int pilha[ 1000 ];
	int sp = 1;
	
	pilha[ 0 ] = 1;
	nos[ 1 ].marcado = true;
	No* aux;
	list<int>::iterator it;
	while( sp ){
		aux = &nos[ pilha[ --sp ] ];
		
		for( it = aux -> adj.begin(); it != aux -> adj.end(); ++it ){
			if( nos[ *it ].marcado == false ){
				nos[ *it ].marcado = true;
				pilha[ sp++ ] = *it;		
			}
		}
	}
	
	for( int i = 1; i <= vertices; ++i ){
		if( nos[ i ].marcado == false )
			return false;
	}
	
	return true;
}

int main(){
	int teste = 1;
	int arestas;
	int a1, a2;
	
	cin >> vertices >> arestas;
	
	while( vertices | arestas ){
		No nos[ 1000 ];
		
		for( int i = 0; i < arestas; ++i ){
			cin >> a1 >> a2;
			nos[ a1 ].adj.push_back( a2 );
			nos[ a2 ].adj.push_back( a1 );
		}
		
		cout << "Teste " << teste++ << endl;
		if( busca( nos ) )
			cout << "normal\n";
		else
			cout << "falha\n";
		cout << endl;
		
		cin >> vertices >> arestas;
	}
}