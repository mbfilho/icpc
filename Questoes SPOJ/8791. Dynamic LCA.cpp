#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 100100

int esq[N], dir[N], pai[N];
bool root[N];

void init(int no, int p){
	esq[no] = dir[no] = 0;
	pai[no] = p;
	root[no] = true;
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
		esq[g] == p ? esq[g] = no : dir[g] = no;
	}
	pai[no] = pai[p];
	pai[p] = no;
	root[no] = root[p];
	root[p] = false;
}

void splay(int no){
	while(!root[no]){
		int p = pai[no];
		if(root[p]) rotate(no);
		else{
			int g = pai[p];
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

void cut(int no){
	access(no);
	root[esq[no]] = true;
	pai[esq[no]] = 0;
	esq[no] = 0;
}

//a eh raiz
void link(int a, int p){
	access(a), access(p);
	pai[a] = p;
}

int lca(int a, int b){
	if(a == b) return a;
	access(a);
	splay(b);
	if(!root[a]) return b;

	root[dir[b]] = true;
	dir[b] = 0;
	
	while(pai[b]){
		int p = pai[b];
		splay(p);
		if(p == a || !root[a]) return p;
		root[dir[p]] = true;
		dir[p] = b;
		root[b] = false;
		splay(b);
	}
	
	throw 1;
}

int main(){
	int n, q;
	scanf("%d%d", &n, &q);
	rep(i, n+1) init(i, 0);
	
	char op[20];
	while(q--){
		scanf("%s", op);
//		printf("> %s\n", op);
		if(!strcmp(op, "link")){
			int a, b;
			scanf("%d%d", &a, &b);
			link(a, b);
		}else if(op[0] == 'l'){
			int a, b;
			scanf("%d%d", &a, &b);
			printf("%d\n", lca(a,b));
		}else{
			int a;
			scanf("%d", &a);
			cut(a);
		}
	}
}



