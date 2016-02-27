#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 200100
#define TREE 1000000

int nos[ TREE ];
int res[ N ];

void build( int no, int ini, int fim ){
	if( ini == fim )
		nos[ no ] = res[ ini ];
	else{
		int meio = ( ini + fim ) / 2;
		
		build( no * 2, ini, meio );
		build( no * 2 + 1, meio + 1, fim );
		nos[ no ] = nos[ 2 * no ] + nos[ 2 * no + 1 ];
	}
}

void setar( int no, int ini, int fim, int inter, int val ){
	if( ini == fim ){
		nos[ no ] = val;
		res[ inter ] = val;
	}else{
		int meio = ( ini + fim ) / 2;
		if( inter <= meio )
			setar( no * 2, ini, meio, inter, val );
		else if( inter > meio )
			setar( no * 2 + 1, meio + 1, fim, inter, val );
		nos[ no ] = nos[ no * 2 ] + nos[ no * 2 + 1 ];
	}
}

int query( int no, int ini, int fim, int a, int b ){
	if( b < ini || a > fim ) return 0;
	if( a <= ini && b >= fim )
		return nos[ no ];
	else{
		int meio = ( ini + fim ) / 2;
		int soma = query( no * 2, ini, meio, a, b );
		soma += query( no * 2 + 1, meio + 1, fim, a, b );
		return soma;
	}
}

int getInt(){
	int ret = 0;
	char ch;
	
	while( ( ch = getchar_unlocked() ) && ( ch < '0' || ch > '9' ) );
	ret = ch - '0';
	
	while( ( ch = getchar_unlocked() ) && ( ch >= '0' && ch <= '9' ) )
		ret = ret * 10 + ch - '0';
	return ret;	

}


char op[ 1000 ];
int main(){
	int n;
	int caso = 1;
	
	while( scanf( "%d", &n  ) != EOF && n ){
		if( caso != 1 ) printf( "\n" );
		printf( "Case %d:\n", caso++ );
		
		for( int i = 0; i < n; ++i )
			scanf( "%d", res + i );
		build( 1, 0, n - 1 );
		
		while( scanf( "%s", op ) != EOF && op[ 0 ] != 'E' ){
			int a= getInt(), b = getInt();
//			scanf( "%d %d", &a, &b );

			if( op[ 0 ] == 'M' )
				printf( "%d\n", query( 1, 0, n - 1, a - 1, b - 1 ) );
			else if( op[ 0 ] == 'S' )
				setar( 1, 0, n - 1, a - 1, b );	
		}
		
	}
}

