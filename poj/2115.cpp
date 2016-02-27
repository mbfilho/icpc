#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;


ll xlinha, ylinha;
ll gcd( ll a, ll b ){
	ll x2, x1, y2, y1, mod, quo, atx, aty;
	x2 = 1;	y2 = 0;	x1 = 0;	y1 = 1;
	
	while( b ){
		quo = a / b;
		mod = a % b;
		atx = x2 - quo * x1;
		aty = y2 - quo * y1;
		a = b;
		b = mod;
		x2 = x1;
		y2 = y1;
		x1 = atx;
		y1 = aty;
	}
	
	xlinha = x2;
	ylinha = y2;
	
	return a;
}

int main(){
	ll a, b, c, k;
	while( scanf( "%lld%lld%lld%lld", &a, &b, &c, &k ) != EOF ){
		if( a == 0 && b == 0 && c == 0 && k == 0 ) break;
		
		k = 1LL << k;
		ll dif = b - a;
		while( dif < 0 ) dif += k;
		
		ll g = gcd( c, k );
		if( dif % g )
			printf( "FOREVER\n" );
		else{
			ll resp = ( xlinha * dif / g ) % k;
			while( resp < 0 ) resp = resp + k;
			k /= g;
			resp = resp % k; //Para achar a menor resposta possivel!
//			while( resp < 0 ) resp += g;
			printf( "%lld\n", resp );
		}
	}
}

