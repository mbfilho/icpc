#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 1000010
#define T 2*N
typedef pair<int,int> pii;
#define mp make_pair
#define OP first
#define VAL second
#define mp  make_pair
#define oo 2000000000

int r, c;

struct Tree{
	int esq[T], dir[T], soma[T], maior[T], menor[T];
	bool setar[T], incr[T];
	int sVal[T], iVal[T];
	int prt;
	
	void init(int c){
		prt = 0;		
		rep(no, 2*c){
			esq[no] = dir[no] = -1;
			maior[no] = menor[no] = soma[no] = 0;
			setar[no] = incr[no] = false;
		}
		
		build(0, c-1);
	}
	
	int build(int ini, int fim){
		int no = prt++;
		
		if(ini != fim){
			int mid = (ini+fim)/2;
			esq[no] = build(ini, mid);
			dir[no] = build(mid+1, fim);
		}
		return no;
	}
	
	void insert(int no, pii tmp){
		if(tmp.OP == 2){
			setar[no] = true;
			incr[no] = false;
			sVal[no] = tmp.second;
		}else{
			if(incr[no]){
				iVal[no] += tmp.second;
			}else{
				incr[no] = true;
				iVal[no] = tmp.second;
			}
		}
	}

	void ajeitar(int no, int size){
		int e = esq[no], d = dir[no];
		if(setar[no]){
			soma[no] = size * sVal[no];
			maior[no] = menor[no] = sVal[no];
		
			if(~e){
				insert(e, mp(2, sVal[no]));
				insert(d, mp(2, sVal[no]));
			}
		}
		if(incr[no]){
			soma[no] += size * iVal[no];
			maior[no] += iVal[no];
			menor[no] += iVal[no];
			
			if(~e){
				insert(e, mp(1, iVal[no]));
				insert(d, mp(1, iVal[no]));
			}
		}
		setar[no] = incr[no] = false;
	}
	
	void update(int no){
		int e = esq[no], d = dir[no];
		soma[no] = soma[e] + soma[d];
		menor[no] = min(menor[e], menor[d]);
		maior[no] = max(maior[e], maior[d]);
	}

	void doOp(int no, int ini, int fim, int x, int y, pii op){
		ajeitar(no, fim - ini + 1);
		
		if(x > fim || y < ini) return;
		
		if(x <= ini && y >= fim){
			insert(no, op);
			ajeitar(no, fim - ini + 1);
		}else{
			int mid = (ini+fim)/2;
			doOp(esq[no], ini, mid, x, y, op);
			doOp(dir[no], mid+1, fim, x, y, op);
			update(no);
		}
	}

	void query(int no, int ini, int fim, int x, int y, int& sum, int& mai, int& men){
		if(x > fim || y < ini) return;
		ajeitar(no, fim - ini + 1);
		if(x <= ini && y >= fim){
			sum += soma[no];
			mai = max(mai, maior[no]);
			men = min(men, menor[no]);
		}else{
			int mid = (ini+fim)/2;
			query(esq[no], ini, mid, x, y, sum, mai, men);
			query(dir[no], mid+1, fim, x, y, sum, mai, men);
		}
	}
}nos[20];

int main(){
	int m;
	int h = 0;
	while(scanf("%d%d%d", &r, &c, &m) == 3){
		rep(i, r) nos[i].init(c);
		
		rep(i, m){
			int op, x[2], y[2];
			scanf("%d%d%d%d%d", &op, &x[0], &y[0], &x[1], &y[1]);
			--x[0];
			--y[0]; --y[1];
			
			if(op == 1){
				int val;
				scanf("%d", &val);
				fr(k, x[0], x[1]) nos[k].doOp(0, 0, c-1, y[0], y[1], mp(1, val));
			}else if(op == 2){
				int val;
				scanf("%d", &val);
				fr(k, x[0], x[1]) nos[k].doOp(0, 0, c-1, y[0], y[1], mp(2, val));
			}else{
				int sum = 0, mai = -oo, men = oo;
				fr(k, x[0], x[1])
					nos[k].query(0, 0, c-1, y[0], y[1], sum, mai, men);
				printf("%d %d %d\n", sum, men, mai);
			}
		}
	}
}




