#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 100100
typedef pair<int,int> pii;
typedef long long ll;
#define mp make_pair
#define pb push_back
#define ft first
#define sd second
#define LG 17

int H[N], fila[N], W[N], idx[N], pai[N], n;
vector<int> adj[N];
pii desc[N][LG];
pii lim[N];
int mk[N], step;
const pii indef = mp(int(1e9)+10, -1);
struct  No
{
	int no, x, y;

	void set(const int& _no, const int& _x, const int& _y){
		no = _no, x = _x, y = _y;
	}
}_stack[2*N];

struct Tree{
	int tree;
	int *R, *L,  *original;
	ll *op;
	pii* least;
	pii _curMin;

	void init(int* input, int size){ 
		original = input;
		R = new int[2*size], L = new int[2*size], op = new ll[2*size];
		least = new pii[2*size];

		tree = 0; build(input, tree++, 0, size - 1); 
	}

	int build(int* input, int no, int x, int y){
		op[no] = 0;

		if(x == y) R[no] = L[no] = -1, least[no] = mp(W[input[x]], x);
		else{
			int mid = (x+y) >> 1;
			L[no] = build(input, tree++, x, mid);
			R[no] = build(input, tree++, mid+1, y);
			least[no] = min(least[L[no]], least[R[no]]);
		}

		return no;
	}

	void fix(int no){
		if(least[no] == indef) return;
		least[no].ft -= op[no];
		if(~R[no]) op[R[no]] += op[no], op[L[no]] += op[no];
		op[no] = 0;
	}

	void decr(int ini, int fim, int val){ if(ini <= fim) _decr(0, 0, tree/2, ini, fim, val); }
	pii getMin(int ini, int fim){ _curMin = indef; return ini <= fim ? _getMin(0, 0, tree/2, ini ,fim) : indef; }
	void extractMin(int ind){ _extractMin(0, 0, tree/2, ind); }

	void _decr(int no, int x, int y, int ini, int fim, int val){
		fix(no);
		if(ini > y || fim < x) return ;
 
		if(ini <= x && fim >= y){
			op[no] += val;
			fix(no);
		}else{
			int mid = (x+y)>>1;
			_decr(L[no], x, mid, ini, fim, val);
			_decr(R[no], mid+1, y, ini, fim, val);
 
			least[no] = min(least[L[no]], least[R[no]]);
		}
	}

	pii _getMin(int no, int x, int y, int ini, int fim){
		int sp = 0;
		_stack[sp++].set(no, x, y);

		while(sp--){
			No at = _stack[sp];
			fix(at.no);
			if(ini > at.y || fim < at.x) continue;
			if(ini <= at.x && fim >= at.y) _curMin = min(_curMin, least[at.no]);
			else{
				int mid = (at.x+at.y) >> 1;
				_stack[sp].set(L[at.no], at.x, mid);
				_stack[sp+1].set(R[at.no], mid+1, at.y);
				sp += 2;
			}
		}

		return _curMin;
	}

	void _extractMin(int no, int x, int y, int ind){
		fix(no);
		if(ind > y || ind < x) return;

		if(x == y && ind == x) least[no] = indef;
		else{
			int mid = (x+y) >>1;
			_extractMin(L[no], x, mid, ind);
			_extractMin(R[no], mid+1, y, ind);
			least[no] = min(least[L[no]], least[R[no]]);
		}
	}
	

}trees[N];

pii cmpPair(const pii& a, const pii& b){
	return mp(min(a.ft, b.ft), max(a.sd, b.sd));
}

namespace KillingTrack{
	int bit[N], prt;
	pii rng[N];

	void update(int no){
		no = rng[no].ft + 1;
		for(int i = no; i <= n; i += i & -i) bit[i] += 1;
	}

	int getQtd(int a){
		int i = rng[a].ft, j = rng[a].sd + 1, sum = 0;
		for(; j > 0; j -= j &-j) sum += bit[j];
		for(; i > 0; i -= i&-i) sum -= bit[i];

		return sum;
	}

	int dfs(int no, int pai){
		rng[no] = mp(prt, prt);
		prt++;

		rep(i, adj[no].size()){
			int nt = adj[no][i];
			if(nt == pai) continue;
			rng[no].sd = max(rng[no].sd, dfs(nt, no));
		}

		return rng[no].sd;
	}

	void init(){
		prt = 0;
		memset(bit, 0, sizeof bit);
		dfs(0, -1);
	}

};

void bfs(){
	memset(H, -1, sizeof H);
	int ini = 0, fim = 1;
	H[0] = fila[0] = 0;
	pai[0] = -1;

	while(ini < fim){
		int at = fila[ini++];

		rep(i, adj[at].size()){
			int nt = adj[at][i];
			if(H[nt] != -1) continue;
			H[nt] = H[at] + 1;
			fila[fim++] = nt;
			pai[nt] = at;
		}
	}

	int i = 0;
	while(i < fim){
		int j = i;
		while(j < fim && H[fila[j]] == H[fila[i]]) ++j;
		fr(k, i, j) idx[fila[k]] = k - i;

		trees[H[fila[i]]].init(fila+i, j-i);

		i = j;
	}
}

void dfs(int no, int p = -1){
	rep(i, LG) desc[no][i] = mp(n, -1);

	rep(i, adj[no].size()){
		int nt = adj[no][i];
		if(nt == p) continue;
		dfs(nt, no);

		desc[no][0] = cmpPair(desc[no][0], mp(idx[nt], idx[nt]));
		rep(j, LG-1) desc[no][j+1] = cmpPair(desc[no][j+1], desc[nt][j]);
	}
}

bool applyBombEffect(int lvl, int power, pii range){
	pii done = indef;
	if(mk[lvl] == step) done = lim[lvl];

	if(done == indef) trees[lvl].decr(range.ft, range.sd, power);
	else{
		trees[lvl].decr(range.ft, done.ft-1, power);
		trees[lvl].decr(done.sd+1, range.sd, power);
	}

	while(1){
		pii least = trees[lvl].getMin(range.ft, range.sd);
		if(least == indef || least.ft > 0) break;

		trees[lvl].extractMin(least.sd);
		KillingTrack::update(trees[lvl].original[least.sd]);
	}

	mk[lvl] = step;
	lim[lvl] = range;

	return range != done;
}

void goDown(int no, int power){
	applyBombEffect(H[no], power, mp(idx[no], idx[no]));

	for(int j = 0, p = power >> 1; j < LG && p; ++j, p >>= 1){
		if(desc[no][j].sd == -1) break;

		if(!applyBombEffect(H[no]+j+1, p, desc[no][j])) break;
	}
}

void bombCity(int no, int power){
	++step;
	goDown(no, power);
	for(int at = pai[no], p = power >> 1; at != -1 && p; at = pai[at], p >>= 1)
		goDown(at, p);
}

int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%d", W + i);

	rep(i, n-1){
		int u, v;
		scanf("%d%d", &u, &v);
		--u, --v;
		adj[u].pb(v), adj[v].pb(u);
	}

	bfs();
	dfs(0);
	int q;
	scanf("%d", &q);
	step = 0;
	
	KillingTrack::init();
	
	while(q--){
		int t, a, x;
		scanf("%d%d", &t, &a);
		--a;
		if(t == 1){
			scanf("%d", &x);
			bombCity(a, x);
		}else printf("%d\n", KillingTrack::getQtd(a));
		
	}
}



