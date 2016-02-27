#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define T 1500100
#define begin laksdfj
#define end askdjf

struct Lazy{
	ll value, op;
	void set(ll v, ll o){ value = v, op = o; }
};

int stack[T], begin[T], end[T], cnt;

struct Treap{
	int L[T], R[T], X[T], Y[T], Pai[T], dummyCnt[T], prt, root;
	bool dummy[T];
	ll value[T];
	Lazy sum[T];

	Treap(){
		prt = 1;
		root = 0;
		L[0] = R[0] = X[0] = Y[0] = 0;
	}

	void fix(int no){
		if(!no) return;
		if(L[no]) sum[L[no]].op += sum[no].op;
		if(R[no]) sum[R[no]].op += sum[no].op;	

		if(!dummy[no]) value[no] += sum[no].op;

		sum[no].value += (X[no] - dummyCnt[no]) * sum[no].op;
		sum[no].op = 0;
	}

	void update(int no){
		if(!no) return;
		fix(L[no]), fix(R[no]);
		if(L[no]) Pai[L[no]] = no;
		if(R[no]) Pai[R[no]] = no;

		sum[no].value = sum[L[no]].value + sum[R[no]].value + value[no];
		dummyCnt[no] = dummyCnt[L[no]] + dummyCnt[R[no]] + dummy[no];
		X[no] = 1 + X[L[no]] + X[R[no]];
	}

	int merge(int l, int r){
		fix(l), fix(r);
		if(!l) return r;
		if(!r) return l;

		if(Y[l] < Y[r]){ R[l] = merge(R[l], r); update(l); return l; }
		else{ L[r] = merge(l, L[r]); update(r); return r; }
	}

	void split(int no, int& l, int& r, int v){
		fix(no);

		if(!no) Pai[l] = Pai[r] = 0, l = r = 0;
		else{
			int c = X[L[no]] + 1;
			if(v >= c) l = no, split(R[no], R[l], r, v - c);
			else r = no, split(L[no], l, L[r], v);
		}
		update(no);
	}

	int createNode(ll val, bool isDummy){
		int no = prt++;
		R[no] = L[no] = Pai[no] = 0;
		sum[no].value = val;
		value[no] = val;
		X[no] = 1, Y[no] = rand(), dummy[no] = isDummy, dummyCnt[no] = dummy[no];

		return no;
	}

	pii addChild(int idx, ll value){
		int l = 0, mid = 0, r = 0;
		split(root, l, r, idx-1);
		int bg = createNode(value, false);
		int end = createNode(0, true);

		l = merge(l, bg);
		l = merge(l, end);
		root = merge(l, r);

		return mp(bg, end);
	}

	void removeSubtree(int ini, int fim){
		int l = 0, mid = 0, r = 0;
		split(root, l, r, fim);
		split(l, l, mid, ini-1);
		root = merge(l, r);
	}

	void incrSubtree(int ini, int fim, ll val){
		int l = 0, mid = 0, r = 0;
		split(root, l, r, fim);
		split(l, l, mid, ini-1);
		sum[mid].op += val;
		l = merge(l, mid);
		root = merge(l, r);
	}

	ll getSum(int ini, int fim){
		int l = 0, mid = 0, r = 0;
		split(root, l, r, fim);
		split(l, l, mid, ini-1);
		ll ans = sum[mid].value;
		l = merge(l, mid);
		root = merge(l, r);

		return ans;
	}

	void fixToRoot(int no){
		int sp = 0;
		while(Pai[no]) stack[sp++] = no, no = Pai[no];
		while(sp--) fix(stack[sp]);
	}

	int getIndex(int no){
		fixToRoot(no);
		int pos = 0, soma = 1;

		while(no){
			if(soma) pos += X[L[no]] + 1;

			if(R[Pai[no]] == no) soma = true;
			else soma = false;
			no = Pai[no];
		}

		return pos;
	}


}treap;

void appendChild(int p, ll value){
	int parentIndex = treap.getIndex(begin[p]);
	pii index = treap.addChild(parentIndex+1, value);
	begin[cnt] = index.ft, end[cnt++] = index.sd;
}

void addValueToSubtree(int A, ll value){
	int ini = treap.getIndex(begin[A]), fim = treap.getIndex(end[A]);
	// while(ini > fim || ini <= 0);
	treap.incrSubtree(ini, fim, value);
}

void removeSubtree(int A){
	int ini = treap.getIndex(begin[A]), fim = treap.getIndex(end[A]);
	// while(ini > fim || ini <= 0);
	treap.removeSubtree(ini, fim);
}

ll getSum(int A){
	int ini = treap.getIndex(begin[A]), fim = treap.getIndex(end[A]);
	// while(ini > fim || ini <= 0);
	// printf("> %d %d\n", ini, fim);
	return treap.getSum(ini, fim);
}

vector<int> adj[T];

void preOrder(){
	int sp = 1;
	stack[0] = 1;

	while(sp--){
		int cur = stack[sp];
		if(cur > 0){
			treap.root = treap.merge(treap.root, begin[cur]);
			stack[sp++] = -cur;
			_(SIZE(adj[cur])) stack[sp++] = adj[cur][i];
		}else{
			treap.root = treap.merge(treap.root, end[-cur]);
		}
	}
}
// 
int main(){
	srand(10);
	cnt = 1;

	int n;
	scanf("%d", &n);

	_(n){
		int value;
		scanf("%d", &value);
		begin[i+1] = treap.createNode(value, false);
		end[i+1] = treap.createNode(0, true);
		++cnt;
	}

	_(n-1){
		int u, v;
		scanf("%d%d" ,&u, &v);
		adj[u+1].pb(v+1);
	}

	// dfs(1);
	preOrder();

	int m;
	ll SPECIAL = 0;
	scanf("%d", &m);

	while(m--){
		int type;
		scanf("%d", &type);
		
		// SPECIAL = 0;

		if(type == 1 || type == 2){
			ll node, value;
			scanf("%lld%lld", &node, &value);
			node += SPECIAL + 1;
			// while(node <= 0);
			type == 1 ? appendChild(node, value) : addValueToSubtree(node, value);
		}else{
			ll node;
			scanf("%lld", &node);
			node += 1 + SPECIAL;
			// while(node <= 0);

			if(type == 3) removeSubtree(node);
			else{
				SPECIAL = getSum(node);
				// printf(">>>> SIZE :: %d\n", linkTree.getSize(node));
				printf("%lld\n", SPECIAL);
			}
		}
	}
}
