#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;


int main(){
	ll l, k;
	int r = 0;
	cin >> k >> l; 
	
	ll temp = k;
	while( k < l ){
		++r;
		k = k * temp;
	}
	
	if( k == l )
		printf( "YES\n%d\n", r );
	else
		printf( "NO\n" );
}


