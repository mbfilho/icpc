#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define MAX 30001

int moedas[] = { 10, 25, 50 };
long long valor[ MAX ];

void preencher(){
	for( int i = 0; i < MAX; ++i ){
		valor[ i ] = 1;
		valor[ i ] += (i / 5);
	}

	for( int i = 0; i < 3; ++i ){
		for( int j = moedas[ i ]; j < MAX; ++j )
			valor[ j ] += valor[ j - moedas[ i ] ];
	}
}

int main(){
	int val;
	
	preencher();
	
	while( scanf( "%d", &val ) != EOF ){
		if( valor[ val ] == 1 )
			printf( "There is only 1 way to produce %d cents change.\n", val );
		else
			cout << "There are " << valor[ val ] << " ways to produce " << val << " cents change." << endl;
		//	printf( "There are %I64i ways to produce %d cents change.\n", (long long) valor[ val ], val );
	}
}