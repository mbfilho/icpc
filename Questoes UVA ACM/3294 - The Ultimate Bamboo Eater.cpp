#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 120000
#define TREE 2*N

struct no{
	int l, w;
	int x[2], y[2];
	int esq, dir;
	int pd;
	
	void init(int xx, int yy){
		x[0] = x[1] = xx;
		y[0] = y[1] = yy;
		esq = dir = -1;
		pd = 0;
	}
	
	void set(int xx, int yy){
		x[0] = min(x[0], xx);
		x[1] = max(x[1], xx);
		y[0] = min(y[0], yy);
		y[1] = max(y[1], yy);
	}
}nos[TREE];
int prt;


no pts[N];

bool cmpX(no a, no b){
	return a.x[0] < b.x[0];
}

bool cmpY(no a, no b){
	return a.y[0] < b.y[0];
}

int build(int no, int ini, int fim, int q){
	int mid = (ini+fim)/2;
	nth_element(pts + ini, pts + mid, pts + fim + 1, q ? cmpX : cmpY);
	nos[no].init(pts[mid].x[0], pts[mid].y[0]);
	fr(i, ini, fim+1)
		nos[no].set(pts[i].x[0], pts[i].y[0]);
	
	if(ini != fim){
		nos[no].esq = build(prt++, ini, mid, 1-q);
		nos[no].dir = build(prt++, mid+1, fim,1-q);
	}
	
	return no;
}

int query(int no, int xi, int yi, int xf, int yf){
	if(no == -1) return 0;
	if(xf < nos[no].x[0] || xi > nos[no].x[1] || yf < nos[no].y[0] || yi > nos[no].y[1]) return 0;
	if(xi <= nos[no].x[0] && xf >= nos[no].x[1] && yi <= nos[no].y[0] && yf >= nos[no].y[1]) 
		return nos[no].pd;
	return max(query(nos[no].dir, xi, yi, xf, yf), query(nos[no].esq, xi, yi, xf, yf));
}

bool cmpW(int a, int b){
	return pts[a].w < pts[b].w;
}
int ord[N];


void atualiza(int root, int ini, int fim, int no, int val){
	nos[root].pd = max(nos[root].pd, val);
	if(ini != fim){
		int mid = (ini+fim)/2;
		if(no <= mid)
			atualiza(nos[root].esq, ini, mid, no, val);
		else
			atualiza(nos[root].dir, mid+1, fim, no, val);
	}
}

int main(){
	int t, n;
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	
	cin >> t;
	
	rep(cas, t){
		cin >> n;
		
		rep(i, n){
			ord[i] = i;
			cin >> pts[i].x[0] >> pts[i].y[0] >> pts[i].w >> pts[i].l;
			int x = pts[i].x[0] - pts[i].y[0];
			int y = pts[i].x[0] + pts[i].y[0];;
			pts[i].init(x,y);
		}
		prt = 0;
		int root = build(prt++, 0, n-1, 0);
		sort(ord, ord + n, cmpW);
		int best = 0;
		rep(i, n){
			no a = pts[ord[i]], b = pts[ord[i]];
			int k = query(root, a.x[0] - a.l, a.y[0] - a.l, a.x[0] + a.l, a.y[0] + a.l);
			best = max(best, 1 + k);
			atualiza(root, 0, n-1, ord[i], k+1);
		}
		
		cout << "Case " << (cas+1) << ": " << best << endl;
		
	}
}





