#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

#define MAXI 200100
int n, l;
ll ar[ MAXI ], seq[ MAXI ];

int bs( ll val ){
	int ini = 1, fim = l, meio, ret = 0;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		
		if( seq[ meio ] > val )
			fim = meio - 1;
		else if( seq[ meio ] < val ){
			ret = meio;
			ini = meio + 1;
		}else
			fim = meio - 1;
	}
	
	return ret;
}

int calc(){
	l = 1;
	seq[ 1 ] = ar[ 0 ];
	
	for( int i = 1; i < n; ++i ){
		int ind = bs( ar[ i ] );
	//	printf( "Num %lld ind %d\n", ar[ i ], ind );
		
		if( ind == l || seq[ ind + 1 ] > ar[ i ] ){
			//printf( "Entrei (%d) Num %lld ind %d\n", (ind + 1 ), ar[ i ], ind );
			seq[ ind + 1 ] = ar[ i ];
			l = max( l, ind + 1 );
		}
	}
	

	return l;
}

int main(){
	while( scanf( "%d", &n ) != EOF ){
		
		for( int i = 0; i < n; ++i )
			scanf( "%lld", ar + i );
				
		printf( "%d\n", calc() );
	}	
}


