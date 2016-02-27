#include <cstdio>
#include <cstring>


int main(){
	int n;
	scanf( "%d", &n );
	char buf[ 5 ] = "abcd";
	
	for( int i = 0; i < n / 4; ++i )
		printf( "%s", buf );
	
	buf[ n % 4 ] = 0;
	printf( "%s\n", buf );
	
}

