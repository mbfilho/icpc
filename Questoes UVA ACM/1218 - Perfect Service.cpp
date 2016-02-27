#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define N 11000
#define COVER 0
#define UNCOVER 1
#define SERVER 2

int pd[N][3];

int faz(int,int,int);
vector<int> adj[N];

int go(int no, int next_state, int pai){
	int soma = 0;
	for(int i = 0; i < adj[no].size(); ++i){
		int nt = adj[no][i];
		if(nt == pai)
			continue;
			
		soma += faz(nt, next_state, no);
	}
	
	return soma;
}

int faz(int no, int st, int pai){
	int& ret = pd[no][st];
	if(~ret)
		return ret;
	
	if(adj[no].size() == 1 && (~pai)){
		if(st == SERVER)
			return ret = 1;
		else if(st == COVER)
			return ret = 0;
		else if(st == UNCOVER)
			return ret = 1000000;
	}
	ret = 10000000;
	
	if(st == COVER){
		ret = go(no, UNCOVER, pai);
	}else if(st == UNCOVER){
		vector<int> tmp, node;
		int soma = 0;
		for(int i = 0; i < adj[no].size(); ++i){
			int nt = adj[no][i];
			if(nt == pai)
				continue;
			
			int aux = faz(nt, UNCOVER, no);
			tmp.push_back(aux);
			node.push_back(nt);
			soma += aux;
		}
		
		for(int i = 0; i < tmp.size(); ++i){
			int custo = soma - tmp[i];
			custo += faz(node[i], SERVER, no);
			ret = min(ret, custo);
		}
		
	}else if(st == SERVER){
		ret = 1;
		
		for(int i = 0; i < adj[no].size(); ++i){
			int nt = adj[no][i];
			if(nt != pai)
				ret += min(faz(nt, SERVER, no), faz(nt, COVER, no));
		}
	}
	
	return ret;
}


int main(){
	int n;
	while(scanf("%d", &n) == 1 && (~n)){
		for(int i = 0; i <= n; ++i)
			adj[i].clear();
		
		for(int i = 1; i < n; ++i){
			int u, v;
			scanf("%d%d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		
		memset(pd, -1, sizeof pd);
		int _unc = faz(1, UNCOVER, -1);
		int _ser = faz(1, SERVER, -1);
		int resp = min(_unc,_ser);
		printf("%d\n", resp);
		scanf("%d", &n);

		if(n == -1)
			break;
		
	}
}





