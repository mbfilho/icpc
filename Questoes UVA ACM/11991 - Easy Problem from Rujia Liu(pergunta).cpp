#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define LIM 1000100

vector<int> adj[LIM];
int mk[LIM], caso;
int n, q;

int main(){
	memset(mk, 0, sizeof mk);
	caso = 0;
	
	while(scanf("%d%d", &n, &q) == 2){
		++caso;

		rep(i, n){
			int tmp;
			scanf("%d", &tmp);
			
			if(mk[tmp] != caso){
				mk[tmp] = caso;
				adj[tmp].clear();
			}
			
			adj[tmp].push_back(i+1);
		}
		
		rep(i, q){
			int k, v;
			scanf("%d%d", &k, &v);
			if(mk[v] != caso || adj[v].size() < k) printf("0\n");
			else printf("%d\n", adj[v][k-1]);
		}
	}
	
}



