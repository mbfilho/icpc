#include <iostream>
using namespace std;

int moedas[ 22 ];
long long pd[ 10000 ];

void proc(){
	
	for( int i = 0; i < 10000; ++i )
		pd[ i ] = 0;
		
	pd[ 0 ] = 1;
	for( int i = 1; i <= 21; ++i )
		moedas[ i ] = i * i * i;
	
	
	for( int j = 1; j <= 21; ++j ){	
		for( int i = 0; i < 10000; ++i ){
			if( i - moedas[ j ] >= 0 )
				pd[ i ] += pd[ i - moedas[ j ] ];
		}
	}
}

int main(){
	int qtd;
	
	proc();
	
	while( cin >> qtd )
		cout << pd[ qtd ] << endl;
}
