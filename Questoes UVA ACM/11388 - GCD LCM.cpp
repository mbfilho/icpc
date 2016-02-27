#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

ll gcd( ll a, ll b ){
	ll temp;
	
	while( b ){
		temp = a % b;
		a = b;
		b = temp;
	}
	
	return a;
}

int main(){
	ll casos;
	scanf( "%d", &casos );
	
	while( casos-- ){
		ll g, l;
		scanf( "%d %d", &g, &l );
		
		ll b = g * l / gcd( g, l );
		if( b > l || l < g )
			printf( "-1\n" );
		else
			printf( "%d %d\n", g, b );
	}
}



