#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <vector>
using namespace std;

int mod;
int dividir( int a, int b ){
	if( a == b ){
		mod = 0;
		return 1;
	}
	
	if( a >= 0 ){
		mod = ( a % (-b) );
		return -( a / (-b) );
	}
	
	int retorno = ( a / b );
	if( retorno * b == a ){
		mod = 0;
		return retorno;
	}
		
	++retorno;
	mod = ( retorno * (-b) + a );
	
	return retorno;	
}

int main(){
	string buffer, num;
	int origem;
	int base;
	char b;
	bool from;
	
	freopen( "in.txt", "r", stdin );
	//freopen( "out.txt", "w", stdout );
	
	cin >> buffer;
	
	while( buffer != "end" ){
		istringstream in( buffer );
		if( buffer[ 0 ] == 't' ){
			in >> b >> b;
			in >> base;
			from = false;
			cin >> origem;
		}else{
			 in >> b >> b >> b >> b;
			 in >> base;
			 from = true;
			cin >> num;
		}
		
		
		if( from ){
			int convertido = 0;
			int mult = 1;
			
			for( int i = num.size() - 1; i >= 0 ; --i ){
				convertido += ( ( num[ i ] - '0' ) * mult );
				mult = mult * base;
			}
			
			cout << convertido << endl;
		}else{
			vector<int> resul;
			int resto;
			resul.push_back( 0 );
			
			int temp;
			
			while( origem ){
				temp = origem;
				origem = dividir( origem , base );					
				resto = mod;
			//	cout << "Original: " << temp << " Dividido: " << origem << " REsto: " << resto <<  endl;
				resul.push_back( resto );
			}
			
			
			if( resul.size() == 1 )
				cout << "0\n";
			else{
				int i = resul.size() - 1;
				
				while( resul[ i ] == 0 )
					--i;
				
				while( i >= 1 )
					cout << resul[ i-- ];
				cout << endl;
			}
			
			
		}
		
		
		cin >> buffer;
	}
	
	
}
