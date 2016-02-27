#include <cstdio>

int **m;
int **ma2;

int r, c, n, k;

void battle(){
	for( int i = 0; i < r; ++i )
		for( int j = 0; j < c; ++j )
			ma2[i][j] = m[i][j];
		
	for( int i = 0; i < r; ++i ){
		for( int j = 0; j < c; ++j ){
			if( i + 1 < r ){
				if( m[i + 1][j] == ((m[i][j] + 1) % n) )
				   ma2[i + 1][j] = m[i][j];
			}

			if( i - 1 >= 0 ){
				if( m[i - 1][j] == ((m[i][j] + 1) % n) )
				   ma2[i - 1][j] = m[i][j];
			}


			if( j + 1 < c ){
				if( m[i][j + 1] == ((m[i][j] + 1) % n) )
					ma2[i][j + 1] = m[i][j];					   
			}

			if( j - 1 >= 0 ){
				if( m[i][j - 1] == ( (m[i][j] + 1) % n ) )
				   ma2[i][j - 1] = m[i][j];
			}

		}		
	}
	
	
	for( int i = 0; i < r; ++i )
		for( int j = 0; j < c; ++j )
			m[i][j] = ma2[i][j];
	
}

int main(){
    m = new int*[100];
    ma2 = new int*[100];
    for( int i = 0; i < 100; ++i ){
         m[i] = new int[100];
         ma2[i] = new int[100];
    }
         
    int** temp;
    
    freopen( "in.txt", "r", stdin );
    freopen( "out.txt", "w", stdout );
    
    while( scanf( "%d %d %d %d", &n, &r, &c, &k ) != EOF && ( n | r | c | k ) ){
           for( int i = 0; i < r; ++i ){
                for( int j = 0; j < c; ++j )
                     scanf( "%d", &m[ i ][ j ] );
           }
           
           for( int i = 0; i < k; ++i ){

                battle();
           }
		   for( int i = 0; i < r; ++i ){
				for( int j = 0; j < c; ++j )
					 printf( "%d%c", ma2[i][j], (j == c - 1 ? '\n' : ' ' ) );
		   }

    } 
    
}
