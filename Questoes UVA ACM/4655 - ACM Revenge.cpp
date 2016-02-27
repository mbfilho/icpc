#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define N 25000

vector<Ponto> adj[N];
ll t[N];
int n;

ll faz(int no){
	if(adj[no].size() == 0) return 1;
	
	pair<ll,int> esq = mp(faz(adj[no][0].X), 1-adj[no][0].Y), dir = mp(faz(adj[no][1].X), 1-adj[no][1].Y), best;

	if(esq < dir) best = esq;
	else best = dir;
//	printf( "(%lld,%d)\n", best.X, best.Y);
	
	ll resp = 2*best.X + t[no];
	
	if(!best.Y) --resp;
//	printf( ">>> %d : %lld\n", no, resp);
	return resp;
}

int main(){
	while(scanf("%d", &n) != EOF && n){
		for(int i = 0; i <= n; ++i) adj[i].clear();
		int root;
		
		for(int i = 1; i <= n; ++i){
			int pai, edge;
			scanf("%d%d%lld", &pai, &edge, t + i);
			
			if(pai)
				adj[pai].push_back(mp(i, edge));
			else
				root = i;
		}
		
//		printf(">>>> %d\n", root);
		ll tmp = faz(root);
		printf( "%lld\n", tmp - 1);
	}
}


