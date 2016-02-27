
#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define N 2000
#define MOD 1000000007

int p[N], n, pd[N];

int main(){
	ios::sync_with_stdio(false);

	cin >> n;
	fr(i, 1, n+1) cin >> p[i];
	pd[0] = 0;
	fr(r, 1, n+1){
		pd[r] = pd[r-1];
		if(p[r] == r) pd[r] += 2;
		else pd[r] += 1 + pd[r-1] - pd[p[r]-1] + 1;
		pd[r] = (pd[r] % MOD + MOD) % MOD;
	}
	cout << pd[n] << endl;
}