#include <cstdio>
#include <algorithm>
using namespace std;

int n, m, soma;
int precos[ 1000 ];

int main(){
	
	scanf( "%d %d", &n, &m );
	
	for( int i = 0; i < n; ++i ){
		scanf( "%d", precos + i );
		if( precos[ i ] == 0 )
			++precos[ i ];
	}
	
	sort( precos, precos + n );
	int cont = 0;
	soma = 0;
	for( int i = 0; i < n && cont < m; ++i ){
		if( precos[ i ] < 0 ){
			soma += -precos[ i ];
			++cont;
		}else
			break;
	}
	
	printf( "%d\n", soma );
}
