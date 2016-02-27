#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef long long ll;
#define N 10100
#define M 200

int ini[N], fim[N];
int n;


int main(){
	ios::sync_with_stdio(false);
	int m;

	while(cin >> n >> m && (n|m)){
		int trash;
		rep(i, n) cin >> trash >> trash >> ini[i] >> fim[i], fim[i] += ini[i] - 1;

		while(m--){
			int u, v;
			cin >> u >> v;
			v += u - 1;
			int ans = 0;
			rep(i, n) if(max(ini[i], u) <= min(fim[i], v)) ++ans;

			cout << ans << endl;
		}
	}
}