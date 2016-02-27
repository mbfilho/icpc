#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <string>
#include <iostream>
using namespace std;
#define CINCO 400000
#define QUATRO 20000
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

struct no{
	int adj[26], fail, pd;
	
	void init(int root){
		memset(adj, -1, sizeof adj);
		fail = root;
		pd = 0;
	}
	
	int& operator[](char ch){
		return adj[ch-'a'];
	}
}nos[CINCO];

int tries[1000];

int mapa[CINCO];
int end[QUATRO];

int prt;

void add(const int root, int ind, string& word){
	int tam = word.size();
	int at = root;
	rep(i, tam){
		if(nos[at][word[i]] == -1){
			nos[prt].init(root);
			nos[at][word[i]] = prt++;
		}
		

		at = nos[at][word[i]];
	}	
	
	end[ind] = at;
}

int fila[CINCO];
void falha(const int root){
	int ini = 0, fim = 0;
	rep(i, 26){
		if(nos[root][i+'a'] != -1)
			fila[fim++] = nos[root][i+'a']; 
	}
	
	while(ini < fim){
		int at = fila[ini++];
		rep(i, 26){
			int nt = nos[at][i+'a'];
			if(~nt){
				int fail = nos[at].fail;
				while(fail != root && nos[fail][i+'a'] == -1) fail = nos[fail].fail;
				if(nos[fail][i+'a'] != -1) fail = nos[fail][i+'a'];
				nos[nt].fail = fail;
				fila[fim++] = nt;
			}
		}
	}
}

int aho(int root, string& word){
	int tam = word.size();
	int pd = 0;
	int at = root;
		
	rep(i, tam){
		while(at != root && nos[at][word[i]] == -1) at = nos[at].fail;
		if(nos[at][word[i]] != -1) at = nos[at][word[i]];
		pd = max(pd, nos[at].pd);
	}
	
	return pd;
}

char buf[CINCO];

struct w{
	int len, id, val;
	string word;
	
	bool operator<(const w& ww) const{
		if(len != ww.len) return len < ww.len;
		return id < ww.id;
	}
}words[QUATRO];

int main(){
	int t;
	cin.sync_with_stdio(false);
	cin >> t;
	
	rep(cas, t){
		int n;
		cin >> n;
		prt = 0;
		
		rep(i, n){
			cin >> words[i].word >> words[i].val;
			words[i].len = words[i].word.size();
			words[i].id = i;
		}
		
		sort(words, words + n);
		
		int last = 0;
		int s = 0;
		
		rep(i, n){
			if(words[i].len != last){
				last = words[i].len;
				tries[s] = prt;
				mapa[words[i].len] = s;
				nos[prt].init(prt);
				++prt;
				++s;
			}
			
			add(tries[mapa[words[i].len]], words[i].id, words[i].word);
		}
		
		rep(i, s)
			falha(tries[i]);
		
		{
			int i = 0;
			while(i < n){
				int a = words[i].id;
				if(a == i) ++i;
				else swap(words[i], words[a]);
			}
		}
		
		int best = 0;
		rep(i, n){
			int minhaTrie = mapa[words[i].len];
			
			int pd = 0;
			rep(j, minhaTrie){
				int res = aho(tries[j], words[i].word);
				pd = max(pd, res);
			}
			pd = max(pd, nos[end[words[i].id]].pd) + words[i].val;
			nos[end[words[i].id]].pd = max(pd, nos[end[words[i].id]].pd);
			best = max(best, pd);
		}
		
		printf("Case #%d: %d\n", cas + 1, best);
	}
	
}












