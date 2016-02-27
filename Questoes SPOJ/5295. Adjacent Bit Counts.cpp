#include <cstdio>
#include <cstring>

int memo[101][102][2];

int tam, sum;

int resolver( int len, int soma, int bit ){
	if( memo[len][soma][bit] != -1 )
		return memo[len][soma][bit];
		
	if( len == tam ){
		if( soma == sum )
			return memo[len][soma][bit] = 1;
		else
			return memo[len][soma][bit] = 0;
	}
		
	int temp = resolver( len + 1, soma, 0 );
	temp += resolver( len + 1, soma + bit, 1 );
	
	return memo[len][soma][bit] = temp;
}

int main(){
	int casos, set;
	
	scanf( "%d", &casos );
	
	while( casos-- ){
		scanf( "%d %d %d", &set, &tam, &sum );
		if( sum >= tam )
			printf( "%d 0\n", set );
		else{
			memset( memo, -1, sizeof( memo ) );
			printf( "%d %d\n", set, resolver( 0, 0, 0 ) );
		}
	}
}