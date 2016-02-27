#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define N 200
struct NO{
	int a, m, g;
	
	int need(){
		return max(a, m+g);
	}
	
	int saldo(){
		return need() - m - g;
	}
}nos[N];
vector<int> adj[N];
int n;

bool cmp(pii a, pii b){
	return a.second > b.second;
}

pii rec(int at, int pai){
	if(adj[at].size() == 1 && (~pai)) return mp(nos[at].need(), nos[at].saldo());
	
	vector<pii> desc;
	rep(i, adj[at].size()){
		int nt = adj[at][i];
		if(nt != pai) desc.pb(rec(nt, at));
	}
	
	int need = nos[at].need(), saldo = nos[at].saldo();
	sort(desc.begin(), desc.end(), cmp);
	
	rep(i, desc.size()){
		pii kid = desc[i];
		if(saldo < kid.first) need += kid.first - saldo, saldo = kid.first;
		saldo -= (kid.first - kid.second);
	}
	return mp(need, saldo);
}

int main(){
	int caso = 0;
	while(scanf("%d", &n) == 1 && n){
		rep(i, n) adj[i].clear();
		rep(i, n) scanf("%d%d%d", &nos[i].a, &nos[i].m, &nos[i].g);
		
		rep(i, n-1){
			int u, v;
			scanf("%d%d", &u, &v);
			--u, --v;
			adj[u].pb(v);
			adj[v].pb(u);
		}
		int melhor = 1<<30;
		rep(i, n){
			pii r = rec(i, -1);
			melhor = min(melhor, r.first);
		}
		printf("Case %d: %d\n", ++caso, melhor);
	}
}



