#include <cstdio>
#include <cstring>

int main(){
	int casos, num;
	int respostas[ 500001 ];
	memset( respostas, 0, sizeof( int ) * 500001 );
	
	for( int i = 1; i <= 250000; ++i ){
		for( int j = 2 * i; j <= 500000; j += i )
			respostas[ j ] += i; 
	}
	
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d", &num );
				
		printf( "%d\n", respostas[ num ] );
	}
}
