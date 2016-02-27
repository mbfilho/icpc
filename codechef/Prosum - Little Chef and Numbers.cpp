#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define N 100100
#define LIM 1000100
int A[N], n;
int bit[LIM], pre[LIM];

void update(int i){
	for(; i > 0; i -= i & -i) ++bit[i];
}

int query(int i){
	int s = 0;
	for(; i < LIM; i += i & -i) s += bit[i];
	return s;
}

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;
	pre[0] = LIM;
	fr(i, 1, LIM){
		pre[i] = pre[i-1];
		while(pre[i] > 0 && ll(i) * pre[i] > i + pre[i]) --pre[i];
		++pre[i];
	}
	while(t--){
		cin >> n;
		rep(i, n) cin >> A[i];
		memset(bit, 0, sizeof bit);
		ll ans = 0;

		rep(i, n){
			ans += query(pre[A[i]]);
			update(A[i]);
		}

		cout << ans << endl;
	}
}
