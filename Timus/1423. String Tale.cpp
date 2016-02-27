#include <cstdio>
#include <algorithm>
#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <set>
using namespace std;

#define MAXI 500100

char text[ MAXI ], pat[ MAXI ];
int tt, tp;

typedef unsigned long long ull;
ull base = 17;

int rexi(){
	ull acc = 0, hp = 0, expo = 1;
	
	for( int i = 0; i < tp; ++i ){
		hp = hp * base + ( pat[ i ] );
		acc = acc * base + text[i];
	}
	
	for( int i = 0; i < tp - 1; ++i )
		expo = expo * base;
	
	if( acc == hp ){
		return 0;
	}
		
	for( int i = tp; i < tt; ++i ){
		acc = acc - text[ i - tp ] * expo;
		acc = acc * base + text[i];
		if( acc == hp ){
			//printf( "%d %d %d\n", i, tp, 0 );
			return tt / 2 - (i - tp + 1);
		}
	}
	
	return -1;
}



int main(){
	int n;
	char temp[ MAXI ];
	
	while( scanf( "%d", &n ) != EOF ){
		scanf( "%s %s", temp, pat );
		sprintf( text, "%s%s", temp, temp );
		tt = 2 * n;
		tp = n;
		
		printf( "%d\n", rexi() );
	}
}

