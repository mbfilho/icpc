#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Ticket{
public:
	string h;
	char a;
	
	bool operator<( const Ticket& a ) const{
		return h < a.h;
	}
	
}array[ 65000 ];

int qtd, qE;

int main(){

    freopen( "in.txt", "r", stdin );
    freopen( "out.txt", "w", stdout );
	
	while( cin >> qtd && qtd ){
		qE = 0;
		
		for( int i = 0; i < qtd; ++i ){
			cin >> array[i].h >> array[i].a;
			if( array[i].a == 'E' )
				++qE;
		}
		
		qE = qtd / 2 - qE;
		
		sort( array, array + qtd );
		
		int dentro = 0, maior = -1;
		for( int i = 0; i < qtd; ++i ){
			if( array[i].a == 'E' )
				++dentro;
			else if( array[i].a == 'X' )
				--dentro;
			else{
				if( qE > 0 ){
					++dentro;
					--qE;
				}else
					--dentro;
			}			
			
			if( dentro > maior )
				maior = dentro;
		}
		
		cout << maior << endl;
		
	}
}
