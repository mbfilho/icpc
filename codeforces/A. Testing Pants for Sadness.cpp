#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define N 110
typedef long long ll;

ll soma[ N ], a[ N ];

int main(){
	int n;
	scanf( "%d", &n );
	for( int i = 0; i < n; ++i )
		cin >> a[ i ];
	
	soma[ 0 ] = a[ 0 ];
	for( int i = 1; i < n; ++i )
		soma[ i ] = a[ i ] + soma[ i - 1 ] + ( a[ i ] - 1 ) * i; 
	
	cout << soma[ n - 1 ];
}














