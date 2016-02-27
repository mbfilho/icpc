#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
#define oo 0x7fffffff
typedef pair<int,int> pii;
#define mp make_pair

vector<pii> adj[N];
vector<int> S;
int ma[15][15];
int n;
int dist[N];
bool mk[N];
void dij(int src){
	rep(i, n) dist[i] = oo, mk[i] = false;
	priority_queue<pii> heap;
	heap.push(mp(0,src));
	dist[src] = 0;
	
	while(!heap.empty()){
		int at = heap.top().second, custo = -heap.top().first;
		heap.pop();
		
		if(mk[at]) continue;
		mk[at] = true;
		rep(i, adj[at].size()){
			int nt = adj[at][i].first, e = adj[at][i].second;
			
			if(mk[nt] == false && dist[nt] > custo + e){
				dist[nt] = custo + e;
				heap.push(mp(-dist[nt], nt));
			}
		}
	}
}

int pd[12][1<<12];

int memo(int last, int mask){
	if(mask == (1<<(S.size()-1)) - 1) return ma[last][S.size()-1];
	
	int& rec = pd[last][mask];
	if(~rec) return rec;
	rec = oo;
	
	rep(i, S.size()){
		int nt = S[i];
		if(i == last || !nt) continue;
		if((1<<i) & mask) continue;
	
		if(ma[last][i] != oo)
			rec = min(rec, ma[last][i] + memo(i, mask | (1<<i)));
	}
	
	return rec;
}


int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		int m;
		scanf("%d%d", &n, &m);
		rep(i, n) adj[i].clear();
		
		rep(i, m){
			int u, v, c;
			scanf("%d%d%d", &u, &v, &c);
			adj[u].push_back(mp(v,c));
			adj[v].push_back(mp(u,c));
		}
		
		int s;
		scanf("%d", &s);
		S.clear();
		while(s--){
			int tmp;
			scanf("%d", &tmp);
			S.push_back(tmp);
		}
		
		rep(i, 15) rep(j, 15) ma[i][j] = oo;
		
		S.push_back(0);
		rep(i, S.size()){
			dij(S[i]);
			rep(j, S.size())
				ma[i][j] = dist[S[j]];
		}
		
		memset(pd, -1, sizeof pd);
		int best = memo(S.size()-1, 0);
		printf("%d\n", best);
	}
}

