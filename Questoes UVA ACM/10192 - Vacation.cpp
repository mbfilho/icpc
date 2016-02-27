#include <cstdio>
#include <cstring>
#define maior( a, b ) (a) > (b) ? (a) : (b)

/*
Longest Common Subsequence simples. 
*/
char s1[101], s2[101];
int matriz[102][102];
int tam1, tam2;

int lcs(){
	for( int i = 0; i <= tam1; ++i )
		matriz[i][0] = matriz[0][i] = 0;
	
	for( int i = 1; i <= tam1; ++i ){
		for( int j = 1; j <= tam2; ++j ){
			if( s1[i - 1] == s2[j - 1] )
				matriz[i][j] = matriz[i - 1][j - 1] + 1;
			else
				matriz[i][j] = maior( matriz[i - 1][j], matriz[i][j - 1] );
		}
	}
	
	return matriz[tam1][tam2];
}

int main(){
	int caso = 1;
	
	while( gets( s1 ) && s1[0] != '#' ){
		gets( s2 );
		tam1 = strlen( s1 );
		tam2 = strlen( s2 );
		printf( "Case #%d: you can visit at most %d cities.\n", caso++, lcs() );
	}
}
