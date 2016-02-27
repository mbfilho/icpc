#include <iostream>
#include <cstring>
using namespace std;

void apagar( bool* array ){
	for( int i = 0; i < 26; ++i )
		array[ i ] = false;
}

int main(){
	bool *atual, *aux, *temp;
	atual = new bool[ 26 ];
	aux = new bool[ 26 ];
	temp = new bool[ 26 ];
	
	int cont, casos, bases, cuts;
	string b;
		
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> casos;
	while( casos-- ){
		apagar( atual );
		
		cont = cuts = 0;
		
		cin >> bases;		
		cin >> b;
		
		if( bases == 1 )
			cout << "0\n";
		else{
			--bases;
			for( int i = 0; i < b.size(); ++i )
				atual[ b[ i ] - 97 ] = true;
			
			while( bases-- ){
				cin >> b;
				apagar( aux );
				apagar( temp );
				cont = 0;
				
				for( int i = 0; i < b.size(); ++i )
					aux[ b[ i ] - 97 ] = true;
				
				for( int i = 0; i < 26; ++i ){
					temp[ i ] = aux[ i ] && atual[ i ];
					cont += temp[ i ];
				}
				
				if( cont == 0 ){
					++cuts;
					bool *t = aux;
					aux = atual;
					atual = t;
				}else{
					bool *t = temp;
					temp = atual;
					atual = t;
				}
			}
			cout << cuts << endl;
		}
		
	}
	
}
