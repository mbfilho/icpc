#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef long long ll;
#define MOD 1000000000000LL

ll k1;

ll mult(ll a, ll b, ll mod){
	ll tmp = 0;

	while(a){
		if(a&1) tmp = (tmp + b) % mod;
		b = (b + b) % mod;
		a >>= 1;
	}
	
	return tmp;
}

ll expo(ll b, ll a, ll mod){
	ll tmp = 1;
	
	while(a){
		if(a&1) tmp = mult(b, tmp, mod);
		a >>= 1;
		b = mult(b, b, mod);
	}

	return tmp;
}

ll back(ll num, ll dig){
	ll mod = dig * 10;
	if(dig == MOD)
		return num;
	
	fr(d, (dig == MOD), 10){
		if(expo(k1, num, mod) == num % mod){
			ll resp = back(num, dig*10);
			if(resp) return resp;
		}
				
		num += dig;			
	}
	
	return 0;
}

int main(){
	int res = 1;

	while(cin >> k1 && k1){
		ll k2 = 0;
		
		rep(d, 10) if((k2 = back(d, 10))) break;
		cout << "Case " << res++ << ": Public Key = " << k1 << " Private Key = " << k2 << endl;
	}
}
