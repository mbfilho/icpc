#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define N 100100
#define MOD 1000000009
#define M 105
#define pb push_back
#define inv sdfj
#define ft first
#define sd second
typedef long long ll;

//pd combinação
/*
Recorrência:
	pd[i][sum] = SUM(comb[qtd(i), k] * pd[i+1][sum + k*i]) 0 <= k <= qtd(i)
	Note que as chamadas para k = 0 e k = m e k = 2m ... diferem apenas
	na multiplicação pelo fator 'comb'. Tomando k = 0 = m = 2m = 3m... como exemplo:
	tmp[0] = pd[i+1][sum + 0] * ( comb[qtd(i), 0] + comb[qtd(i), m] + comb[qtd(i), 2m] ...)
	O array sum[i][0] corresponde a essa soma.

*/

int cards[N];
int pd[M][M];
int n, m;
vector<int> sum[M];
int qtd[M];

inline int fix(int a){
	if(a >= 0 && a < m) return a;
	a %= m;
	if(a < 0) a += m;
	return a;
}

int faz(){
	rep(i, m) pd[m][i] = 0;
	pd[m][0] = 1;
	for(int ind = m - 1; ind >= 0; --ind){
		rep(s, m){
			int lim = min(m, qtd[ind]+1), &ans = pd[ind][s];
			ans = 0;

			rep(i, lim){
				ans += (pd[ind+1][fix(ind*i + s)] * ll(sum[ind][i]) ) % MOD;
				ans %= MOD;
			}
		}
	}
	return pd[0][0];
}

pair<ll,ll> gcd(ll a, ll b){
	if(!b) return mp(1,0);
	pair<ll,ll> rec = gcd(b, a%b);
	return mp(rec.sd, rec.ft-(a/b)*rec.sd);
}

ll calcInv(int a, int b){
	return gcd(a, MOD).first;
}

ll inv[N];

int main(){
	int t;
	scanf("%d", &t);
	fr(i, 1, N) inv[i] = (calcInv(i, MOD)%MOD+MOD)%MOD;

	while(t--){
		int q;
		scanf("%d%d", &n, &q);
		rep(i, n) scanf("%d", cards+i);
		
		while(q--){
			scanf("%d", &m);
			memset(qtd, 0, sizeof qtd);
			rep(i, M) sum[i].clear();
			rep(i, n) ++qtd[fix(cards[i])];
			rep(i, m) sum[i].resize(qtd[i]+1);
			
			rep(i, m){
				sum[i][0] = 1;
				fr(k, 1, qtd[i]+1){
					ll s = (sum[i][k-1] * ll(qtd[i]-k+1)) % MOD;
					sum[i][k] = (s * inv[k])%MOD;
				}

				fr(k, m, qtd[i]+1) sum[i][k%m] = (sum[i][k%m] + sum[i][k]) % MOD;
			}
			
			printf("%d\n", faz());
		}
	}
}
