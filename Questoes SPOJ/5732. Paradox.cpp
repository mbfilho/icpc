#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 300

vector<int> adj[N];
int scc[N], tempo[N], pilha[N], cont, tt, sp;

void clear(int n = N){
	rep(i, n){
		adj[i].clear();
		scc[i] = tempo[i] = -1;
	}
	cont = tt = sp = 0;
}

int dfs(int no){
	pilha[sp++] = no;
	int low = tempo[no] = tt++;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(~scc[nt]) continue;
		
		if(~tempo[nt]) low = min(low, tempo[nt]);
		else low = min(low, dfs(nt));
	}
	
	if(low == tempo[no]){
		int tmp;
		do{
			tmp = pilha[--sp];
			scc[tmp] = cont;
		}while(tmp != no);
		++cont;
	}
	return low;
}

int yes(int a){
	return 2*a;
}

int no(int a){
	return 2*a+1;
}

#define pb push_back
void add(int a, int b){
	adj[a].pb(b);
	adj[b^1].pb(a^1);
}

int main(){
	int n;
	while(scanf("%d", &n) == 1 && n){
		clear(2*n);
		rep(i,n){
			int other;
			char val[10];
			scanf("%d%s", &other, val);
			--other;
			
			if(val[0] == 't'){
				add(yes(i), yes(other));
				add(no(i), no(other));
			}else{
				add(yes(i), no(other));
				add(no(i), yes(other));
			}
		}
		
		bool sat = true;
		rep(i, n){
			if(scc[yes(i)] == -1) dfs(yes(i));
			if(scc[no(i)] == -1) dfs(no(i));
			
			if(scc[yes(i)] == scc[no(i)]){
				sat = false;
				break;
			}
		}
		
		if(sat) printf("NOT PARADOX\n");
		else printf("PARADOX\n");
	}
}



