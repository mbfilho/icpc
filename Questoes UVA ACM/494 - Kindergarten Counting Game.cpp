#include <iostream>
#include <string>
using namespace std;

int main(){
	string linha;
	int i, cont;
	
	while( getline( cin, linha ) ){
		i = 0;
		cont = 0;
		
		while( i < linha.size() ){
			while( i < linha.size() && !( (linha[ i ] >= 65 && linha[ i ] <= 90) || (linha[ i ] >= 97 && linha[ i ] <= 122 ) ) )
				++i;
			if( i < linha.size() )
				++cont;
			while( i < linha.size() && ( (linha[ i ] >= 65 && linha[ i ] <= 90) || (linha[ i ] >= 97 && linha[ i ] <= 122 ) ) )
				++i;
		}
		
		cout << cont << endl;
	}
}
