#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
#define mp make_pair
typedef pair<int,int> pii;
#define ft first
#define sd second
#define LIM 100100

//Ver como outros fizeram!

int A[LIM];
vector<int> P;

void pre(){
	memset(A, -1, sizeof A);

	fr(i, 2, LIM){
		if(A[i] == -1){
			A[i] = P.size();
			P.pb(i);
		}

		rep(j, A[i]+1){
			ll tmp = i * ll(P[j]);
			if(tmp >= LIM) break;
			A[tmp] = j;
		}
	}
}

struct No{
	int begin, end;
	pii best;
	No *left, *right;
};
vector<No> trees[10000];
vector<pii> values[10000];
int prt;

pii maximiza(pii a, pii b){
	if(a.ft == b.ft) return mp(a.ft, a.sd+b.sd);
	return a < b ? b : a;
}

No* build(vector<pii>& val, vector<No>& tree, No* at, int x, int y){
	if(x == y) at->left = at->right = NULL, at->best = mp(val[x].ft,1), at->begin = at->end = val[x].sd;
	else{
		int mid = (x+y)>>1;
		at->left = build(val, tree, &tree[prt++], x, mid);
		at->right = build(val, tree, &tree[prt++], mid+1, y);
		at->begin = at->left->begin;
		at->end = at->right->end;
		at->best = maximiza(at->left->best, at->right->best);		
	}

	return at;
}

pii indef = mp(-1, 0);
int melhor_global;

pii query(No* root, int x, int y, int ini, int fim){
	if(fim < root->begin || ini > root->end) return indef;
	if(melhor_global > root->best.ft) return indef;

	if(ini <= root->begin && fim >= root->end){
		melhor_global = max(melhor_global, root->best.ft);
		return root->best;
	}else{
		int mid = (x+y)>>1;
		pii ans = maximiza(query(root->left, x, mid, ini, fim), query(root->right, mid+1, y, ini, fim));
		melhor_global = max(melhor_global, ans.ft);
		return ans;
	}
}

map<int,int> mapa;
int contTree, n;
int num[LIM];

int getTree(int p){
	if(mapa.find(p) == mapa.end()) mapa[p] = contTree++;
	return mapa[p];
}

void buildTrees(){
	contTree = 0;
	
	rep(i, n) if(num[i] != 1){
		int tmp = num[i];
		while(tmp != 1){
			// cout << tmp << " " << A[tmp] << endl;
			int p = P[A[tmp]], t = getTree(p);
			values[t].pb(mp(num[i], i));
			while(tmp % p == 0) tmp /= p;
		}
	}

	rep(i, contTree){
		// cout << "Tree" << i << endl;
		// rep(j, values[i].size()) cout << values[i][j].ft << endl;

		trees[i].resize(2*values[i].size()-1);
		prt = 0;
		build(values[i], trees[i], &trees[i][prt++], 0, values[i].size()-1);
	}
}


int main(){
	ios::sync_with_stdio(false);
	pre();
	int m;
	cin >> n >> m;
	rep(i, n) cin >> num[i];
	buildTrees();

	rep(i, m){
		int g, a, b;
		cin >> g >> a >> b;

		if(g == 1) cout << "-1 -1\n";
		else{
			melhor_global = -1;
			pii ans = indef;
			while(g != 1){
				int p = P[A[g]];
				int t = mapa.find(p) == mapa.end() ? -1 : mapa[p];
				
				if(~t){
					pii tmp = query(&trees[t][0], 0, trees[t].size()-1, a-1, b-1);
					ans = max(ans, tmp);
				}
				while(g % p == 0) g /= p;
			}

			if(ans.ft == -1) cout << "-1 -1\n";
			else cout << ans.ft << " " << ans.sd << endl;
		}
	}


}