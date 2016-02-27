#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;




vector<int> grupos[ 10100 ];
int tam[ 10100 ];

int n;

int bs( int t ){
	int dif = 0;
	
	for( int i = 0; i < n; ++i ){
		int ini = 0, fim = tam[ i ] - 1, soma = 0, meio;
		
		while( ini <= fim ){
			meio = ( ini + fim ) / 2;
			if( grupos[ i ][ meio ] >= t ){
				soma = meio;
				fim = meio - 1;
			}else
				ini = meio + 1;
		}
		
		dif += abs( tam[ i ] - 2 * soma );
	}
	
	return dif;
}

int main(){
	
	while( scanf( "%d", &n ) && n ){
		for( int i = 0; i < n; ++i ){
			scanf( "%d", tam + i );
			int temp;
			grupos[ i ].clear();
			for( int j = 0; j < tam[ i ]; ++j ){
				scanf( "%d", &temp );
				grupos[ i ].push_back( temp );
			}
			
			sort( grupos[ i ].begin(), grupos[ i ].end() );
		}
		
		int melhor = 0x7fffffff;
		for( int i = 0; i <= 1000; ++i ){
			melhor = min( melhor, bs( i ) );
		}
		
		printf( "%d\n", melhor );
	}
}


