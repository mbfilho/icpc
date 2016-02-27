#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

ll a, b, n;

ll gcd( ll x, ll y ){
	ll tmp;
	while(y){
		tmp = x % y;
		x = y;
		y = tmp;
	}
	
	return x;
}

int main(){
	scanf( "%lld %lld %lld", &a, &b, &n );
	ll g = gcd(a,b);
	
	ll aa = min(n/a, b/g), bb = min(n/b, a/g);
	ll ma = 0, mb = 0;
	
	if(aa < bb){
		for(int i = 0; i <= aa; ++i){
			ll tmp = (n - i*a)/b;
			if( i * a + tmp * b > ma * a + mb * b ){
				ma = i; mb = tmp;
			}
		}
	}else{
		for( int i = 0; i <= bb; ++i ){
			ll tmp = (n - i*b)/a;
			if( tmp * a + i * b > ma * a  + mb * b ){
				ma = tmp; mb = i;
			}
		}
	}
	
	printf( "%lld %lld\n", ma, mb );
	
}





