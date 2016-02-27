#include <iostream>
using namespace std;

int sequencia[ 20000 ];
int tamanho;

void gerarSequencia( int n ){
	tamanho = 2;
	int a1, a2, atual;
	
	a1 = 0;
	a2 = 1;
	atual = 1;
	
	while( a2 != 1 || atual != 0 ){
		sequencia[ tamanho++ ] = atual;
		a1 = a2;
		a2 = atual;
		atual = ( a1 + a2 ) % n;
	}
}

int expo( unsigned long long base, unsigned long long exp ){
	int retorno = 1;
	base = base % tamanho;
	
	while( exp ){
		if( exp & 1 )
			retorno = ( ( retorno * base ) % tamanho );
		base = ( base * base ) % tamanho;
		
		exp = ( exp >> 1 );
	}
	
	return retorno;
}


int main(){
	int casos;
	unsigned long long base, exp;
	int mod;

	sequencia[ 0 ] = 0;
	sequencia[ 1 ] = 1;
	
	cin >> casos;

	while( casos-- ){
		cin >> base >> exp >> mod;
		if( mod == 1 )
			cout << "0\n";
		else{
			gerarSequencia( mod );
			cout << sequencia[ expo( base, exp ) ] << endl;
		}
	}
}
