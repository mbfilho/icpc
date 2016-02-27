#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define N 200200
typedef pair<int,int> pii;
#define mp make_pair

struct Q{
	int id, val, tipo;
};

vector<int> tree[N];
int ini[N];
vector<Q> node[N];
vector<pii> res;

int n, m;

int bit[N];

void update(int idx, int val){
	while(idx < N) bit[idx] += val, idx += idx & -idx;
}

int sum(int idx){
	int s = 0;
	while(idx) s += bit[idx], idx -= idx & -idx;
	return s;
}

void rec(int p, int no, int dep){
	int fat = (dep == 0 ? 1 : -1);
	rep(q, node[no].size()){
		Q tmp = node[no][q];
		if(tmp.tipo == 2) res.pb(mp(tmp.id, ini[no] + fat * sum(tmp.id)));
		else update(tmp.id, fat * tmp.val); 
		//multiplicar por fat funciona de forma surpreendente,
		// pois pega o valor correto para esse nó e ao mesmo tempo inverte o valor para os filhos!
	}
		
	rep(i, tree[no].size()){
		int nt = tree[no][i];
		if(nt == p) continue;
		
		rec(no, nt, dep^1);
	}
	
	rep(q, node[no].size()){
		Q tmp = node[no][q];
		if(tmp.tipo == 1) update(tmp.id, -fat * tmp.val);
	}
}

int main(){
	scanf("%d%d", &n, &m);
	rep(i, n) scanf("%d", ini+i+1);
	
	rep(i, n-1){
		int u, v;
		scanf("%d%d", &u, &v);
		tree[u].pb(v), tree[v].pb(u);
	}
	
	rep(i, m){
		Q tmp;
		int v;
		scanf("%d%d", &tmp.tipo, &v);
		tmp.id = i+1;
		if(tmp.tipo == 1) scanf("%d", &tmp.val);
		node[v].pb(tmp);
	}
	
	rec(-1, 1, 0);
	sort(res.begin(), res.end());
	rep(i, res.size()) printf("%d\n", res[i].second);
}


