#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define ft first
#define sd second
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define MOD 1000000007
#define N 2000100

int input[N], tmp[N];
ll cnt[300];
ll sum[300];

void build(int x, int y, int lvl){
	
	if(x != y){
		sum[lvl] += (ll(y-x+1) * (y-x)) >> 1;

		int mid = (x+y) >> 1;

		build(x, mid, lvl+1);
		build(mid+1, y, lvl+1);
		int prt = y, a = mid, b = y;
		while(a >= x && b > mid){
			while(a >= x && input[a] > input[b]) tmp[prt--] = input[a--], cnt[lvl] += b - mid;
			while(a >= x && b > mid && input[b] >= input[a]) tmp[prt--] = input[b--];
		}

		while(a >= x) tmp[prt--] = input[a--];
		while(b > mid) tmp[prt--] = input[b--];
		fr(i, x, y+1) input[i] = tmp[i];

		int h = x;
		while(h <= y){
			int c = 0;
			int fim = h;
			while(fim <= y && input[fim] == input[h]) ++c, ++fim;
			sum[lvl] -= (ll(c) * (c-1)) / 2;
			h = fim;
		}
	}
}

int n, m;
int main(){
	scanf("%d", &n);

	rep(i, (1<<n)) scanf("%d", input + i);
	memset(cnt, 0, sizeof cnt);
	memset(sum, 0, sizeof sum);
	build(0, (1<<n)-1, 0);

	scanf("%d", &m);
	for(int i = 28; i >= 0; --i) cnt[i] += cnt[i+1];

	while(m--){
		int q;
		scanf("%d", &q);
		q = n - q;

		ll delta = -cnt[q];
		fr(i, q, n){
			ll size = (1 << (n-i));
			cnt[i] = sum[i] - cnt[i];
		}
		delta += cnt[q];

		for(int i = q-1; i >= 0; --i) cnt[i] += delta;

		cout << cnt[0] << "\n";
	}
}