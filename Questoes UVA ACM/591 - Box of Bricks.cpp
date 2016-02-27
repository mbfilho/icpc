#include <iostream>
using std::cout;
using std::cin;

int main(){
	int pilhas, alturas[ 50 ], soma, media, set = 1;
	
//	freopen( "in.txt", "r", stdin );
//	freopen( "out.txt", "w", stdout );
	
	cin >> pilhas;
	while( pilhas != 0 ){
		soma = 0;
		
		for( int k = 0; k < pilhas; ++k ){	
			cin >> alturas[ k ];
			soma += alturas[ k ];
		}
		
		media = soma / pilhas;
		soma = 0;
		while( pilhas-- ){
			if( alturas[ pilhas ] <= media )
				continue;
			soma += ( alturas[ pilhas ] - media );
		}
		
		cout << "Set #" << set << "\n";
		++set;
		cout << "The minimum number of moves is " << soma << ".\n\n";
		cin >> pilhas;
	}
	
	cout.flush();	
}
