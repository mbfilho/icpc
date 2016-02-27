#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
#include <map>
#include <string>
#include <iostream>
using namespace std;
typedef long long ll;

int seq[ 10001 ];
int n;

int bs( int arg ){
	int ret = -1, ini = 0, fim = n - 1, meio;
	
	while( ini <= fim ){
		meio = ( ini + fim ) / 2;
		
		if( seq[ meio ] > arg )
			fim = meio - 1;
		else if( seq[ meio ] < arg )
			ini = meio + 1;
		else{
			ret = meio;
			fim = meio - 1;
		}
	}	
	
	return ret;
}

int main(){
	int caso = 1, q;
	
	while( scanf( "%d %d", &n, &q ) && ( n | q ) ){
		int temp;

		for( int i = 0; i < n; ++i ){
			scanf( "%d", &temp );
			
			seq[ i ] = temp;

		}
		
		printf( "CASE# %d:\n", caso++ );
		sort( seq, seq + n );
		
		int resp;
		for( int i = 0; i < q; ++i ){
			scanf( "%d", &temp );
			if( ( resp = bs( temp ) ) == -1 )
				printf( "%d not found\n", temp );
			else
				printf( "%d found at %d\n", temp, resp + 1 );
		}
	}
	
}
