#include <iostream>
using namespace std;

int main(){
	int n;
	char pri[ 5 ], sec[ 5 ], ter[ 5 ], quar[ 5 ];
	int impares[ 8 ], pares[ 8 ];
		
	cin >> n;
	
	while( n-- ){
		cin >> pri >> sec >> ter >> quar;
		
		impares[ 0 ] = 2 *( pri[ 0 ] - '0' );
		impares[ 1 ] = 2 * ( pri[ 2 ] - '0' );
		impares[ 2 ] = 2 * ( sec[ 0 ] - '0' );
		impares[ 3 ] = 2 * ( sec[ 2 ] - '0' );
		impares[ 4 ] = 2 * ( ter[ 0 ] - '0' );
		impares[ 5 ] = 2 * ( ter[ 2 ] - '0' );
		impares[ 6 ] = 2 * ( quar[ 0 ] - '0' );
		impares[ 7 ] = 2 * ( quar[ 2 ] - '0' );
		
		pares[ 0 ] = ( pri[ 1 ] - '0' );
		pares[ 1 ] = ( pri[ 3 ] - '0' );
		pares[ 2 ] = ( sec[ 1 ] - '0' );
		pares[ 3 ] = ( sec[ 3 ] - '0' );
		pares[ 4 ] = ( ter[ 1 ] - '0' );
		pares[ 5 ] = ( ter[ 3 ] - '0' );
		pares[ 6 ] = ( quar[ 1 ] - '0' );
		pares[ 7 ] = ( quar[ 3 ] - '0' );
		
		int soma = 0;
		for( int i = 0; i < 8; ++i ){
			if( impares[ i ] >= 10 ){
				soma += 1;
				soma += ( impares[ i ] - 10 );
			}else
				soma += impares[ i ];
				
			soma += pares[ i ];
		}
		
		if( soma % 10 == 0 )
			cout << "Valid" << endl;
		else
			cout << "Invalid" << endl;
		
	}
	
}
