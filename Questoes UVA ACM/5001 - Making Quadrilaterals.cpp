#include <cstdio>
#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
#include <set>
#include <vector>
#include <list>
using namespace std;
typedef long long ll;

ll pd[65];

int main(){
	pd[ 1 ] = pd[ 2 ] = pd[ 3 ] = 1;
	
	for( int i = 4; i <= 61; ++i )
		pd[ i ] = pd[ i - 3 ] + pd[ i - 1 ] + pd[ i - 2 ];
	int temp, caso = 1;
	
	while( scanf( "%d", &temp ) && temp )
		printf( "Case %d: %lld\n", caso++, pd[ temp ] );
}
