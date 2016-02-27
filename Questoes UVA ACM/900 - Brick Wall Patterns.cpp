#include <iostream>
using namespace std;

int main(){
	int fibo[ 51 ];
	fibo[ 1 ] = 1;
	fibo[ 2 ] = 2;
	int n;
	
	for( int i = 3; i <= 51; ++i )
		fibo[ i ] = fibo [ i - 1 ] + fibo[ i - 2 ];
	
	cin >> n;
	
	while( n ){
		cout << fibo[ n ] << endl;
		cin >> n;
	}
	
	
}
