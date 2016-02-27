#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int ma[ 9 ][ 9 ], cont;
bool achou;

int lin[ 81 ], col[ 81 ];

void rec( int ind ){
	if( ind == cont )
		achou = true;
		
	if( achou ) return;
	
	int c = 3 * ( col[ ind ] / 3 ), l = 3 * ( lin[ ind ] / 3 );
	for( int num = 1; !achou && num <= 9; ++num ){
		bool dm = false;
		
		for( int i = 0; !dm && i < 3; ++i ){
			for( int j = 0; !dm && j < 3; ++j ){
				if( ma[ l + i ][ c + j ] == num )
					dm = true;
			}
		}
		for( int i = 0; !dm && i < 9; ++i ){
			if( ma[ i ][ col[ind] ] == num ) dm = true;
			if( ma[ lin[ind] ][ i ] == num ) dm = true;
		}
		
		if( !dm ){
			ma[ lin[ind] ][ col[ind] ] = num;
			rec( ind + 1 );
			if( !achou ) ma[ lin[ind] ][ col[ind] ] = 0;
		}
	}
}

int main(){
	int casos;
	scanf( "%d", &casos );
	char linha[ 10 ];
	
	while( casos-- ){
		cont = 0;
		achou = false;
		for( int i = 0; i < 9; ++i ){
			scanf( "%s", linha );
			for( int j = 0; j < 9; ++j ){
				ma[ i ][ j ] = linha[ j ] - '0';
				if( ma[ i ][ j ] == 0 ){
					lin[ cont ] = i;
					col[ cont++ ] = j;
				}
			}
		}

		rec( 0 );
		for( int i = 0; i < 9; ++i ){
			for( int j = 0; j < 9; ++j )
				printf( "%d", ma[ i ][ j ] );
			printf( "\n" );
		}
	}
}






