#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 100100
int A[N];

int main(){
	int t, n;

	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		rep(i, n) scanf("%d", A+i);
		ll ans = 0;

		int ini = 0, fim;
		while(ini < n) {
			fim = ini;
			while(fim + 1 < n && A[fim+1] >= A[fim]) ++fim;
			ll tot = fim - ini + 1;
			ans += (tot * (tot + 1)) >> 1;
			ini = fim + 1;
		}

		printf("%lld\n", ans);
	}
}
