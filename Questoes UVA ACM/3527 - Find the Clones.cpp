#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int main(){
	string dna[ 20001 ];
	int vezes[ 20001 ];
	int n, m;
	
	cin >> n >> m;
	while( n | m ){
		for( int i = 0; i <= n; ++i )
			vezes[ i ] = 0;
		
		for( int i = 0; i < n; ++i )
			cin >> dna[ i ];
		sort( dna, dna + n );
		
		int cont;
		int i = 0;
		while( i < n ){
			cont = 0;
			while( i < n - 1 &&  dna[ i ] == dna[ i + 1 ] ){
				++i;
				++cont;
			}
			++i;
			++vezes[ cont ];
		}
		
		for( int i = 0; i < n; ++i ){
			cout << vezes[ i ] << endl;
		}
		cin >> n >> m;
	}
}
