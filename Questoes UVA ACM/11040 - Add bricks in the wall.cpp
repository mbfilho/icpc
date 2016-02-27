#include <cstdio>
#include <iostream>
using namespace std;

int main(){
	int wall[ 10 ][ 46 ];
	int x, casos;
	
		freopen( "in.txt", "r", stdin );
	freopen( "out.txt", "w", stdout );
	
	cin >> casos;
	
	while( casos-- ){
		for( int i = 1; i <= 9; i += 2 ){
			for( int j = 1; j <= i; j += 2 )
				cin >> wall[ i ][ j ];
		}
		

		
		for( int i = 7; i >= 1; i -= 2 ){
			for( int j = 1; j <= i; j += 2 ){
				x = (wall[ i ][ j ] - wall[ i + 2 ][ j ] - wall[ i + 2 ][ j + 2 ]) / 2;
				wall[ i + 2 ][ j + 1 ] = x;
				wall[ i + 1 ][ j ] = wall[ i + 2 ][ j ] + x;
				wall[ i + 1 ][ j + 1 ] = wall[ i + 2 ][ j + 2 ] + x;
			}
		}
		
		for( int i = 1; i <= 9; ++i ){
			for( int j = 1; j <= i; ++j ){
				cout << wall[ i ][ j ];
				if( j != i )
					cout << " ";
			}
			cout << endl;
		}
		
	}
	
}


