#include <iostream>
#include <list>
#include <queue>
using namespace std;

const int infinito = 0x0FFFFFFF;
class Nod{
	public:
		int dist, id;
	Nod(){}
	
	Nod( int id, int dist ){
		this -> id = id;
		this -> dist = dist;
	}
	
	bool operator<( const Nod& b ) const{
		return dist > b.dist;
	}
	
};

class No{
	public:
		bool marcado;
		int dist, air;		
		list<int> adj;
}nos[ 2001 ];

void dijkstra( int inicial ){
	priority_queue<Nod> heap;
	Nod aux;
	aux.dist = nos[ inicial ].air;
	aux.id = inicial;
	nos[ inicial ].dist = aux.dist;
	heap.push( aux );
	
	list<int>::iterator it, fim;
	
	while( heap.empty() == 0 ){
		aux = heap.top();
		heap.pop();
		
		if( nos[ aux.id ].marcado == false ){
			nos[ aux.id ].marcado = true;
			
			fim =  nos[ aux.id ].adj.end();
			for( it = nos[ aux.id ].adj.begin(); it != fim; ++it ){
				if( nos[ *it ].marcado == false && ( nos[ aux.id ].dist 
					+ nos[ *it ].air < nos[ *it ].dist ) ){
					
					nos[ *it ].dist = nos[ aux.id ].dist + nos[ *it ].air;
					heap.push( Nod( *it, nos[ *it ].dist ) );
				}
			}
		}
	}
}

int main(){
	int casos, citys, arestas, aeroportos;
	int temp, temp2;
	int teste;
	
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	cin >> casos;
	
	for( int cases = 1; cases <= casos; ++cases ){
		cin >> citys >> arestas >> aeroportos;
		
		for( int i = 0; i <= citys; ++i ){
			nos[ i ].air = 1;
			nos[ i ].adj.clear();
		}
		
		
		for( int i = 0; i < aeroportos; ++i ){
			cin >> temp;
			nos[ temp ].air = 0;
		}
		
		for( int i = 0; i < arestas; ++i ){
			cin >> temp >> temp2;
			nos[ temp ].adj.push_back( temp2 );
			nos[ temp2 ].adj.push_back( temp );
		}
		
		cin >> teste;
		cout << "Case " << cases << ":" << endl;
		for( int i = 0; i < teste; ++i ){
			cin >> temp >> temp2;
		
			if( temp == temp2 )
				cout << "0\n";
			else{
				for( int j = 0; j <= citys; ++j ){
					nos[ j ].marcado = false;
					nos[ j ].dist = infinito;
				}
				
				dijkstra( temp );
				if( nos[ temp2 ].dist != infinito )
					cout << nos[ temp2 ].dist << endl;
				else
					cout << "-1\n";
			}
		}
		
		cout << endl;
		
	}
}
