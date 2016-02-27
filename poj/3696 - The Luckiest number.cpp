#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <cmath>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair

typedef long long ll;
typedef pair<ll,int> pii;
vector<pii> mapa;
ll K, L;

void baby(){
	mapa.clear();
	K = 10 + ll(sqrt(double(L)));
	ll pot = 1;
	
	rep(i, K){
		mapa.pb(mp(pot, i));
		pot = (pot * 10) % L;
	}
	sort(mapa.begin(), mapa.end());
}

ll mult(ll a, ll b, ll mod){
	ll resp = 0;
	
	while(b){
		if(b&1) resp += a, resp %= mod;
		a += a;
		a %= mod;
		b >>= 1;
	}
	return resp;
}


ll expo(ll num, ll xp, ll mod){
	ll resp = 1;
	
	while(xp){
		if(xp&1) resp = mult(resp, num, mod);
		num = mult(num, num, mod);
		xp >>= 1;
	}
	return resp;
}

ll giant(){
	ll value = expo(10, K, L), pot = value;
	
	fr(q, 1, K+1){
		int ind = upper_bound(mapa.begin(), mapa.end(), mp(value, 0x7fffffff)) - mapa.begin() - 1;
		if(ind >= 0 && mapa[ind].first == value){
			return q * K - mapa[ind].second;
		}
		value = mult(value, pot, L);
	}
	
	return 0;
}

ll gcd(ll a, ll b){
	return b == 0 ? a : gcd(b, a%b);
}

int main(){
	int caso = 0;
	cin.sync_with_stdio(false);
//Escrever o numero 8's como 8*(10^x - 1)/9
	while(cin >> L && L){
		L = (L * 9) / gcd(L, 8);
		ll resp;
		if(gcd(L, 10) != 1) resp = 0;
		else{
			baby();
			resp = giant();
		}
		
		printf("Case %d: %lld\n", ++caso, resp);
	}
}



