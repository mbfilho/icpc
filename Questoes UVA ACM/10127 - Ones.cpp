#include <iostream>
using std::cout;
using std::cin;

int main(){
	unsigned int numero, pot, modulo, cont;
	
	while( cin >> numero ){
		cont = pot = 0;
		
		while( true ){
			pot = pot * 10 + 1;
			++cont;
			
			modulo = pot % numero;
			if( modulo == 0 )
				break;
			else
				pot = modulo;
		}
		
		cout << cont << std::endl;
	}
}
