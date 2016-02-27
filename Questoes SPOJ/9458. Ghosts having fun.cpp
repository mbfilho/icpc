#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 1100

int blocks;
struct no{
	#define SIZE 30
	int val[N/SIZE];
	
	void init(int n){
		blocks = (n+SIZE-1)/SIZE;
		rep(i, blocks) val[i] = 0;
	}
	
	void set(int i){
		int b = i/SIZE;
		i %= SIZE;
		val[b] |= (1<<i);
	}
	
	int operator[](int i){
		int b = i/SIZE;
		i %= SIZE;
		return val[b] & (1<<i);
	}
	
	no& operator|=(const no& other){
		rep(i, blocks){
			val[i] |= other.val[i];
		}
		
		return *this;
	}
	#undef SIZE
};

no adj[N];
int n;

int main(){
	int m;
	scanf("%d%d", &n, &m);
	rep(i, n) adj[i].init(n), adj[i].set(i);
	
	rep(i, m){
		int u, v;
		scanf("%d%d", &u, &v);
		--u; --v;
			
		if(adj[v][u]) printf("%d %d\n", u+1, v+1);
		else if(!adj[u][v]){
			adj[u].set(v);
			adj[u] |= adj[v];
			
			rep(i, n){
				if(i != u && i != v && adj[i][u])
					adj[i] |= adj[u];
			}
		}
	}
	printf("0 0\n");
}




