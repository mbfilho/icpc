#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

struct no{
	int adj[26], fail, pd;
	bool final;
	
	void init(){
		memset(adj, -1, sizeof adj);
		fail = pd = 0;
		final = false;
	}
	
	int& operator[](const int a){
		return adj[a];
	}
}nos[1001000];
int prt;


void insert(char* text){
	int at = 0;
	
	for(int i = 0; text[i]; ++i){
		if(nos[at][text[i] - 'a'] == -1){
			nos[prt].init();
			nos[at][text[i]-'a'] = prt++;
		}
		at = nos[at][text[i]-'a'];
	}
	
	nos[at].final = true;
}

int fila[1001000];

int falha(){
	int ini = 0, fim = 0;
	int best = 1;
	
	rep(i, 26){
		if(~nos[0][i]){
			nos[ nos[0][i] ].pd = nos[ nos[0][i] ].final;
			fila[fim++] = nos[0][i];
		}
	}
	
	while(ini < fim){
		int at = fila[ini++];
		rep(i, 26){
			int nt = nos[at][i];
			if(~nt){
				int fail = nos[at].fail;
				while(fail && nos[fail][i] == -1) fail = nos[fail].fail;
				if(~nos[fail][i]) fail = nos[fail][i];
				nos[nt].fail = fail;
				nos[nt].pd = nos[nt].final + max(nos[at].pd, nos[fail].pd);
				best = max(best, nos[nt].pd);
				fila[fim++] = nt;
			}
		}
	}
	
	return best;
}

char buf[1000000];
int n;

int main(){
	while(scanf("%d", &n) == 1 && n){
		nos[0].init();
		prt = 1;
		
		rep(i, n){
			scanf("%s", buf);
			insert(buf);
		}
		
		int best = falha();
		printf("%d\n", best);
		
	}	
}




