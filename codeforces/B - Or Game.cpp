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
#define N 200100

int n, k, x;
int inp[N];
int R[N], L[N];

int main(){
	ios::sync_with_stdio(false);
	cin >> n >> k >> x;
	_(n) cin >> inp[i];

	int tmp = x;
	_(k-1) x *= tmp;

	L[0] = inp[0];
	fr(i, 1, n) L[i] = L[i-1] | inp[i];

	R[n-1] = inp[n-1];
	for(int i = n - 2; i >= 0; --i) R[i] = R[i+1] | inp[i];

	ll best = 0;
	
	rep(i, n) {
		int l = i ? L[i - 1] : 0, r = i == (n-1) ? 0 : R[i+1];
		best = max(best, l | (ll(inp[i]) * x) | r);
	}

	cout << best << endl;

}

