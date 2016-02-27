#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 410000
#define B 13
typedef unsigned int H;

int esq[N], dir[N], y[N], cnt[N];
bool val[N];
H hash[N][2], pot[N];
bool inv[N];

void init(int no, int x, bool v){
	esq[no] = dir[no] = -1;
	cnt[no] = x;
	val[no] = v;
	hash[no][0] = hash[no][1] = v;
	inv[no] = false;
}

void ajeitar(int no){
	if(inv[no]){
		swap(hash[no][0], hash[no][1]);
		swap(esq[no], dir[no]);
		int e = esq[no], d = dir[no];
		if(~e) inv[e] = !inv[e];
		if(~d) inv[d] = !inv[d];
		
		inv[no] = false;
	}
}

void update(int no){
	int e = esq[no], d = dir[no];
	int se = 0, sd = 0;
	cnt[no] = 1;
	hash[no][0] = hash[no][1] = 0;
	H he[] = {0,0}, hd[] = {0,0};
	
	if(~e){ajeitar(e); cnt[no] += cnt[e]; se = cnt[e]; he[0] = hash[e][0]; he[1] = hash[e][1];}
	if(~d){ajeitar(d); cnt[no] += cnt[d]; sd = cnt[d]; hd[0] = hash[d][0]; hd[1] = hash[d][1];}
	
	hash[no][0] = (he[0] * B + val[no]) * pot[sd] + hd[0];
	hash[no][1] = (hd[1] * B + val[no]) * pot[se] + he[1];
}

void split(int root, int& L, int& R, int x){
	if(root == -1) L = R = -1;
	else{
		ajeitar(root);
		int c = 1 + (esq[root] == -1 ? 0 : cnt[esq[root]]);
		if(x > c){
			split(dir[root], dir[root], R, x - c);
			L = root;
		}else{
			split(esq[root], L, esq[root], x);
			R = root;
		}
		
		update(root);
	}
}

int merge(int L, int R){
	if(L == -1) return R;
	if(R == -1) return L;
	ajeitar(L); ajeitar(R);
	
	if(y[L] < y[R]){
		dir[L] = merge(dir[L], R);
		update(L);
		return L;
	}else{
		esq[R] = merge(L, esq[R]);
		update(R);
		return R;
	}
}

int add(int no, int nw){
	if(no == -1 || y[nw] < y[no]){
		split(no, esq[nw], dir[nw], cnt[nw]);
		update(nw);
		return nw;
	}
	ajeitar(no);
	
	int c = 1 + (esq[no] == -1 ? 0 : cnt[esq[no]]);
	if(cnt[nw] > c){
		cnt[nw] -= c;
		dir[no] = add(dir[no], nw);
	}else
		esq[no] = add(esq[no], nw);
	
	update(no);
	return no;
}

H get(int no, int x){
	H ha = 0;
	
	while(x){
		if(no == -1) return ha; //nao esperado =P
		ajeitar(no);
		int c = 1 + (esq[no] == -1 ? 0 : cnt[esq[no]]);
	
		if(x >= c){
			H e = 0;
		
			if(esq[no] != -1){
				ajeitar(esq[no]);
				e = hash[esq[no]][0];
			}
			ha += (e * B + val[no]) * pot[x-c];
			no = dir[no];
			x -= c;
		}else if(x < c){
			no = esq[no];
		}
	}
	
	return ha;
}

int root, prt;
H getHash(int i, int j){
	H todo = get(root, j);
	H parte = get(root, i-1);
	return todo - parte * pot[j-i+1];
}

char buf[N];
int main(){
	pot[0] = 1;
	fr(i, 1, N) pot[i] = B * pot[i-1];
	srand(12);
	rep(i, N) y[i] = rand() * rand();
	int n, m;
	while(scanf("%d%d", &n, &m) == 2){
		scanf("%s", buf);
		prt = 0;
		root = -1;
	
		rep(i, n){
			init(prt, i+1, buf[i] - '0');
			root = add(root, prt);
			++prt;
		}
		int len = n;
		
		while(m--){
			int op;
			scanf("%d", &op);
			if(op == 1){
				int p, c;
				scanf("%d %d", &p, &c);
				int e = -1, d = -1;
				split(root, e, d, p+1);
				init(prt, p+1, c);
				e = add(e, prt);
				++prt;
				root = merge(e, d);
				++len;
			}else if(op == 2){
				int p;
				scanf("%d", &p);
				int e = -1, d = -1;
				split(root, e, d, p);
				
				int ele = -1, nd = -1;
				split(d, ele, nd, 2); 
				root = merge(e, nd);
				--len;
			}else if(op == 3){
				int p1, p2;
				scanf("%d%d", &p1, &p2);
				int e = -1, d = -1, ne = -1, nd = -1;
				split(root, e, d, p2+1);
				split(e, ne, nd, p1);
				inv[nd] = !inv[nd];
				e = merge(ne, nd);
				root = merge(e, d);
			}else if(op == 4){
				int p1, p2;
				scanf("%d%d", &p1, &p2);
				
				int ini = 0, fim = min(len - p1, len - p2), best = 0;
				while(ini <= fim){
					int mid = (ini+fim)/2;
					H ha = getHash(p1, p1+mid), hb = getHash(p2, p2+mid);
					
					if(ha == hb)
						best = ini = mid + 1;
					else
						fim = mid - 1;
				}
				printf("%d\n", best);
			}
		}
	}
}





