#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 310
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back
typedef long long ll;
ll oo = 0x3f3f3f3f3f3f3f3fLL;
int n, k;
ll A[N][N];//min cost to cover the whole segment from i to j

void calcA(){
	fr(size, 1, n){
		for(int i = 1; i + size <= n; ++i){
			int j = i + size;
			ll aux = oo;
			fr(x, i, j+1){
				aux = min(A[x][j], aux);
				A[i][j] = min(A[i][j], A[i][x] + aux);
			}
		}
	}
}

ll memo[N][N];
ll rec(int idx, int fixed){
	if(fixed >= k) return 0;
	if(idx > n) return oo;
	ll& pd = memo[idx][fixed];
	if(~pd) return pd;
	pd = oo;
	
	fr(i, idx, n+1){
		ll tmp = rec(i+1, fixed + i-idx+1);
		pd = min(pd, tmp + A[idx][i]);
	}
	
	pd = min(pd, rec(idx+1, fixed));
	return pd;
}

int main(){
	int m;
	scanf("%d%d%d", &n, &m, &k);
	memset(memo, -1, sizeof memo);
	memset(A, 0x3f, sizeof A);
	rep(i, m){
		int l, r, c;
		scanf("%d%d%d", &l, &r, &c);
		A[l][r] = min(A[l][r], ll(c));
	}	
	
	calcA();
	ll res = rec(1,0);
	if(res >= oo) res = -1;
	cout << res << endl;
}

