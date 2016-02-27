#include <cstdio>

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		int n, ums = 0, outros = 0;
		scanf( "%d", &n );
		
		for( int i = 0; i < n; ++i ){
			int temp;
			scanf( "%d", &temp );
			if( temp == 1 )
				++ums;
			else
				++outros;
		}
		
		if( ums % 2 == 0 && outros == 0 )
			printf( "piloop\n" );
		else
			printf( "poopi\n" );
	}
}

