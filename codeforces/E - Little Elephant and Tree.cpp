#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for( __typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 100100
#define T (2*N)
typedef pair<int,int> pii;
#define mp make_pair
#define pb push_back

vector<pii> inter[N];

struct Q{
	bool ini;
	int q, x;
	
	Q(){}
	Q(int query, int ind, bool comeco){
		ini = comeco;
		q = query;
		x = ind;
	}
	bool operator<(const Q& ot) const{
		if(x != ot.x) return x < ot.x;
		return ini > ot.ini;
	}
};
vector<Q> eventos;

vector<int> adj[N];
int n;
pii range[N];
int tempo;

int esq[T], dir[T], size[T], mk[T];
int tree;

int build(int no, int x, int y){
	if(x != y){
		int mid = (x+y)/2;
		esq[no] = build(tree++, x, mid);
		dir[no] = build(tree++, mid+1, y);
	}else 
		esq[no] = dir[no] = -1;
		
	return no;
}

void update(int no, int x, int y){
	if(mk[no]){
		size[no] = y - x + 1;
	}else{
		if(~esq[no])
			size[no] = size[esq[no]] + size[dir[no]];
		else
			size[no] = 0;
	}
}

void increment(int no, int x, int y, int ini, int fim, int val){
	if(ini > y || fim < x) return;
	
	if(ini <= x && fim >= y){
		mk[no] += val;
		update(no, x, y);
	}else{
		int mid = (x+y)/2;
		increment(esq[no], x, mid, ini, fim, val);		
		increment(dir[no], mid+1, y, ini, fim, val);
		update(no, x, y);
	}
}

int mapa[N];
void dfs(int no, int pai){
	range[no].first = tempo;
	mapa[tempo++] = no;
	
	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(nt != pai){
			dfs(nt, no);
		}
	}
	
	range[no].second = tempo-1;
}


void addQuery(int i, int a, int b){
	inter[i].pb(range[a]);
	inter[i].pb(range[b]);
	sort(inter[i].begin(), inter[i].end());
	
	if(inter[i][1].first <= inter[i][0].second){
		inter[i][0].second = max(inter[i][0].second, inter[i][1].second);
		inter[i].pop_back();
	}
	
	rep(j, inter[i].size()){
		pii tmp = inter[i][j];
		eventos.pb(Q(i, tmp.first, true));
		eventos.pb(Q(i, tmp.second, false));
	}
}

void dealQuery(int q, int val){
	rep(j, inter[q].size()){
		pii r = inter[q][j];
		increment(0, 0, n-1, r.first, r.second, val);
	}
}

int resp[N];
int main(){
	ios::sync_with_stdio(false);
	int q;
	cin >> n >> q;
	rep(i, n-1){
		int u, v;
		cin >> u >> v;
		--u; --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(0, -1);
	if(tempo != n) throw 1;
	
	rep(i, q){
		int a, b;
		cin >> a >> b;
		--a; --b;
		addQuery(i, a, b);
	}
	
	sort(eventos.begin(), eventos.end());
	
	tree = 0;
	build(tree++, 0, n-1);
	int prt = 0;
	rep(i, n){
		while(prt < eventos.size() && eventos[prt].ini && eventos[prt].x == i){
			dealQuery(eventos[prt].q, 1);
			++prt;
		}
		if(size[0])
			resp[mapa[i]] = size[0] - 1;
		while(prt < eventos.size() && !eventos[prt].ini && eventos[prt].x == i){
			dealQuery(eventos[prt].q, -1);
			++prt;
		}
	}
	
	rep(i, n){
		if(i) cout << " ";
		cout << resp[i];
	}
	cout << endl;
	
}



