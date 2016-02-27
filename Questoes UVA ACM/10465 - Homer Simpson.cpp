#include <iostream>
#include <cstring>
using namespace std;

int qtd[ 10001 ];
int n, m, t;

int min( int x, int y ){
	if( x > y )
		return y;
	return x;
}

int max( int x, int y ){
	if( x > y )
		return x;
	return y;
}

void pd(){

	int temp1, temp2;
	for( int i = 1 + min( n, m ); i <= t; ++i ){
		if( i >= n )
			temp1 = qtd[ i - n ];
		else
			temp1 = -1;

		if( i >= m )
			temp2 = qtd[ i - m ];
		else
			temp2 = -1;

		if( temp1 == -1 && temp2 == -1 ){
			if( qtd[ i ] == -1 )
				qtd[ i ] = -1;
		}else
			qtd[ i ] = max( temp1 + 1, temp2 + 1 );
		
		
	}

}

int main(){

	while( cin >> m >> n >> t ){
		for( int i = 0; i <= t; ++i )
			qtd[ i ] = -1;

		qtd[ m ] = qtd[ n ] = 1;
		
		if( t < m && t < n )
			cout << "0 " << t << endl;
		else{
			pd();
			if( qtd[ t ] == -1 ){
				int i = t;
				while( i >= 1 && qtd[ i ] == -1 )
					--i;
				cout << qtd[ i ] << " " << ( t - i ) << endl;
			}else
				cout << qtd[ t ] << endl;
		}
	}

}

