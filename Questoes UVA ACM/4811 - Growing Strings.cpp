
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define TRIE 1000100
#define N 2001

struct no{
	int adj[26];
	int fail;
	int pd;
	bool final;
	
	int& operator[](const char& a){
		return adj[a-'a'];
	}
	
	void init(){
		memset(adj, -1, sizeof adj);
		fail = 0;
		final = false;
		pd = 0;
	}
}nos[TRIE];
int prt;

void insert(char* tmp){
	int root = 0;
	
	for(int i = 0; tmp[i]; ++i){
		if(nos[root][tmp[i]] == -1){
			nos[prt].init();
			nos[root][tmp[i]] = prt++;
		}
		root = nos[root][tmp[i]];
	}
	
	nos[root].final = true;
	++nos[root].pd;
}

int fila[TRIE];
int best;
void build(){
	int ini = 0, fim = 0;
	
	rep(i, 26){
		if(nos[0].adj[i] != -1)
			fila[fim++] = nos[0].adj[i];
	}
	
	while(ini < fim){
		int root = fila[ini++];
		
		rep(i, 26){
			int nt = nos[root].adj[i];

			if(~nt){
				nos[nt].pd = nos[nt].final + nos[root].pd;
				
				int fail = nos[root].fail;
				
				while(fail && nos[fail].adj[i] == -1){
					fail = nos[fail].fail;
				}
				
				if(nos[fail].adj[i] != -1) 
					fail = nos[fail].adj[i];
				nos[nt].fail = fail;
				nos[nt].pd = max(nos[nt].pd, nos[nt].final + nos[fail].pd);
				best = max(best, nos[nt].pd);
				fila[fim++] = nt;
			}
		}
	}
}

int n;
char buf[10000];
int main(){
	cin.sync_with_stdio(false);
	cout.sync_with_stdio(false);
	
	while(cin >> n && n){
		prt = 1;
		nos[0].init();
		
		rep(i, n){
			cin >> buf;
			insert(buf);
		}
		
		best = 1;
		build();
		cout << best << endl;
	}
}


