#include <cstdio>
#include <cstring>
#include <algorithm>
#include <ctime>
using namespace std;
typedef unsigned int hash;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,b) Fr(i,0,n)
#define B 1095

#define L 210000
#define Q 260000

hash pot[L+Q];

struct No{
	int c, y;
	int esq, dir;
	hash soma;
	char ch;
	
	void set(int val, char chh){
		c = val;
		esq = dir = -1;
		y = rand();
		ch = chh-'a'+1;
		soma = 0;
	}
}nos[L+Q];

void ajeitar(int no){
	int esq = 0, dir = 0;
	nos[no].soma = 0;
	hash somae = 0, somadir = 0;
		
	if(~nos[no].esq){
		esq = nos[nos[no].esq].c;
		somae = nos[nos[no].esq].soma;
	}
	if(~nos[no].dir){
		somadir = nos[nos[no].dir].soma;
		dir = nos[nos[no].dir].c;
	}
	
	nos[no].soma = somae;
	nos[no].soma += pot[esq] * nos[no].ch;
	nos[no].soma += pot[esq+1]*somadir;
	nos[no].c = esq + 1 + dir;
}

int merge(int esq, int dir){
	if(esq == -1) return dir;
	if(dir == -1) return esq;
	
	if(nos[esq].y > nos[dir].y){
		nos[dir].esq = merge(esq, nos[dir].esq);
		ajeitar(dir);
		return dir;
	}else{
		nos[esq].dir = merge(nos[esq].dir, dir);
		ajeitar(esq);
		return esq;
	}
}

void split(int no, int& esq, int& dir, int val){
	if(no == -1){
		esq = dir = -1;
	}else{
		if(!val){
			esq = -1;
			dir = no;
			return;
		}
		int cont = 1;
		if(~nos[no].esq)
			cont = nos[nos[no].esq].c + 1;
		
		if(val < cont){
			split(nos[no].esq, esq, nos[no].esq, val);
			dir = no;
			ajeitar(no);
		}else if(val == cont){
			esq = no;
			dir = nos[no].dir;
			nos[no].dir = -1;
			ajeitar(no);
		}else{
			split(nos[no].dir, nos[no].dir, dir, val - cont);
			ajeitar(no);
			esq = no;
		}
	}
}

int add(int no, int nw){
	if(no == -1 || nos[nw].y < nos[no].y){
		split(no, nos[nw].esq, nos[nw].dir, nos[nw].c);
		ajeitar(nw);
		return nw;
	}
	int cont = 1;
	if(~nos[no].esq)
		cont = nos[nos[no].esq].c + 1;
	
	if(nos[nw].c < cont){
		nos[no].esq = add(nos[no].esq, nw);
	}else{
		nos[nw].c -= cont;
		nos[no].dir = add(nos[no].dir, nw);
	}
	
	ajeitar(no);
	return no;
}

char str[L];
/*
void print(int no, int pad=0){
	if(no == -1)
		return;
	
	print(nos[no].esq, pad+1);
	printf( "%c\n", nos[no].ch);
	print(nos[no].dir, pad+1);;
}
*/
int main(){
	int t;
	scanf("%d", &t);
	srand(time(0));
	pot[0] = 1;
	Fr(i, 1, Q+L) pot[i] = pot[i-1]*B;
	
	while(t--){
		scanf("%s", str);
		int l = 0;
		int root = -1, prt = 0;
		for(int i = 0; str[i]; ++i){
			nos[prt].set(prt+1, str[i]);
			++l;
			while(str[i] >= 'A' && str[i] <= 'Z') throw 1;
			root = add(root, prt);
			++prt;
		}
		
		int q;
		scanf("%d", &q);
		char buf[30];
		while(q--){
			scanf("%s", buf);
			
			if(buf[0] == 'Q'){
				int a, b;
				scanf("%d%d", &a, &b);
				int ini = 1, fim = prt+10;
				int best = 0;
				
				while(ini <= fim){
					int meio = (ini+fim)/2;
					if(max(a,b) + meio - 1 > prt){
						fim = meio - 1;
						continue;
					}
					
					int m[] = {-1,-1,-1};

					hash h[] = {0,0};
					
					split(root, m[0], m[1], a-1);
					split(m[1], m[1], m[2], meio);
					h[0] = nos[m[1]].soma;

					root = merge(m[0], m[1]);
					root = merge(root, m[2]);
					
					m[0] = m[1] = m[2] = -1;
					split(root, m[0], m[1], b-1);
					split(m[1], m[1], m[2], meio);
					h[1] = nos[m[1]].soma;

					root = merge(m[0], m[1]);
					root = merge(root, m[2]);

					if(h[0] == h[1]){
						best = meio;
						ini = meio + 1;
					}else
						fim = meio - 1;
				}
				
				printf("%d\n", best);				
				
			}else if(buf[0] == 'R'){
				int ind;
				scanf("%d%s", &ind, buf);
				
				int m[] = {-1,-1,-1};
				split(root, m[0], m[1], ind-1);
				split(m[1], m[1], m[2], 1);
				nos[m[1]].ch = buf[0]-'a'+1;
				ajeitar(m[1]);
				root = merge(m[0], m[1]);
				root = merge(root, m[2]);
			}else if(buf[0] == 'I'){
				int ind;;
				scanf("%d%s", &ind, buf);
				int m[] = {-1,-1};
				split(root, m[0], m[1], ind);
				nos[prt].set(ind+1, buf[0]);
				m[0] = add(m[0], prt);
				++prt;
				root = merge(m[0], m[1]);
			}else throw 2;
		}
	}
}





