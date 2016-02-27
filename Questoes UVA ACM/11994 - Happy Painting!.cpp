#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define T 100100

int esq[T], dir[T], pai[T];
bool root[T];
int op[T], minha[T], color[T], size[T];
int prt;

void init(int no, int cor){
	esq[no] = dir[no] = 0;
	root[no] = true;
	op[no] = 0;
	minha[no] = color[no] = cor;
	size[no] = 1;
}

void fix(int no){
	if(!no) return;
	
	if(op[no]){
		if(esq[no]) op[esq[no]] = op[no];
		if(dir[no]) op[dir[no]] = op[no];
		
		minha[no] = color[no] = op[no];
		op[no] = 0;
	}
}

void update(int no){
	if(!no) return;
	
	color[no] = minha[no];
	size[no] = 1;

	if(dir[no]) fix(dir[no]), color[no] |= color[dir[no]], size[no] += size[dir[no]];
	if(esq[no]) fix(esq[no]), color[no] |= color[esq[no]], size[no] += size[esq[no]];
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
		if(esq[g] == p)	esq[g] = no;
		else dir[g] = no;
	}
	
	pai[no] = pai[p];
	pai[p] = no;
	root[no] = root[p];
	root[p] = false;
	
	update(p);
	update(no);
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
	update(no);
	
	while(pai[no]){
		int p = pai[no];
		splay(p);
		root[dir[p]] = true;
		dir[p] = no;
		update(p);
		
		root[no] = false;
		splay(no);
	}
}

void paint(int x, int y, int cor){
	if(x == y) return;
	access(x);
	
	splay(y);
	if(!root[x]){//lca eh y
		op[dir[y]] = cor;
	}else{
		bool achou = false;
		root[dir[y]] = true;
		dir[y] = 0;
		update(y);
		
		while(pai[y]){
			int p = pai[y];
			splay(p);
			
			if(!achou && (!root[x] || p == x)){ //lca = p
				op[dir[p]] = cor;
				op[y] = cor;
				achou = true;
				fix(y);
			}
			
			root[dir[p]] = true;
			dir[p] = y;
			update(p);
			root[y] = false;
			splay(y);
		}
	}	
}

void cut(int no){
	access(no);
	root[esq[no]] = true;
	pai[esq[no]] = 0;
	esq[no] = 0;
	update(no);
}

void trocar(int x, int y, int cor){
	if(x == y) return;
	access(y);
	splay(x);
	
	if(!root[y]) return;
	cut(x);
//	printf("X %d Size %d Mask %d %d %d\n", x, size[x], color[x], esq[x], dir[x]);
	pai[x] = y;
	minha[x] = color[x] = cor;
}

int contar(int mask){
	int c = 0;
	while(mask){
		if(mask & 1) ++c;
		++c;
		mask -= mask & -mask;
	}
	
	return c;
}

void count(int x, int y){

	int s = -1, mask;
	access(x);
	
	splay(y);
	if(!root[x]){//lca eh y
		s = size[dir[y]], mask = color[dir[y]];
	}else{
		root[dir[y]] = true;
		dir[y] = 0;
		update(y);
		
		while(pai[y]){
			int p = pai[y];
			splay(p);
			
			if(s == -1 && (!root[x] || x == p)){ //lca eh p
				s = size[dir[p]] + size[y];
				mask = color[dir[p]] | color[y];
			}
			
			root[dir[p]] = true;
			dir[p] = y;
			update(p);
			root[y] = false;
			splay(y);
		}
	}
	if(s == -1) s = mask = 0;
	printf("%d %d\n", s, contar(mask));
}

int pot[32];
int main(){
	prt = 1;
	int n;
	rep(i, 32) pot[i] = 1<<i;
	
	int q;
	while(scanf("%d%d", &n, &q) == 2){
		rep(i, n)
			scanf("%d", &pai[i+1]);
		
		rep(i,n){
			int c;
			scanf("%d", &c);
			
			if(pai[i+1]) c = pot[c];
			else c = 0;
			
			init(i+1, c);
		}
		
		int op;
		while(q--){
			int x, y;
			if(scanf("%d %d %d", &op, &x, &y) != 3) break;
			if(op == 1){
				int c;
				scanf("%d", &c);
				trocar(x, y, pot[c]);
			}else if(op == 2){
				int c;
				scanf("%d", &c);
				paint(x,y,pot[c]);
			}else{
				count(x,y);
			}
		}
	}	
}






