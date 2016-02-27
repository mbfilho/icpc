#include <iostream>
#include <algorithm>
using namespace std;

int main(){
	int lista[ 20001 ];
	lista[ 0 ] = -1;
	int vezes, compras;
	
	cin >> vezes;
	
	while( vezes-- ){
		cin >> compras;
		
		for( int i = 1; i <= compras; ++i )
			cin >> lista[ i ];
		
		sort( lista, lista + compras + 1 );
		
		int soma = 0;
		int i;
		i =  1 + (compras % 3);
		
		for( ; i <= compras; i += 3 )
			soma += lista[ i ];
		
		cout << soma << endl;
	}
}
