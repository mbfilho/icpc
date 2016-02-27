#include <iostream>
#include <cstdio>
using namespace std;

char ma[4][4];
char temp[4][4];
char texto[4][4];

int main() {
	freopen( "in.txt", "r", stdin );

	for( int i = 0; i < 4; ++i ){
		for( int j = 0; j < 4; ++j ){
			cin >> ma[ i ][ j ];
			temp[i][j] = ma[i][j];
		} 
	}
	
	for( int i = 0; i < 4; ++i ){
		for( int j = 0; j < 4; ++j ){
			cin >> texto[ i ][ j ];
		} 
	}
	
	for ( int k = 0; k < 4; ++k ){
		for( int i = 0; i < 4; ++i ){
			for( int j = 0; j < 4; ++j ){
				if( ma[ i ][ j ] == 'X' )
					cout << texto[ i ][ j ];
			} 
		}
	
		for( int i = 0; i < 4; ++i ){
			for( int j = 3; j >= 0; --j ){
				temp[i][3 - j] = ma[j][i];
			}
		}
		
		for( int i = 0; i < 4; ++i ){
			for( int j = 3; j >= 0; --j ){
				ma[i][j] = temp[i][j];
			}
		}
			
	}
	
	cout << endl;
	
}

