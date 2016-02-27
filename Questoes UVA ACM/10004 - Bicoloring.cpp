#include <iostream>
#include <list>
using namespace std;

const int A = 2, B = -2, IND = -1;
class No{
	public:
		list<int> adj;
		bool marcado;
		int cor;
		int id;
		
		No(){
			marcado = false;
		}
};


int main(){
	bool retorno;
	list<int>::iterator it;
	int pilha[ 200 ];
	int sp;
	
	int n, arestas, temp1, temp2;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> n;
	while( n ){
		No nos[ 200 ];
		cin >> arestas;

		while( arestas-- ){
			cin >> temp1 >> temp2;
			nos[ temp1 ].adj.push_back( temp2 );
			nos[ temp2 ].adj.push_back( temp1 );
			nos[ temp1 ].id = temp1;
			nos[ temp2 ].id = temp2;
		}		
		
		pilha[ 0 ] = 0;
		nos[ 0 ].cor = A;
		nos[ 0 ].marcado = true;
		sp = 1;
		retorno = false;

		while( sp != 0 && retorno == false ){
			No& temp = nos[ pilha[ --sp ] ];
			for( it = temp.adj.begin(); it != temp.adj.end(); it++ ){
				if( nos[ *it ].marcado == false ){
					nos[ *it ].cor = -temp.cor;
					
					pilha[ sp++ ] = *it;
					nos[ *it ].marcado = true;
				}else if( nos[ *it ].cor == temp.cor  ){
					retorno = true;
					break;
				}
			}
		}
		
		if( retorno )
			cout << "NOT BICOLORABLE." << endl;
		else
			cout << "BICOLORABLE." << endl;
			
		cin >> n;
	
	}
	
	
}
