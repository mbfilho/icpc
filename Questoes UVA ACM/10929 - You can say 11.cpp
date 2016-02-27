#include <iostream>
#include <string>
using namespace std;


int main(){
	string buffer;
	int soma;
	bool sub;
	
	cin >> buffer;
	
	while( buffer != "0" ){
		sub = false;
		soma = 0;
		for( int i = 0; i < buffer.length(); ++i ){
			if( sub )
				soma -= ( buffer[ i ] - '0' );
			else
				soma += ( buffer[ i ] - '0' );
			sub = !sub;
		}
		
		if( soma % 11 == 0 )
			cout << buffer << " is a multiple of 11." << endl;
		else
			cout << buffer << " is not a multiple of 11." << endl;
			
		cin >> buffer;
	}
}

