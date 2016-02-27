#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>
#include <map>
#include <set>
using namespace std;

typedef long long ll;

int main(){
	char n[ 200 ], m[ 200 ];
	
	scanf( "%s %s", n, m );
	
	for( int i = 0; i < strlen( n ); ++i ){
		if( n[ i ] == m[ i ] )
			printf( "0" );
		else
			printf( "1" );
	}
	
	printf( "\n" );
}