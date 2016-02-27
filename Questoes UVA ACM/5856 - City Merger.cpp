#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
using namespace std;
typedef unsigned long long hash;
#define N 30
#define B 1097
#define mp make_pair
typedef pair<int,int> pii;

int entra[N][N];
int pd[1<<16][16];
int dois[N];
int tam[N];
vector<string> words;
bool exc[N];
int n;

void eliminar(){
	memset(exc, false, sizeof exc);
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(i == j) continue;
			
			if(words[j].find(words[i]) != string::npos){
				exc[i] = true;
				break;
			}
		}
	}
	

	for(int i = 0; i < n; ++i)
		tam[i] = words[i].size();
}

int encaixar(int a, int b){
	int best = 0, cont = 0;
	hash ha = 0, hb = 0, pot = 1;
	int len = min(tam[a], tam[b]);
	
	for(int i = 0; i < len; ++i){
		++cont;
		hb = hb * B + words[b][i];
		ha = words[a][tam[a] - 1 - i] * pot + ha;
		
		if(ha == hb)
			best = cont;
		pot = pot * B;
	}
	
	return best;
}

void pre(){
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			entra[i][j] = encaixar(i,j);
		}
	}
}

void faz(){
	memset(pd, 0, sizeof pd);
	queue<pii> fila;
	for(int i = 0; i < n; ++i){
		if(exc[i]) continue;
		fila.push(mp(i, dois[i]));
		pd[dois[i]][i] = tam[i];
	}
	
	while(!fila.empty()){
		int at = fila.front().first, mask = fila.front().second, custo = pd[mask][at];
		fila.pop();
		
		for(int i = 0; i < n; ++i){
			if(dois[i] & mask) continue;
			if(exc[i]) continue;
			
			int nmask = mask | dois[i];
			
			if(!pd[nmask][i]){
				pd[nmask][i] = custo + tam[i] - entra[at][i];
				fila.push(mp(i, nmask));
			}else
				pd[nmask][i] = min(pd[nmask][i], custo + tam[i] - entra[at][i]);
		}
	}
}

char buf[100];

int main(){
	for(int i = 0; i < N; ++i) dois[i] = 1 << i;
	
	while(scanf("%d", &n) == 1 && n){
		words.clear();
		for(int i = 0; i < n; ++i){
			scanf("%s", buf);
			words.push_back(buf);
		}
		
		eliminar();
		pre();
		faz();
		int best = 1000000;
		int mask = 0;
		for(int i = 0; i < n; ++i){
			if(!exc[i])
				mask |= dois[i];
		}
		
		for(int i = 0; i < n; ++i){
			if(exc[i]) continue;
			best = min(best, pd[mask][i]);
		}
		printf("%d\n", best);
		
	}
}


