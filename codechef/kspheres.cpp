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
#define MOD 1000000007
#define C 1002

ll cnt[C], cnt2[C];
int n, m;

ll pd[C][2];

int main(){
	int n, m, c;
	scanf("%d %d %d", &n, &m, &c);
	memset(cnt, 0, sizeof cnt);
	memset(cnt2, 0, sizeof cnt2);

	rep(i, n) {
		int aux;
		scanf("%d", &aux);
		++cnt[aux];
	}

	rep(i, m) {
		int aux;
		scanf("%d", &aux);
		++cnt2[aux];
	}

	rep(i, c+1) {
		cnt[i] *= cnt2[i];
		cnt[i] %= MOD;
	}

	int at = 0;
	memset(pd, 0, sizeof pd);
	pd[0][0] = pd[0][1] = 1;

	fr(which, 1, c+1) {
		fr(size, 1, c+2) {
			pd[size][at] = (cnt[which] * pd[size - 1][1-at]) % MOD;
			pd[size][at] = (pd[size][at] + pd[size][1-at]) % MOD;
		}
		at = 1 - at;
	}
	at = 1 - at;
	printf("%lld", pd[2][at]);
	fr(i, 3, c+2) {
		printf(" %lld", pd[i][at]);
	}
	printf("\n");
}
