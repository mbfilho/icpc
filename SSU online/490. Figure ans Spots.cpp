#include <cstdio>

bool ma[ 20 ][ 20 ];

int main(){
	int h, w, n, casos;
	
	freopen("in.txt","r",stdin);
	freopen("out.txt","w",stdout);
	
	scanf( "%d", &casos );
	
	for( int u = 1; u <= casos; ++u ){
		scanf( "%d %d %d", &h, &w, &n );
		
		bool atual;
		int cont = 0;
		
		for( int i = 0; i < h; ++i ){
			for( int j = 0; j < w; ++j )
				ma[ i ][ j ] = false;
		}
		
		
		for( int i = 1; i < h - 1 && cont < n; ++i ){
			if( i % 2 == 1 )
				atual = true;
			else
				atual = false;
				
			for( int j = 1; j < w - 1 && cont < n; ++j ){
				ma[ i ][ j ] = atual;
				if( atual )
					++cont;
				atual = !atual;
			}
		}
		
		if( cont != n )
			printf( "Impossible\n" );
		else{
			for( int i = 0; i < h; ++i ){
				for( int j = 0; j < w; ++j ){
					if( ma[ i ][ j ] )
						printf( "#" );
					else
						printf( "." );
				}
				printf( "\n" );
			}
		}
		
		if( u != casos )
			printf( "\n" );
	}
}
