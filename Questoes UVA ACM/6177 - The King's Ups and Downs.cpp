#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 22

ll pd[2][N][N];

ll memo(bool big, int st, int n){
	if(!n) return 1;
	if(st >= n || st < 0) return 0;
	
	ll& ans = pd[big][st][n];
	if(~ans) return ans;
	ans = 0;
	
	if(big){
		fr(i, st, n) ans += memo(false, i-1, n-1);
	}else{
		rep(i, st+1) ans += memo(true, i, n-1);
	}
	
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int d, n;
		scanf("%d%d", &d, &n);
		if(n == 1) printf("%d 1\n", d);
		else{
			memset(pd, -1, sizeof pd);
			ll ans = memo(true, 0, n) + memo(false, n-1, n);
			printf("%d %lld\n", d, ans);
		}
	}
}





