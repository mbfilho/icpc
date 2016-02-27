#include <iostream>
using namespace std;

int main(){
	int jogos, times, pontos;
	char nome[ 100 ];
	cin >> times >> jogos;
	
	int soma;
	while( times | jogos ){
		soma = 0;
		for( int i = 0; i < times; ++i ){
			cin >> nome >> pontos;
			soma += pontos;
		}
		
		if( soma == jogos * 3 )
			cout << "0\n";
		else
			cout << ( jogos * 3 - soma ) << endl;
		cin >> times >> jogos;
	}
}
