#include <iostream>
#include <vector>
#include <utility>
using namespace std;

pair<int,int> arestas[1001];
int contA;

int conj[1001];

int find( int a ){
	if( conj[a] != a )
		conj[a] = find( conj[a] );
	return conj[a];
}

void unir( int a, int b ){
	conj[find( a )] = find( b );
}

int main(){
	int cid;
	contA = 0;
	
	cin >> cid;
	for( int i = 1; i <= cid; ++i )
		conj[i] = i;
	
	int u, v;
	for( int i = 1; i <= cid; ++i ){
		cin >> u >> v;
		
		if( find(u) != find(v) )
			unir( u, v );
		else{
			arestas[contA].first = u;
			arestas[contA].second = v;
			++contA;
		}
	}
	
	if( contA == 1 )
		cout << "0" << endl;
	else{
		cout << (contA - 1) << endl;
		
		for( int i = 0; i < contA; ++i ){
			u = arestas[i].first;
			v = arestas[i].second;
			
			for( int j = 1; j <= cid; ++j ){
				if( find( j ) != find( u ) ){
					cout << u << " " << v << " " << u << " " << find( j ) << endl;
					unir( j, u );
					break;
				}
			}
		}
	
	}

}

