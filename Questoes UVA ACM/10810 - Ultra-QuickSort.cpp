#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 500100
typedef long long ll;

int n;
ll bit[N];

void update(int ind, int val){
	while(ind > 0) bit[ind] += val, ind -= ind & (-ind);
}

ll query(int ind){
	ll soma = 0;
	while(ind <= n) soma += bit[ind], ind += ind & (-ind);
	return soma;
}

int input[N], ord[N];

int main(){
	while(scanf("%d", &n) == 1 && n){
		rep(i, n) scanf("%d", input + i), ord[i] = input[i], bit[i+1] = 0;
		sort(ord, ord + n);
		
		ll res = 0;
		rep(i, n){
			int ind = 1 + lower_bound(ord, ord + n, input[i]) - ord;
			res += query(ind);
			update(ind, 1);
		}
		cout << res << endl;
	}
}



