#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long ll;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
#define TREE (2*N)

int A[N];

struct tree{
	int esq[TREE], dir[TREE];
	int soma[TREE];
	bool op[TREE];
	int prt, pot;
	
	void init(int p, int n){
		prt = 0;
		pot = p;
		
		build(prt++, 0, n-1);
	}
	
	int build(int no, int ini, int fim){
		esq[no] = dir[no] = -1;
		op[no] = false;
		
		if(ini != fim){
			int mid = (ini+fim)/2;
			esq[no] = build(prt++, ini, mid);
			dir[no] = build(prt++, mid + 1, fim);
			
			soma[no] = soma[esq[no]] + soma[dir[no]];
		}else
			soma[no] = (A[ini] & pot) ? 1 : 0;
		return no;
	}
	
	void ajeitar(int no, int size){
		if(op[no]){
			op[no] = false;
			soma[no] = size - soma[no];
			op[esq[no]] = !op[esq[no]];
			op[dir[no]] = !op[dir[no]];
		}
	}
	
	void revert(int no, int ini, int fim, int x, int y){
		ajeitar(no, fim - ini + 1);
		
		if(x > fim || y < ini) return;
		if(x <= ini && y >= fim){
			op[no] = true;
			ajeitar(no, fim - ini + 1);
		}else{
			int mid = (ini+fim) / 2;
			
			revert(esq[no], ini, mid, x, y);
			revert(dir[no], mid + 1, fim, x, y);
			
			soma[no] = soma[esq[no]] + soma[dir[no]];
		}
	}
	
	int query(int no, int ini, int fim, int x, int y){
		ajeitar(no, fim - ini + 1);
		
		if(x > fim || y < ini) return 0;
		if(x <= ini && y >= fim)
			return soma[no];
		else{
			int mid = (ini+fim)/2;
			
			return query(esq[no], ini, mid, x, y) + query(dir[no], mid + 1, fim, x, y);
		}
	}
}nos[21];


int n;

int main(){
	cout.sync_with_stdio(false);
	scanf("%d", &n);
	
	rep(i, n) scanf("%d", A + i);	
	rep(i, 21) nos[i].init(1 << i, n);
	
	int q;
	scanf("%d", &q);
	while(q--){
		int t, l, r;
		scanf("%d%d%d", &t, &l, &r);
		if(t == 2){
			int x;
			scanf("%d", &x);
			int pot = 0;
			
			while(x){
				if(x&1) nos[pot].revert(0, 0, n-1, l-1, r-1);
				++pot;
				x >>= 1;
			}
		}else{
			ll pot = 1, soma = 0;
			
			rep(i, 21){
				soma += pot * nos[i].query(0, 0, n-1, l-1, r-1);
				pot *= 2;
			}
			
			cout << soma << endl;
		}
	}
}











