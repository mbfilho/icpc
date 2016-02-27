#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define N 25100
#define pb push_back
map<string,int> mapa;
vector<string> input;
vector<int> adj[N];
int pd[N];

void add(int u, int v){
	adj[min(u,v)].pb(max(u,v));
}

void replace(int idx){
	string str = input[idx];
	
	rep(i, str.size()){
		char ch = str[i];
		rep(c, 26){
			if(c + 'a' == ch) continue;
			str[i] = c + 'a';
			if(mapa.find(str) != mapa.end())
				add(idx, mapa[str]);
		}
		str[i] = ch;
	}
}

void remove(int idx){
	string str = input[idx];
	
	rep(i, str.size()){
		string res = "";
		rep(j, str.size()){
			if(i == j) continue;
			res += str[j];
		}
		if(mapa.find(res) != mapa.end()) add(idx, mapa[res]);
	}
}

int main(){
	{
		char linha[100];
		while(scanf("%s", linha) == 1){
			mapa[linha] = input.size();
			input.pb(linha);
		}
	}	
	rep(i, input.size()){
		replace(i);
		remove(i);
	}
	
	int best = 0;
	for(int i = input.size() - 1; i >= 0; --i){
		pd[i] = 1;
		rep(j, adj[i].size()){
			pd[i] = max(pd[i], 1 + pd[adj[i][j]]);
		}
		best = max(best, pd[i]);
	}
	printf("%d\n", best);
	
}

