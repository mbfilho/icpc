//poj

#include <cstring>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
typedef unsigned int ui;
ll A, B, C, k;

ll modo(ll a, ll x){
	a = (a%x) + x;
	return a%x;
}

ll h;
ll gcd(ll a, ll b){
	ll x2 = 1, y2 = 0;
	ll x1 = 0, y1 = 1;
	ll quo, mod;
	
	while(b){
		quo = a / b;
		mod = a % b;
		
		ll tmp = x2 - quo * x1;
		x2 = x1;
		x1 = tmp;
		
		tmp = y2 - quo * y1;
		y2 = y1;
		y1 = tmp;
		
		a = b;
		b = mod;
	}
	h = x2;
	return a;
}

int main(){
	cin.sync_with_stdio(false);
	while(cin >> A >> B >> C >> k && (A|B|C|k)){
		k = 1LL << k;
		ll g = gcd(C, k);
		ll resp;
		
		if((B-A) % g){
			printf("FOREVER\n");
		}else{
			ll x = modo((B-A)/g, k);
			resp = modo(h*x, k);
			resp %= k / g;
			printf("%lld\n", resp);
		}
	}
}







