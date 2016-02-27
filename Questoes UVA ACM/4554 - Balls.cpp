#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int pd[ 1001 ][ 51 ];

int rec( int ini, int fim, int qtd ){
	if( ini > fim ) return 0;
	if( qtd == 0 ) return 0x80000000;
	if( ini == fim ) return 1;
	
	int& ret = pd[ fim - ini + 1 ][ qtd ]; 	
	if( ret != -1 ) return ret;
	
	ret = 0x7fffffff;
	for( int i = ini; i <= fim; ++i ){
		int r1 = rec( ini, i - 1, qtd - 1 ), r2 = rec( i + 1, fim, qtd );
		if( r1 == 0x80000000 || r2 == 0x80000000 ) continue;
		
		ret = min( ret, 1 + max( r1, r2 )  );
		
	}
	
	return ret;
}


int main(){
	int casos;
	scanf( "%d", &casos );
	
	memset( pd, -1, sizeof( pd ) );
	while( casos-- ){
		int id, balls, f;
		scanf( "%d %d %d", &id, &balls, &f );
		
		printf( "%d %d\n", id, rec( 0, f - 1, balls ) );
	}
}
