#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <cstdio>
using namespace std;
#define N 30100

string yoda[ N ];
char temp[ 100 ];
int bit[ N ];
int n;

void add( int pos, int val ){
	for( int i = pos; i <= n; i += ( i & -i ) )
		bit[ i ] += val;
}

int soma( int pos ){
	int ret = 0;
	
	for( int i = pos; i > 0; i -= ( i & -i ) )
		ret += bit[ i ];
	
	return ret;
}

map<string,int> mapa;

int main(){
	int casos;
	scanf( "%d", &casos );
	while( casos-- ){
		scanf( "%d", &n );
//		memset( bit, 0, sizeof( bit ) );
		for( int i = 0; i <= n; ++i ) bit[ i ] = 0;
		mapa.clear();
		
		for( int i = 0; i < n; ++i ){
			scanf( "%s", temp );
			yoda[ i ] = temp;
		}		
		
		for( int i = 0; i < n; ++i ){
			scanf( "%s", temp );
			mapa[ temp ] = i + 1;
		}
		
		int sum = 0;
		for( int i = 0; i < n; ++i ){
			int pos = mapa[ yoda[i] ];
			sum += soma( n ) - soma( pos );
			add( pos, 1 );
		}
		
		printf( "%d\n", sum );
	}
}


