#include <iostream>
#include <algorithm>
using namespace std;


int main(){
	int resposta[ 100001 ];
	int dados, numero;
	
	cin >> dados;
	
	for( int i = 1; i <= dados; ++i ){
		cin >> numero;
		resposta[ i ] = numero;
	}
	
	sort( resposta + 1, resposta + dados + 1 );
	
	numero = 0;
	while( numero < 3 ){
		if( cin.get() == '#' )
			++numero;
	}
	
	cin >> dados;
	while( dados-- ){
		cin >> numero;
		cout << resposta[ numero ] << endl;
	}
	
	return 0;
}



