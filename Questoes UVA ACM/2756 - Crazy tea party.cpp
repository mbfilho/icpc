#include <iostream>
using namespace std;

int main(){
	int casos, respostas[ 32768 ];
	
	//Preprocesso
	respostas[ 1 ] = respostas[ 2 ] = 0;
	respostas[ 3 ] = 1;
	respostas[ 4 ] = 2;
	
	int cont = 2;
	bool troca = false;
	for( int i = 4; i <= 32766; i += 2 ){
		respostas[ i + 1 ] = respostas[ i ] + cont;
		respostas[ i + 2 ] = respostas[ i + 1 ] + cont;
        ++cont;		
	}
	
	cin >> casos;
	int temp;
	while( casos-- ){
		cin >> temp;
		cout << respostas[ temp ] << "\n";
	}
}
