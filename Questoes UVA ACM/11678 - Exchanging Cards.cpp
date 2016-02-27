#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

int main(){
	bool alice[ 100001 ], bet[ 100001 ];
	int qtd_a, qtd_b;
	
	cin >> qtd_a >> qtd_b;
	

	while( qtd_a | qtd_b ){
		memset( alice, 0, 100001 );
		memset( bet, 0, 100001 );
		
		int temp;
		int repa = 0, repb = 0;
		for( int i = 1; i <= qtd_a; ++i ){
			cin >> temp;
			if(	alice[ temp ] )
				++repa;
			else
				alice[ temp ] = true;
		}
		
		for( int i = 1; i <= qtd_b; ++i ){
			cin >> temp;
			if( bet[ temp ] )
				++repb;
			else
				bet[ temp ] = true;
		}
		
		int cont = 0;
		for( int i = 1; i < 100001; ++i ){
			if( alice[ i ] && bet[ i ] )
				++cont;
		}
		int menor;
		if( qtd_a - repa < qtd_b - repb )
			menor = qtd_a - repa;
		else
			menor = qtd_b - repb;
		cout << ( menor - cont ) << endl;
		cin >> qtd_a >> qtd_b;
	}
}
