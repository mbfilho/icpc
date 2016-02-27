#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;



int main(){
	int s, d;
	int meses[ 12 ];
	
	while( scanf( "%d %d", &s, &d ) != EOF ){
		int lucro = 4 * s, prej = d;
		for( int i = 0; i < 4; ++i ){
			meses[ i ] = s;
		}
		meses[ 4 ] = -d;
		int id = 3;
		
		while( prej <= lucro ){
			meses[ id ] = -d;
			prej += d;
			lucro -= s;
			--id;
		}
		
		for( int i = 5; i < 12; ++i ){
			lucro = 0;
			for( int j = i - 4; j < i; ++j )
				lucro += meses[ j ];
			if( lucro + s < 0 )
				meses[ i ] = s;
			else
				meses[ i ] = -d;
		}
		
		int soma = 0;
		for( int i = 0; i < 12; ++i ){
			soma += meses[ i ];
		}
		
		if( soma < 0 )
			printf( "Deficit\n" );
		else
			printf( "%d\n", soma );
	}
}




