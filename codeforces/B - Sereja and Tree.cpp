#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <cmath>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define pb push_back
typedef pair<int,int> pii;
#define mp make_pair

struct S{
	int l, r, x;
};
vector<S> tree[8000];
int mk[1000100], step, ans;
int  n;

pii expand(int v){
	int inc = 0;
	if(v > 1){
		while((1<<inc) < v) ++inc;
	}
	int bef = (v-1) + inc;
	pii at = mp(bef+1, bef+1);
	if(!(v & (v-1))) at.second = (bef+2);
	return at;
}

void answer(int lvl, int v){
	pii at = mp(v,v);
	
	while(lvl <= n){
		pii next = mp(expand(at.first).first, expand(at.second).second);
		
		for(int i = 0; i < tree[lvl].size(); ++i){
			int l = tree[lvl][i].l, r = tree[lvl][i].r, x = tree[lvl][i].x;
			if(at.first > r || at.second < l) continue;
			
			if(mk[x] != step) ++ans, mk[x] = step;
		}
		at = next;
		++lvl;
	}
}

void process(){
	int m;	
	scanf("%d%d", &n, &m);
	step = 0;
		
	rep(i, m){
		int type, t, l, r, c, v, x;
		scanf("%d", &type);
		if(type == 1) scanf("%d %d %d %d", &t, &l, &r, &x), tree[t].pb((S) {l, r, x});
		else scanf("%d %d", &t, &v), ans = 0, ++step, answer(t, v), printf("%d\n", ans);
	}
}

int main(){
	process();
}

