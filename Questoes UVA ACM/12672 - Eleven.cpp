#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef long long ll;
#define N 101
#define MOD 1000000007
typedef pair<ll,ll> pll;
#define mp make_pair

ll fat[N], fatInv[N];
int n;
ll memo[N][20][21];
int mk[N][20][21], step;
int cnt[10], tot[20];

pll gcd(ll a, ll b){
	if(!b) return mp(1, 0);
	pll rec = gcd(b, a %b);
	return mp(rec.second, rec.first - rec.second * (a / b));
}

ll fix(ll num){
	num %= MOD, num+=MOD, num%= MOD;
	return num;
}

// bool db = false;
ll rec(int par, int dig, int mod){

	if(dig == 10){
		return ((mod == 0) * fat[n/2] * fat[n-n/2]) % MOD;
	}
	ll& pd = memo[par][dig][mod];
	if(mk[par][dig][mod] == step) return pd;
	mk[par][dig][mod] = step;
	pd = 0;

//verifica a quantidade de posições pares. Isso para evitar guarda a qtd de pares e impares no estado.
	rep(i, 1+cnt[dig]) if(i <= par && par - i <= tot[dig+1]){
		int nmod = (mod + i * dig - (cnt[dig] - i) * dig) % 11;
		nmod += 11, nmod %= 11;
		ll tmp = rec(par - i, dig+1, nmod);
		tmp = (tmp * fatInv[i])	% MOD;
		tmp = (tmp * fatInv[cnt[dig]-i]) % MOD;
		pd = (pd + tmp) % MOD;

	}
	return pd;
}


int main(){
	ios::sync_with_stdio(false);
	fatInv[0] = fatInv[1] = fat[0] = fat[1] = 1;
	fr(i, 2, N)	fatInv[i] = (fatInv[i-1] * gcd(i, MOD).first) % MOD, fat[i] = (fat[i-1] * i) % MOD;

	string tmp;
	while(cin >> tmp){
		n = tmp.size();
		memset(cnt, 0, sizeof cnt);
		rep(i, tmp.size()) ++cnt[tmp[i]-'0'];

		--n;
		ll ans = 0;
		fr(i, 1, 10) if(cnt[i]){
			--cnt[i];
			tot[10] = 0;
			for(int j = 9; j >= 0; --j) tot[j] = tot[j+1] + cnt[j];
			++step;
			ans += rec(n/2, 0, i), ans %= MOD;
			++cnt[i];
		}
		if(ans < 0) ans += MOD;
		cout << ans << endl;

	}



}
