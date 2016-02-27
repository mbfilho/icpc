#include <iostream>
#include <string>

using namespace std;

int main(){
	char matriz[ 200 ][ 200 ];

	for( int i = 0; i < 200; ++i ){
		for( int j = 0; j < 200; ++j )
			matriz[ i ][ j ] = ' ';
	}

	int tam = 0, col = 0;
	string buf;

	while( getline( cin, buf ) ){
		if( buf.size() > tam )
			tam = buf.size();

		for( int i = 0; i < buf.size(); ++i )
			matriz[ i ][ col ] = buf[ i ];
		++col;
	}

	for( int i = 0; i < tam; ++i ){
		for( int j = col - 1; j >= 0; --j )
			cout << matriz[ i ][ j ];
		cout << endl;
	}
}
