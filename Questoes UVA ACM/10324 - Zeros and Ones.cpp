#include <iostream>
using std::cout;
using std::cin;

#include <string>
using std::string;

int main(){
	string buffer;
	int i, j, qtd, caso = 1;
			
	while( cin >> buffer ){
		cout << "Case " << caso << ":\n";
		++caso;
		
		int indices[ buffer.size() ];
		indices[ 0 ] = 0;
		char temp = buffer[ 0 ];
		int anterior = 0;
		for( int k = 1; k < buffer.size(); ++k ){
			if( buffer[ k ] == temp )
				indices[ k ] = anterior;
			else{
				anterior = k;
				temp = buffer[ k ];
				indices[ k ] = anterior;
			}
		}
		
		cin >> qtd;
	
		while( qtd-- ){
			cin >> i;
			cin >> j;
			
			if( indices[ i ] == indices[ j ] )
				cout << "Yes\n";
			else
				cout << "No\n";
		}
	}
}
