#include <cstdio>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;

ll a, b, m;
ll teto(ll x, ll y){
	if((x%y) == 0) return x / y;
	ll k = x / y;
	if(k > 0) return k + 1;
	return k - 1;
}

int main(){
	cin >> a >> b >> m;
	
	bool dm = false;
	ll cnt = 0;
	if(b > a) swap(a,b);
	while(a < m){
		if(a+b <= b){
			dm = true;
			break;
		}
		
		ll k = teto(a-b, a);
		if(!k) ++k;
		b += k * a;
		cnt += k;
		
		if(b > a) swap(a,b);
	}
	if(dm) cout << "-1\n";
	else cout << cnt << endl;
}

