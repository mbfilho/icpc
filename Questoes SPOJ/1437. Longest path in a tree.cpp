#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) Fr(i,0,n)
#define N 20000

vector<int> adj[N];
int n;
int best;

int dfs(int no, int pai){
	int ft = 0, snd = 0;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(nt == pai) continue;
		
		int tmp = dfs(nt, no);
		if(tmp > ft){
			swap(snd, ft);
			ft = tmp;
		}
		else if(tmp > snd) snd = tmp;
	}
	
	best = max(best, ft + snd);
	return ft + 1;
}

int main(){
	while(scanf("%d", &n) == 1&& n){
		rep(i, n) adj[i].clear();
		best = 0;
		rep(i, n-1){
			int a, b;
			scanf("%d%d", &a, &b);
			--a; --b;
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		
		dfs(0, -1);
		printf("%d\n", best);
	}
}



