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
#define N 2000

int n;
char ans[N], correct[N];
pii W[N];
int main(){
	int t;
	scanf("%d", &t);

	while(t--) {
		scanf("%d %s %s", &n, correct, ans);
		int acc = 0;
		rep(i, n) acc += (correct[i] == ans[i]);
		bool wa = acc != n;
		rep(i, n+1) scanf("%d", &W[i].ft), W[i].sd = i;
		sort(W, W + n + 1);
		
		int best = -1;
		for(int i = n; i >= 0; --i) {
			bool can = (acc == W[i].sd) || (acc > W[i].sd && wa);
			if(can) best = max(best, W[i].ft);
		}

		printf("%d\n", best);
	}
}