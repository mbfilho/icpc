#include <cstdio>
#include <cstring>

int caminho[20000][20000];
int n, tracks;
int knap[20001], cd[20];

int resolver(){
	memset( knap, 0, (n + 1) * sizeof(int) );
	
	for( int i = 0; i < tracks; ++i ){
		for( int j = n; j >= 0; --j ){
			if( j - cd[i] < 0 || knap[j] > knap[j - cd[i]] + cd[i] ){
				caminho[i][j] = j;
			}else{
				knap[j] = knap[j - cd[i]] + cd[i];
				caminho[i][j] = j - cd[i];
			}
		}
	}
	
	return knap[n];
}

void print( int i, int j ){
	if( i < 0 || j < 0 )
		return;
		
	print( i - 1, caminho[i][j] );
	if( caminho[i][j] != j )
		printf( "%d ", cd[i] );
	
}


int main(){
		
	while( scanf( "%d %d", &n, &tracks ) != EOF ){
		for( int i = 0; i < tracks; ++i )
			scanf( "%d", cd + i );

		resolver();
		print( tracks - 1, n );
		printf( "sum:%d\n", knap[n] );
		
	}
}
