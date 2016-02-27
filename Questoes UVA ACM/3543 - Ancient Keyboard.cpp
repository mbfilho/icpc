#include <iostream>
using namespace std;

int tempo[ 1050 ];

int main(){
		
	int casos, sub, a, b;
	char buff;
	cin >> casos;
	
	while( casos-- ){
		cin >> sub;
		
	for( int i = 0; i <= 1050; ++i )
		tempo[ i ] = 0;
		
		while( sub-- ){
			cin >> buff >> a >> b;
			
			for( int i = a; i < b; ++i )
				++tempo[ i ];
		}
		
		char base = 'A';
		for( int i = 0; i <= 1000; ++i ){
			if( tempo[ i ] != 0 )
				cout << (char)( base + tempo[ i ] - 1 );
		}

		cout << endl;
	}
}

