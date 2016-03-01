#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;
typedef long long ll;

ll rec( ll n, ll k ){
	if( n == 1 ) return 1;
	
	ll ret = ( rec( n - 1, k ) + k ) % n;
	if( !ret ) ret = n;
	
	return ret;
}

ll faz( ll n, ll k ){
	if( n == 1 ) return 1;
	if( n <= k ){
		return rec( n, k );
	}
	
	ll tmp = faz( n - n / k, k );
	ll ret;
	if( tmp  <= n % k ){
		ret = k*(n/k) + tmp;
	}else{
		tmp -= n % k;
		ret = k * ( tmp / ( k - 1 ) )+ tmp % (k-1); 
		if( ret % k == 0 ) --ret;
	}
	
	return ret;
}


int main(){
	#ifndef X
	freopen( "psyche.in", "r", stdin );
	freopen( "psyche.out", "w", stdout );
	ll n;
	int k;
	
	scanf( "%I64d %d", &n, &k );
	printf( "%I64d\n", faz( n, k ) );
	#endif
}



