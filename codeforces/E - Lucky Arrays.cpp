#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;
#define MOD 777777777
typedef pair<int,int> pii;
#define X first
#define Y second
#define mp make_pair
#define N 77797
#define T (2*N)

int esq[T], dir[T];
int qtd[T][3][3];
int cont;
int value[N];
bool good[3][3];

void update(int no, int x, int y){
	if(x == y){
		if(~value[x]){
			rep(i, 3) rep(j, 3) qtd[no][i][j] = 0;
			qtd[no][value[x]][value[x]] = 1;
		}else
			rep(i, 3) qtd[no][i][i] = 1;
	}else{
		rep(i, 3) rep(j, 3) qtd[no][i][j] = 0;	
		int mid = (x+y)/2;
		
		rep(i, 3){
			rep(j, 3){
				rep(k, 3){
					rep(q, 3){
						if(good[k][q]){
							ll inc = ll(qtd[esq[no]][i][k]) * ll(qtd[dir[no]][q][j]) % MOD;
							qtd[no][i][j] = (qtd[no][i][j] + int(inc)) % MOD;
						}
					}
				}
			}
		}
	}
}

int build(int no, int x, int y){
	rep(i, 3) rep(j, 3) qtd[no][i][j] = 0;
	if(x != y){
		int mid = (x+y)/2;
		esq[no] = build(cont++, x, mid);
		dir[no] = build(cont++, mid+1, y);
	}else
		esq[no] = dir[no] = -1;
		
	update(no, x, y);
	return no;
}

void setar(int no, int x, int y, int ind, int val){
	if(ind > y || ind < x) return;
	
	if(x == y && x == ind) value[ind] = val;
	else{
		int mid = (x+y)/2;
		setar(esq[no], x, mid, ind, val);
		setar(dir[no], mid+1, y, ind, val);
	}
	
	update(no, x, y);
}

int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	
	rep(i, 3){
		rep(j, 3){
			int tmp;
			scanf("%d", &tmp);
			good[i][j] = tmp == 1;
		}
	}
	rep(i, n) value[i] = -1;
	cont = 0;
	build(cont++, 0, n-1);
	
	while(q--){
		int v, t;
		scanf("%d%d", &v, &t);
		--v; --t;
		setar(0, 0, n-1, v, t);
		int resp = 0;
		rep(i, 3){
//			if((~value[0]) && value[0] != i) continue;
			rep(j, 3){
//				if((~value[n-1]) && value[n-1] != j) continue;
				resp = (resp + qtd[0][i][j]) % MOD;
			}
		}
		
		printf("%d\n", resp);
	}
}



