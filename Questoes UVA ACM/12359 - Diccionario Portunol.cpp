#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;

int adj[300000][30];
int cont[30], nos;
int prt;

void init(int no){
	rep(i,30) adj[no][i] = -1;
}

void insert(char* word, int k, int root){
	int start = root;
	
	for(int i = 0; word[i]; ++i){
		int ch = word[i] - 'a';
		if(adj[root][ch] == -1){
			init(prt);
			adj[root][ch] = prt++;
			if(k){
				if(root != start)
					++cont[ch];
				++nos;
			}
		}
		root = adj[root][ch];
	}
}

ll resp;
void dfs(int root){
	if(root) 
		resp += nos;
	
	rep(i, 30){
		if(adj[root][i] != -1){
			dfs(adj[root][i]);
			
			if(root)
				resp -= cont[i];
		}
	}
}

char buf[10000];
int main(){
	int n, m;
	
	while(scanf("%d%d", &n, &m) == 2 && (n|m)){
		prt = nos = 0;
		memset(cont, 0, sizeof cont);
		
		init(prt++);
		rep(i, n){
			scanf("%s", buf);
			insert(buf, 0, 0);
		}
		
		int root = prt++;
		init(root);
		rep(i, m){
			scanf("%s", buf);
			reverse(buf, buf + strlen(buf));
			insert(buf, 1, root);
		}
//		printf("> %d %d %d %d\n", nos, cont[0], cont[1], cont[2]);
		resp = 0;
		dfs(0);
		printf("%lld\n", resp);
	}
}


