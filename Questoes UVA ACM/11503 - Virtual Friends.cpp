#include <iostream>
#include <string>
#include <list>
#include <map>
using namespace std;

class No{
	public:
		int rep, qtd;		
}nos[ 200000 ];

int find( int no ){
	
	if( no == nos[ no ].rep )
		return no;
	
	nos[ no ].rep = find( nos[ no ].rep );
	
	return nos[ no ].rep;
}

void uniao( int conj1, int conj2 ){
	int rep2 = find( conj2 );
	int rep1 = find( conj1 );
	
	//Faz a união somente se eles não fizerem parte do mesmo conjunto
	if( rep2 != rep1 ){
		int a = nos[ rep1 ].qtd;
			
		nos[ rep1 ].rep = rep2;
		nos[ rep2 ].qtd += a;
	}
}

int main(){
	int casos, amigos, contador;
	map<string,int> mapa;
	map<string,int>::iterator it1, it2;
	string temp1, temp2;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> casos;
	while( casos-- ){
		contador = 1;
		mapa.clear();
		
		cin >> amigos;
		
		while( amigos-- ){
			cin >> temp1 >> temp2;
			
			it1 = mapa.find( temp1 );
			if( it1 == mapa.end() ){
				mapa[ temp1 ] = contador;
				nos[ contador ].qtd = 1;
				nos[ contador ].rep = contador;
				it1 = mapa.find( temp1 );
				++contador;
			}
			
			it2 = mapa.find( temp2 );
			if( it2 == mapa.end() ){
				mapa[ temp2 ] = contador;
				nos[ contador ].qtd = 1;
				nos[ contador ].rep = contador;
				it2 = mapa.find( temp2 );
				++contador;
			}
			
			uniao( it1 -> second, it2 -> second );
			
			cout << nos [ nos[ it2 -> second ].rep ].qtd << endl;
		}
		
	}
	
}
