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
#define sd second
#define N 30

int cnt[N];
bool adj[N][N];
vector<pii> G;
int n, p;

int main(){
	ios::sync_with_stdio(false);
	int t;
	cin >> t;

	while(t--){
		cin >> n >> p;
		memset(cnt, 0, sizeof cnt);
		memset(adj, 0, sizeof adj);
		G.clear();

		int tot = 2 * n + p;

		while(tot--){
			pii menor = mp(1000000, -1), ot = mp(100000, 0);
			rep(i, n) menor = min(menor, mp(cnt[i], i));

			rep(i, n) if(i != menor.sd && !adj[i][menor.sd]){
				ot = min(ot, mp(cnt[i], i));
			}

			adj[menor.sd][ot.sd] = adj[ot.sd][menor.sd] = true;
			G.pb(mp(menor.sd+1, ot.sd+1));
			++cnt[menor.sd], ++cnt[ot.sd];
		}

		rep(i, G.size()) cout << G[i].ft << " " << G[i].sd << endl;
	}

}