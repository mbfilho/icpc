#include <iostream>
using namespace std;

const int maxpreco = 1000001;

int main(){
	int livros, dinheiro;
	short precos[ maxpreco ];
	int temp, busca;
	int i, j;
	int i_t, j_t;
	 
	while( cin >> livros ){
		i = -1;
		for( int h = 0; h < maxpreco; ++h )
			precos[ h ] = 0;
			
		for( int t = 0; t < livros; ++t ){
			cin >> temp;
			++precos[ temp ];
		}
		
		cin >> dinheiro;
		
		busca = dinheiro;
		if( busca >= maxpreco )
			busca = maxpreco - 1;
		
		while( busca > 0 ){
			while( precos[ busca ] == 0 )
				--busca;
			
			if( busca <= 0 )
				break;
			
			if( (dinheiro - busca) < maxpreco ){
				if( 2 * busca == dinheiro ){
					if( precos[ busca ] >= 2 ){
						i = j = busca;
						break;
					}
				}else if( precos[ dinheiro - busca ] > 0 ){
					i_t = dinheiro - busca;
					j_t = busca;
					if( i_t > j_t ){
						temp = i_t;
						i_t = j_t;
						j_t = temp;
					}
					
					if( i == -1 || ( j - i ) > ( j_t - i_t ) ){
						i = i_t;
						j = j_t;
					}
				}
			}
			
			--busca;
		}
		
		cout << "Peter should buy books whose prices are " << i << " and " << j << "." << endl << endl;
	}
	
}
