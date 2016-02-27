#include <iostream>
#include <list>
using namespace std;

int pilha[ 301 ];
class No{
	public:
		list<int> adj;
		int cor;	
	
}nos[ 301 ];

bool busca(){
	int sp = 0, temp;
	list<int>::iterator it;
	pilha[ sp++ ] = 1;
	nos[ 1 ].cor = 1;
	for( int i = 2; i < 301; ++i )
		nos[ i ].cor = 0;
	
	while( sp ){
		temp = pilha[ --sp ];
		
		for( it = nos[ temp ].adj.begin(); it != nos[ temp ].adj.end(); ++it ){
			if(	nos[ *it ].cor == nos[ temp ].cor )
				return false;
			else if( nos[ *it ].cor == 0 ){
				pilha[ sp++ ] = *it;
				nos[ *it ].cor = -nos[ temp ].cor;
			}
		}
	}
	
	return true;
}

int main(){
	int vert, ar1, ar2;
	
	freopen( "in.txt", "r", stdin );
	
	cin >> vert;
	while( vert ){
		if( vert % 2 == 0 ){
			for( int i = 1; i < 301; ++i )
				nos[ i ].adj.clear();
					
			cin >> ar1 >> ar2;
			
			while( ar1 | ar2 ){
				nos[ ar1 ].adj.push_back( ar2 );
				nos[ ar2 ].adj.push_back( ar1 );
				cin >> ar1 >> ar2;
			}
		
			if( busca() )
				cout << "YES\n";
			else
				cout << "NO\n";
		}else
			cout << "NO\n";
		
		
		cin >> vert;
	}
	
}
