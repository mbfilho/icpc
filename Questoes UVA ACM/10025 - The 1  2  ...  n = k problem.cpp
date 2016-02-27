#include <iostream>
#include <cmath>
using namespace std;

int main(){
	long long soma, k;
	int n, vezes;

	cin >> vezes;

	while( vezes-- ){
		cin >> k;
		if( k != 0 ){
			k = abs( k );
			n = (static_cast<long long> ( sqrt( 1 + 8 * k ) ) - 1) / 2;

			if( n * ( n + 1 ) / 2 != k ){

				do{
					++n;
				}while(  ((n * ( n + 1 ) / 2) - k) % 2 != 0 );
			}
		}else
			n = 3;

		cout << n << endl;
		if( vezes )
			cout << endl;
	}
}
