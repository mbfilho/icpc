#include <iostream>
using namespace std;

int main(){
	int amostras;
	bool anterior, atual;

	int array[ 10000 ];
	
	freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> amostras;
	while( amostras ){
	
		int temp;
		if( amostras == 2 ){
			cin >> temp >> temp;
			cout << 2 << endl;
		}else{
			for( int i = 0; i < amostras; ++i ){
				cin >> temp;
				array[ i ] = temp;
			}
			
			int cont = 0;
			for( int i = 1; i < amostras - 1; ++i ){
				if( array[ i - 1 ] > array[ i ] && array[ i ] < array[ i + 1 ] )
					++cont;
				else if( array[ i - 1 ] < array[ i ] &&  array[ i ] > array[ i + 1 ] )
					++cont;
			}
			
			if( array[ amostras - 1 ] > array[ 0 ] && array[ 0 ] < array[ 1 ] )
				++cont;
			else if( array[ amostras - 1 ] < array[ 0 ] && array[ 0 ] > array[ 1 ] )
				++cont;
			
			if( array[ amostras - 1 ] > array[ amostras - 2 ] && array[ amostras - 1 ] > array[ 0 ] )
				++cont;
			else if( array[ amostras - 1 ] < array[ amostras - 2 ] && array[ amostras - 1 ] < array[ 0 ] )
				++cont;
			
			cout << cont << endl;
		}
		cin >> amostras;
	}
}
