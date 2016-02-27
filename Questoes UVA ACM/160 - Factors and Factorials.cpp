#include <iostream>
#include <iomanip>
using namespace std;

int main(){
	int primos[ 100 ];
	int cont_p = 1;
	primos[ 1 ] = 2;

	int resposta[ 101 ][ 101 ];
	resposta[ 2 ][ 0 ] = 1;
	resposta[ 2 ][ 1 ] = 1;

	int div, pa, cont;
	bool primo;
	for( int i = 3; i < 101; ++i ){
		div = i;
		pa = 1;
		cont = 0;
		primo = true;

		while( div != 1 ){
			if( pa > cont_p && primo ){
				++cont_p;
				primos[ cont_p ] = i;
				resposta[ i ][ 0 ] = pa;
				resposta[ i ][ pa ] = 1;
				for( int j = 1; j <= resposta[ i - 1 ][ 0 ]; ++j )
					resposta[ i ][ j ] = resposta[ i - 1 ][ j ];
				break;
			}else{

				while( div % primos[ pa ] == 0 ){
					div /= primos[ pa ];
					++cont;
					primo = false;
				}

				resposta[ i ][ pa ] = cont;
				cont = 0;
				++pa;
			}
		}

		if( primo == false ){
			--pa;
			if( resposta[ i - 1 ][ 0 ] > pa ){
				resposta[ i ][ 0 ] = resposta[ i - 1 ][ 0 ];

				int j;
				for( j = 1; j <= pa; ++j )
					resposta[ i ][ j ] += resposta[ i - 1 ][ j ];
				for( ; j <= resposta[ i - 1 ][ 0 ]; ++j )
					resposta[ i ][ j ] = resposta[ i - 1 ][ j ];
			}else{
				resposta[ i ][ 0 ] = pa;

				int j;
				for( j = 1; j <= resposta[ i - 1 ][ 0 ]; ++j )
					resposta[ i ][ j ] += resposta[ i - 1 ][ j ];
			}

		}
	}

	int n;
	cin >> n;
	while( n != 0 ){
		cout.width( 3 );
		cout.setf( ios::right, ios::adjustfield );
		cout << n << "! =";

		cont = 0;
		for( int i = 1; i <= resposta[ n ][ 0 ]; ++i ){
			if( cont == 15 ){
				cout << "\n";
				cont = 0;
				cout.width( 9 );
			}else
				cout.width( 3 );

			cout << resposta[ n ][ i ];
			++cont;
		}
		cout << "\n";

		cin >> n;
	}
}
