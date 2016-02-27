#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long ll;
#define mp make_pair
#define oo 0x7fffffff

pair<int,int> cont[ 300 ];
bool exc[ 300 ];
char linha[ 100100 ];
int k;

int main(){
	scanf( "%s", linha );
	scanf( "%d", &k );
	memset( exc, false, sizeof( exc ) );
	for( int i = 'a'; i <= 'z'; ++i )
		cont[ i - 'a' ] = mp( 0, i );
			
	int qtd = 0;
	for( int i = 0; linha[ i ]; ++i ){
		++cont[ linha[i] - 'a' ].first;
		if( cont[ linha[i] - 'a' ].first == 1 )
			++qtd;
	}
	
	sort( cont, cont + ( 'z' - 'a' + 1 ) );
	for( int i = 'a'; k && i <= 'z'; ++i ){
		if( !cont[ i - 'a' ].first ) continue;
		
		if( cont[ i - 'a' ].first <= k ){
			exc[ cont[i-'a'].second ] = true;
			k -= cont[ i - 'a' ].first;
			--qtd;
		}
	}
	
	printf( "%d\n", qtd );
	for( int i = 0; linha[ i ]; ++i ){
		if( !exc[ linha[i] ] )
			printf( "%c", linha[i] );
	}
	printf( "\n" );
	
}
