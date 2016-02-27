#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 100100
//DYNACON1

int pai[N], esq[N], dir[N];
bool flip[N], root[N];
int n;

void init(int no){
	pai[no] = esq[no] = dir[no] = 0;
	flip[no] = false;
	root[no] = true;
}

void fix(int no){
	if(!no) return;
	
	if(flip[no]){
		swap(esq[no], dir[no]);
		flip[esq[no]] = !flip[esq[no]];
		flip[dir[no]] = !flip[dir[no]];
		flip[no] = false;
	}
}

void rotate(int no){
	int p = pai[no];
	
	if(esq[p] == no){
		esq[p] = dir[no];
		pai[dir[no]] = p;
		dir[no] = p;
	}else{
		dir[p] = esq[no];
		pai[esq[no]] = p;
		esq[no] = p;
	}
	
	if(!root[p]){
		int g = pai[p];
		dir[g] == p ? dir[g] = no : esq[g] = no;
	}
	
	root[no] = root[p];
	root[p] = false;
	pai[no] = pai[p];
	pai[p] = no;
}

void splay(int no){
	fix(no);
	
	while(!root[no]){
		int p = pai[no];
		
		if(root[p]) fix(p), fix(no), rotate(no);
		else{
			int g = pai[p];
			fix(g), fix(p), fix(no);
			if((esq[g] == p && esq[p] == no) || (dir[g] == p && dir[p] == no)) rotate(p), rotate(no);
			else rotate(no), rotate(no);
		}
	}
}

void access(int no){
	splay(no);
	root[dir[no]] = true;
	dir[no] = 0;
	
	while(pai[no]){
		int p = pai[no];
		splay(p);
		root[dir[p]] = true;
		dir[p] = no;
		root[no] = false;
		splay(no);
	}
}

void remove(int a, int b){
	access(a);
	splay(b);
	if(pai[a]) swap(a,b);
	//b esta em baixo
	access(b);
	pai[esq[b]] = 0;
	root[esq[b]] = true;
	esq[b] = 0;
}

void makeRoot(int no){
	access(no);
	flip[no] = true;
	fix(no);
	access(no);
}

void add(int a, int b){
	makeRoot(b);
	access(a);
	pai[b] = a;
}

bool connected(int a, int b){
	access(a);
	access(b);
	
	if(pai[a]) return true;
	return false;
}

int main(){
	int q;
	while(scanf("%d%d", &n, &q) == 2){
		rep(i, n+1) init(i);
		
		char op[20];
		int u, v;
		while(q--){
			scanf("%s%d%d", op, &u, &v);
			
			if(op[0] == 'a') add(u,v);
			else if(op[0] == 'r') remove(u,v);
			else{
				if(connected(u,v)) printf("YES\n");
				else printf("NO\n");
			}
		}
	}
}








