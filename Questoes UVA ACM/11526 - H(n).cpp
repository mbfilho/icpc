#include <iostream>
#include <cmath>
using namespace std;

int main(){
	int casos, numero, raiz;
	long long soma;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> casos;
	
	while( casos-- ){
		soma = 0;
		
		cin >> numero;
		
		if( numero <= 0 )
			soma = 0;
		else{
			raiz = int( sqrt( numero ) );
			for( int i = 1; i < raiz; ++i )
				soma += numero / i;
				
			int vezes, anterior = raiz;
			for( int i = ( numero / anterior - 1 ); i >= 1; --i ){
				vezes = numero / i - anterior;
				anterior = numero / i;
				soma += ( vezes * i );
			}
			
			soma += ( numero / raiz );
		}
		
		cout << soma << endl;
		
	}
	
}
