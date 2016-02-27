#include <iostream>
#include <list>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

class Are{
public:
	int no, peso;
	
	Are( int u, int p ){
		no = u;
		peso = p;
	}
};

class No{
public:
	list<Are> adj;
	int dist;
	bool marcado;
}nos[ 605 ];

class noh{
public:
	int id, dist;
	
	noh(){}
	
	noh( int i, int dis ){
		id = i;
		dist = dis;
	}
	
	bool operator<( const noh& a ) const{
		return !( dist < a.dist );
	}
};

bool fire[ 600 ];
int maior_dist = 0, indice;
int casas;

void dij( int ini ){
	priority_queue<noh> heap;
	list<Are>::iterator it;
	noh temp;
	
	for( int i = 1; i <= casas; ++i ){
		nos[ i ].marcado = false;
		if( fire[ i ] ){
			nos[ i ].dist = 0;
			heap.push( noh( i, 0 ) );
		}else
			nos[ i ].dist = 0x7fffffff;	
	}
		
	int id;
	while( heap.empty() == false ){
		temp = heap.top();
		heap.pop();
		
		id = temp.id;
		if( nos[ id ].marcado )
			continue;
		nos[ id ].marcado = true;
		nos[ id ].dist = temp.dist;
		
		for( it = nos[ id ].adj.begin(); it != nos[ id ].adj.end(); ++it ){
			if( nos[ it -> no ].marcado )
				continue;
			if( nos[ it -> no ].dist > ( nos[ id ].dist + (it -> peso) ) ){
				nos[ it -> no ].dist = nos[ id ].dist + ( it -> peso );
				heap.push( noh( it -> no, nos[ it -> no ].dist ) );
			}	
		}
	}
}

int main(){
	int casos, station;
	char line[ 50000 ];
	
	cin >> casos;
	
	while( casos-- ){	
		cin >> station >> casas;
		int temp;
		for( int i = 1; i <= casas; ++i ){
			nos[ i ].adj.clear();
			fire[ i ] = false;
		}
		
		for( int i = 0; i < station; ++i ){
			cin >> temp;
			fire[ temp ] = true;
		}
		
		int u, v, peso;

		string linha;
		
		getline( cin, linha );
		
		while( getline( cin, linha ) && linha != "" ){
			istringstream ss( linha );
			ss >> u >> v >> peso;
			nos[ u ].adj.push_back( Are( v, peso ) );
			nos[ v ].adj.push_back( Are( u, peso ) );
		}
		

		maior_dist = 0x7fffffff;
		indice = 1;
		for( int i = 1; i <= casas; ++i ){
			if( fire[ i ] )
				continue;
			
			fire[ i ] = true;
			dij( i );
			fire[ i ] = false;
			
			int maior_temp = 0;
			for( int j = 1; j <= casas; ++j ){
				if( nos[ j ].dist > maior_temp )
					maior_temp = nos[ j ].dist;
			}
			
			if( maior_temp < maior_dist ){
				maior_dist = maior_temp;
				indice = i;
			}
		}
		
		cout << indice << endl;
		if( casos > 0 )
			cout << endl;
	}
	
	return 0;
}


