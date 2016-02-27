#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef long long ll;

ll expo(ll num, int xp, ll mod){
	ll tmp = 1;
	
	while(xp){
		if(xp&1) tmp *= num, tmp %= mod;
		num *= num;
		num %= mod;
		xp >>= 1;
	}
	
	return tmp;
}

int main(){
	ios::sync_with_stdio(false);
	ll p, a;
	
	while(cin >> p >> a && (p|a)){
		ll resp = expo(a, p, p);
		bool primo = true;
		for(ll i = 2; i * i <= p; ++i){
			if(p % i == 0){
				primo = false;
				break;
			}
		}
		if(resp == a && !primo) cout << "yes" << endl;
		else cout << "no" << endl;
	}
}

