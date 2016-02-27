#include <string>
#include <sstream>
#include <iostream>
#define LIM_SIZE 10
using namespace std;

typedef long long ll;
ll MAX = 0x7FFFFFFF;

ll soma[ 200 ][ 200 ];
string seq;

ll resolver( int i, int j ){
	if( i > j )
		return 0;
			
	if( soma[ i ][ j ] != -1 )
		return soma[ i ][ j ];
	if( j - i + 1 <= 10 ){
		istringstream in( seq.substr( i, j - i + 1 ) );
		ll numero;
		in >> numero;
		if( numero <= MAX )
			return soma[ i ][ j ] = numero;
	}
		
	ll sum = 0, temp;
	for( int size = 0; size < (j - i) && size <= 10; ++size ){
		temp = resolver( i, i + size ) + resolver( i + size + 1, j );
		if( temp > sum )
			sum = temp;
	}
	
	return soma[ i ][ j ] = sum;
}

int main(){
	int casos, qtd;
	
	cin >> casos;
	while( casos-- ){
		cin >> seq;
		qtd = seq.size();

		for( int i = 0; i < qtd; ++i ){
			for( int j = 0; j < qtd; ++j )
				soma[ i ][ j ] = -1;
		}
		cout << resolver( 0, seq.size() - 1 ) << endl;
	}	
}
