#include <cstdio>

int main(){
	int m, n;
	
	scanf( "%d %d", &n, &m );
	
	if( n == 1 ){
		if( m == 2 ){
			printf( "0\n" );
			printf( "1 1\n" );
			printf( "1 2\n" );
			printf( "1 1\n" );
			return 0;
		}else{
			printf( "1\n" );
			printf( "1 %d 1 1\n", m );
			
			for( int i = 1; i <= m; ++i )
				printf( "1 %d\n", i );
			
			printf( "1 1\n" ); 
		}
	}else if( m == 1 ){
		if( n == 2 ){
			printf( "0\n" );
			printf( "1 1\n" );
			printf( "2 1\n" );
			printf( "1 1\n" );
			return 0;
		}else{
			printf( "1\n" );
			printf( "%d 1 1 1\n", n );
			
			for( int i = 1; i <= n; ++i )
				printf( "%d 1\n", i );
			
			printf( "1 1\n" );
		}
	}else if( n % 2 == 0 ){
		printf( "0\n" );
		
		for( int i = 1; i <= n; ++i )
			printf( "%d 1\n", i );
		
		bool direita = true;
		for( int lin = n; lin >= 1; --lin ){
			if( direita ){
				for( int j = 2; j <= m; ++j )
					printf( "%d %d\n", lin, j );
			}else{
				for( int j = m; j > 1; --j )
					printf( "%d %d\n", lin, j );
			}
			
			direita = !direita;
		}
		
		printf( "1 1\n" );
	}else if( m % 2 == 0 ){
		printf( "0\n" );
		
		for( int j = 1; j <= m; ++j )
			printf( "1 %d\n", j );
		
		bool baixo = true;
		for( int col = m; col >= 1; --col ){
			if( baixo ){
				for( int i = 2; i <= n; ++i )
					printf( "%d %d\n", i, col );
			}else{
				for( int i = n; i > 1; --i )
					printf( "%d %d\n", i, col );
			}
			
			baixo = !baixo;
		}
		
		printf( "1 1\n" );
	}else{
		printf( "1\n" );
		printf( "%d %d 1 1\n", n, m );
		
		bool direita = true;
		for( int i = 1; i <= n; ++i ){
			if( direita ){
				for( int j = 1; j <= m; ++j )
					printf( "%d %d\n", i, j );
			}else{
				for( int j = m; j >= 1; --j )
					printf( "%d %d\n", i, j );
			}
			
			direita = !direita;
		}
		printf( "1 1\n" );
	}
}
