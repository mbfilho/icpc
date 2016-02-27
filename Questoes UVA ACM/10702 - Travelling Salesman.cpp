#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back
#define N 200
#define oo 700000000

vector<pii> adj[N];
bool end[N];
int n, t;

int pd[N][1200], mk[N][1200], caso;

int memo(int no, int rest){
	if(!rest){
		if(end[no]) return 0;
		return -oo;
	}
	
	if(mk[no][rest] == caso) return pd[no][rest];
	mk[no][rest] = caso;
	int& val = pd[no][rest];
	val = -oo;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i].first, custo = adj[no][i].second;
		val = max(val, custo + memo(nt, rest - 1));
	}
	
	return val;
}
int main(){
	caso = 0;
	memset(mk, 0, sizeof mk);
	int s, e;
	while(scanf("%d%d%d%d", &n, &s, &e, &t) == 4 && (n|s|e|t)){
		++caso;
		--s;
		rep(i, n) adj[i].clear(), end[i] = false;
		
		int custo;
		rep(i, n){
			rep(j, n){
				scanf("%d", &custo);
				adj[i].pb(mp(j, custo));
			}
		}
		
		rep(i, e){
			int tmp;
			scanf("%d", &tmp);
			--tmp;
			end[tmp] = true;
		}
		
		printf("%d\n", memo(s, t));
		
	}
}


