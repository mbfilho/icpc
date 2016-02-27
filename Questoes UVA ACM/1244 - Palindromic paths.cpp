#include <cstdio>
#include <cstring>
#include <algorithm>
#include  <map>
#include <vector>
#include <set>
#include <string>
using namespace std;
#define Fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,a) Fr(i,0,a)
#define N 60
#define mp make_pair

typedef long long ll;
struct No{
	int u, v, tam;
	
	No(){}
	No(int a, int b, int c){
		u = a;
		v = b;
		tam = c;
	}
};

bool marc[N][N][N];
pair<int,int> next[N][N][N];
vector<No> fila;

char ma[N][N];
vector<int> adj[N][26], rev[N][26];
int n;

bool cmp(const No& a, const No& b){
	return ma[a.u][a.v] < ma[b.u][b.v];
}

void faz(){
	memset(marc, false, sizeof marc);
	fila.clear();
	
	rep(i, n){
		Fr(j, i+1, n){
			fila.push_back(No(i, j, 1));
			marc[i][j][1] = true;
		}
	}
	sort(fila.begin(), fila.end(), cmp);

	rep(i, n){
		fila.push_back(No(i, i, 0));
		marc[i][i][0] = true;
	}

	while(fila.size()){
		int lim = 1;
		while(lim < fila.size() && fila[lim].tam == fila[0].tam) 
			++lim;
			
		for(int ch = 'A'; ch <= 'Z'; ++ch){
			for(int i = 0; i < lim; ++i){
				int u = fila[i].u, v = fila[i].v, tam = fila[i].tam;
				for(int x = 0; x < rev[u][ch-'A'].size(); ++x){
					for(int y = 0; y < adj[v][ch-'A'].size(); ++y){
						int nu = rev[u][ch-'A'][x], nv = adj[v][ch-'A'][y];
						
						if(!marc[nu][nv][tam+2]){
							marc[nu][nv][tam + 2] = true;
							next[nu][nv][tam+2] = mp(u,v);
							
							fila.push_back(No(nu, nv, tam+2));
						}
					}
				}
			}
		}
		rep(i, lim) fila.erase(fila.begin());
		
	}
}

void junta(int u, int v, int tam){
	if(tam == 1)
		printf( "%c", ma[u][v]);
	else if(tam){
		int nu = next[u][v][tam].first, nv = next[u][v][tam].second;
		printf( "%c", ma[u][nu]);
		junta(nu, nv, tam - 2);
		printf( "%c", ma[nv][v]);
	}
}


int main(){
	int t;
	scanf("%d", &t);
	
	while(t--){
		scanf("%d", &n);
		for(int i = 'A'; i <= 'Z'; ++i){
			for(int j = 0; j < n; ++j){
				adj[j][i-'A'].clear();
				rev[j][i-'A'].clear();
			}
		}
		
		for(int i = 0; i < n; ++i) scanf("%s", ma[i]);
		
		for(int i = 0; i < n; ++i){
			for(int j = i+1; j < n; ++j){
				int ch = ma[i][j] - 'A';
				adj[i][ch].push_back(j);
				rev[j][ch].push_back(i);
			}
		}

		faz();
		int best = -1;
		rep(i, n){
			if(marc[0][n-1][i]) best = i;
		}
		
		if(~best){
			junta(0, n-1, best);
			printf("\n");
		}else{
			while(1);
			printf("NO PALINDROMIC PATH\n");
		}
	}
}

