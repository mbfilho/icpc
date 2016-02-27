#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)

#define N 250100
#define T (N*30 + 100)
typedef pair<int,int> pii;
#define mp make_pair
#define X first
#define Y second
#define oo 2000000000
#define pb push_back

struct no{
	int adj[26];
	vector<pii> best;
	int s;
	
	no(){
		memset(adj, -1, sizeof adj);
		s = -1;
	}
	
	void addPair(pii par){
		best.pb(par);
		sort(best.begin(), best.end());
		while(best.size() > 2) best.pop_back();
	}
};
vector<no> nos;

int ord[N];

void add(int ind, string buf, int tam, bool pares = false){
	int at = 0;
	pii thePair = mp(ord[ind], ind);
	rep(i, tam){
		if(pares) nos[at].addPair(thePair);
		int ch = buf[i] - 'a';
		if(nos[at].adj[ch] == -1) nos[at].adj[ch] = nos.size(), nos.pb(no());
		at = nos[at].adj[ch];
	}
	
	nos[at].s = ind;
	if(pares) nos[at].addPair(thePair);
}

int cont;
void ordena(int no){
	if(~nos[no].s) ord[nos[no].s] = cont++;
	rep(i, 26) if(~nos[no].adj[i]) ordena(nos[no].adj[i]);
}

vector<pii> thePath(char* buf, int tam){
	vector<pii> path;
	int at = 0;
	
	rep(i, tam){
		for(int j = nos[at].best.size() - 1; j >= 0; --j) path.pb(nos[at].best[j]);
		int ch = buf[i] - 'a';
		at = nos[at].adj[ch];
		if(at == -1) break;
	}
	if(~at)	for(int j = nos[at].best.size() - 1; j >= 0; --j) path.pb(nos[at].best[j]);
	return path;
}

vector<string> words;
char linha[1000];

int main(){
	nos.clear();
	nos.pb(no());
	
	{
		int i = 0;
		while(gets(linha) && linha[0]){
			int tam = strlen(linha);
			add(i++, linha, tam);
			reverse(linha, linha + tam);
			words.pb(linha);
		}
	}
	
	cont = 0;
	ordena(0);
	
	nos.clear();
	nos.pb(no());

	rep(i, words.size()) add(i, words[i], words[i].size(), true);
	
	while(gets(linha) && linha[0]){
		int tam = strlen(linha);
		reverse(linha, linha + tam);
		vector<pii> path = thePath(linha, tam);
		string resp = "";
		
		for(int i = path.size() - 1; i >= 0; --i){
			int j = path[i].second;
			if(words[j] != linha){
				resp = words[j];
				reverse(resp.begin(), resp.end());
				break;
			}
		}
		
		printf("%s\n", resp.c_str());
	}
	
}






