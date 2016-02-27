#include <iostream>
using namespace std;

#define max( x, y ) (x) > (y)? (x) : (y)

int matriz[ 101 ][ 101 ];
int torre1[ 101 ], torre2[ 101 ];
int n1, n2;

int lcs(){
	int lado1, lado2, diago;
	
	for( int i = 1; i <= n1; ++i ){
		for( int j = 1; j <= n2; ++j ){
			lado1 = matriz[ i - 1 ][ j ];
			lado2 = matriz[ i ][ j - 1 ];
			diago = matriz[ i - 1 ][ j - 1 ];
			if( torre1[ i ] == torre2[ j ] )
				++diago;
			lado1 = max( lado1, lado2 );
			matriz[ i ][ j ] = max( lado1, diago );
		}
	}
	
	return matriz[ n1 ][ n2 ];
}

int main(){

	int cont = 1;
	for( int i = 0; i < 101; ++i ){
		matriz[ i ][ 0 ] = 0;
		matriz[ 0 ][ i ] = 0;
	}
	
	freopen( "in.txt", "r", stdin );
	cin >> n1 >> n2;
	
	while( n1 | n2 ){
		for( int i = 1; i <= n1; ++i )
			cin >> torre1[ i ];
		for( int i = 1; i <= n2; ++i )
			cin >> torre2[ i ];
		
		cout << "Twin Towers #" << cont++ << endl;
		cout << "Number of Tiles : " << lcs() << endl << endl;
		cin >> n1 >> n2;
	}
	
}