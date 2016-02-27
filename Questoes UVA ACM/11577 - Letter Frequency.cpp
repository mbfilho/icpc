#include <iostream>
using namespace std;

class No{
	public:
		char letra;
		int frequencia;
		
	bool operator<( const No& outro ) const{
		if( outro.frequencia != frequencia ){
			if( outro.frequencia < frequencia )
				return true;
		}else{
			if( outro.letra > letra )
				return true;
		}
		return false;
	}
	
} frequencias[ 26 ];

int main(){
//A = 65 a = 97
	string buffer;
	int casos;
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	cin >> casos;
	
	while( casos-- ){
		for( int i = 0; i < 26; ++i ){
			frequencias[ i ].letra = (char) i + 65;
			frequencias[ i ].frequencia = 0;
		}
		
		while( cin.peek() == '\n' )
			cin.ignore();
			
		getline( cin, buffer );
		
		for( int i = 0; i < buffer.size(); ++i ){
			if( buffer[ i ] >= 65 && buffer[ i ] <= 91 ){
				++frequencias[ buffer[ i ] - 65 ].frequencia;
			}else if( buffer[ i ] >= 97 && buffer[ i ] <= 123 )
				++frequencias[ buffer[ i ] - 97 ].frequencia;
		}
		
		sort( frequencias, 26 + frequencias );
		int cont = frequencias[ 0 ].frequencia;
		int i = 0;

		while( i < 26 && frequencias[ i ].frequencia == cont ){
			cout << (char)( frequencias[ i ].letra + 32 );
			++i;
		}
		
		cout << endl;
	}
	
	
	
	

}
