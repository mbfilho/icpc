#include <iostream>
using namespace std;

int main(){
	int dias, din, valor;
	
	cin >> dias;
	while( dias ){
		int i = 1;
		din = 0;
		valor = 1;
		while( i <= dias ){
			for( int k = 1; k <= valor && i <= dias; ++k ){
				din += valor;
				++i;
			}
			++valor;
		}
		
		cout << dias << " " << din << endl;
		cin >> dias;
	}
}
