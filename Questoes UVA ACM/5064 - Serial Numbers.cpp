#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef long long ll;

struct no{
	int fail;
	int adj[10];
	bool match;
	
	void init(){
		memset(adj, -1, sizeof adj);
		match = false;
		fail = 0;
	}
	
	bool tem(int c){
		return adj[c] != -1;
	}
	
	int& operator[](const int& a){
		return adj[a];
	}
}nos[10000];
int prt;

int ncaso;
int cacheNext[200][10];
int next[200][10];

void insert(char* word){
	int at = 0;
	for(int i = 0; word[i]; ++i){
		if(nos[at].tem(word[i]-'0')){
			at = nos[at][word[i]-'0'];
		}else{
			nos[prt].init();
			nos[at][word[i]-'0'] = prt;
			at = prt++;
		}
	}
	nos[at].match = true;
}
void build(){
	queue<int> fila;
	rep(i, 10){
		if(nos[0].tem(i))
			fila.push(nos[0][i]);
	}
	while(!fila.empty()){
		int at = fila.front();
		fila.pop();
		rep(it, 10){
			if(!nos[at].tem(it)) continue;
			int fail = nos[at].fail;
			while(fail && !nos[fail].tem(it)) 
				fail = nos[fail].fail;	
			if(nos[fail].tem(it))
				fail = nos[fail][it];
			nos[ nos[at][it] ].fail = fail;
			nos[ nos[at][it] ].match |= nos[fail].match;
			fila.push(nos[at][it]);
		}
	}
}

int getNext(int no, int ch){
	if(cacheNext[no][ch] == ncaso) return next[no][ch];
	cacheNext[no][ch] = ncaso;
	
	int& nt = next[no][ch];
	nt = no;
	while(nt && !nos[nt].tem(ch)) nt = nos[nt].fail;
	if(nos[nt].tem(ch)) nt = nos[nt][ch];
	return nt;
}

ll pd[200][15];
int mk[200][15];

char num[100];
int tam;

ll rec(int no, int p, bool tight){
	if(nos[no].match) return 0;
	if(!num[p]) return 1;
	if(mk[no][tam-p] == ncaso && !tight) return pd[no][tam-p];
	
	ll total = 0;
	
	int st;
	if(!p){
		st = 1;
		for(int i = 1; num[i]; ++i){
			fr(k, 1, 10){
				int nt = getNext(0, k);
				total += rec(nt, i+1, false);
			}
		}
	}else
		st = 0;
		
	if(tight){
		fr(ch, st, num[p] - '0'){
			int nt = getNext(no, ch);
			total += rec(nt, p+1, false);
		}
		int nt = getNext(no, num[p] - '0');
		total += rec(nt, p+1, true);
	}else{
		fr(ch, st, 10){
			int nt = getNext(no, ch);
			total += rec(nt, p+1, false);
		}
	}
	
	if(!tight){
		mk[no][tam-p] = ncaso;
		pd[no][tam-p] = total;
	}
	return total;
} 


char buf[1000];
int main(){
	int t;
	scanf("%d", &t);
	memset(mk, 0, sizeof mk);
	memset(cacheNext, 0, sizeof cacheNext);
	ncaso = 0;
	while(t--){
		++ncaso;
		prt = 1;
		nos[0].init();

		int op;
		scanf("%d", &op);
		while(op--){
			scanf("%s", buf);
			insert(buf);
		}
		build();
		int k;
		scanf("%d", &k);
		while(k--){
			ll tmp;
			scanf("%lld", &tmp);
			ll ini = tmp, fim = 0x7fffffff;
			int resp = -1;
			
			while(ini <= fim){
				int meio = (ini+fim)/2;
				sprintf(num, "%d", meio);
				tam = strlen(num);
				ll qtd = rec(0, 0, true);
				
				if(qtd > tmp)
					fim = meio - 1;
				else if(qtd < tmp)
					ini = meio + 1;
				else{
					resp = meio;
					fim = meio - 1;
				}
			}
			if(k)
				printf("%d ", resp);
			else 
				printf("%d\n", resp);
		}
	}
}






