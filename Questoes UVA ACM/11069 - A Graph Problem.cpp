#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

ll n, pd[ 80 ];

ll rec( int s ){
	if( s >= n ) return 1;
	if( pd[ s ] != -1 ) return pd[ s ];
	
	return pd[ s ] = ( rec( s + 2 ) + rec( s + 3 ) );
}

int main(){
	
	while( scanf( "%d", &n ) != EOF ){
		if( n == 1 )
			printf( "1\n" );
		else{
			for( int i = 0; i < 80; ++i ) pd[ i ] = -1;
			cout << rec( 1 ) << endl;
		}
	}
}
