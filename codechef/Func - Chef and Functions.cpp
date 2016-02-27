#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define reps(i, str) for(int i = 0; str[i]; ++i)
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 12000
#define MOD 1000000007

int A[N], acc[N], n, q;
int lim[] = {0,-1,1000000000,1000000,31622,3981,1000,372,177,100,63,43,31,24,19,15,13,11,10,8,7,7,6,6,5,5,4,4,4,4,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};


ll expo(ll a, int xp){
	ll ans = 1;

	while(xp){
		if(xp&1) ans *= a;

		xp >>= 1;
		a *= a;
	}

	return ans;
}

//raiz(ord, x) ^ ord <= x
int raiz(int ord, ll x){
	if(ord == 1) return x;

	int ini = 0, fim = lim[ord];

	while(ini <= fim){
		int mid = (ini+fim)>>1;
		if(expo(mid, ord) <= x) ini = mid+1;
		else fim = mid-1;
	}
	return ini-1;
}

int main(){
	int t;
	scanf("%d", &t);

	while(t--){
		scanf("%d%d", &n, &q);
		_(n) scanf("%d", A + i);
		bool ft = true;
		acc[n-1] = A[n-1];
		for(int i = n - 2; i >= 0; --i) acc[i] = (A[i] + acc[i+1])%MOD;

		while(q--){
			if(ft) ft = false;
			else printf(" ");

			ll x;
			int ans = 0;
			scanf("%lld", &x);

			_(n){
				ll fat = (i == 0) ? x : raiz(i+1, x);

				if(fat == 1){
					ans = (ans + acc[i]) % MOD;
					break;
				}
				fat %= MOD;
				ans = (fat * A[i] + ans)%MOD;
			}
			if(ans < 0) ans += MOD;
			printf("%d", ans);
		}
		printf("\n");
	}
}
