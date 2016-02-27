#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define N 200100
typedef unsigned long long ull;
typedef pair<int,int> pii;

int mk[8][8][12][1<<12];
int dx[] = {-1,-1,1,1};
int dy[] = {-1,1,-1,1};
int caso;
int best;
int contar(int ma){
	int c = 0;
	
	while(ma){
		++c;
		ma -= ma & (-ma);
	}
	
	return c;
}

char ma[12][12];
int sei[12][12];
int blan[12][12];

int b, w;
int wmask, qtd, no;

bool pode(int ni, int nj){
	if(ni < 0 || ni >= 8 || nj < 0 || nj >= 8) return false;
	return true;
}

void dfs(int i, int j, int bmask){
	if(!bmask){
		best = min(best, qtd);
		return;
	}
	
	if(mk[i][j][no][bmask] == caso) return;
	mk[i][j][no][bmask] = caso;
	
	int qtdb = contar(bmask);
	
	best = min(best, qtd + qtdb);
	
	rep(d, 4){
		int ni = i + dx[d], nj = j + dy[d];
		if(!pode(ni,nj)) continue;
		
		if(ma[ni][nj] != 'B' || !pode(ni + dx[d], nj + dy[d])) continue;
		if(ma[ni + dx[d]][nj + dy[d]] == 'W') continue;
		
		if(ma[ni + dx[d]][nj + dy[d]] == 'B'){
			ma[i][j] = '.';
			ma[ni + dx[d]][nj + dy[d]] = 'W';
			ma[ni][nj] = '.';
			++qtd;
			dfs(ni + dx[d], nj + dy[d], (bmask ^ sei[ni + dx[d]][nj + dy[d]]) ^ sei[ni][nj]);
			--qtd;
			ma[ni][nj] = 'B';
			ma[ni + dx[d]][nj + dy[d]] = 'B';
			ma[i][j] = 'W';
			continue;
		}
		
		swap(ma[ni + dx[d]][nj + dy[d]], ma[i][j]);
		ma[ni][nj] = '.';
		dfs(ni + dx[d], nj + dy[d], bmask ^ sei[ni][nj]);
		swap(ma[ni + dx[d]][nj + dy[d]], ma[i][j]);
		ma[ni][nj] = 'B';
	}
}

pii mapa[12];

int main(){
	rep(i, 8)
		scanf("%s", ma[i]);
	memset(mk, -1, sizeof mk);
	caso = -1;
	
	int aux = 0;
	int w = 0;
	rep(i, 8){
		rep(j, 8){
			if(ma[i][j] == 'B'){
				sei[i][j] = (1 << aux);
				++aux;
			}else if(ma[i][j] == 'W'){
				blan[i][j] = w;
				mapa[w] = mp(i,j);
				w++;
			}
		}
	}
	
	char gr[12][12];
	rep(i, 12)
		rep(j, 12) gr[i][j] = ma[i][j];
	
	best = 100000;
	rep(i, 1 << w){
		qtd = contar(i);
		if(qtd > best) continue;
		++caso;
		
		rep(j, w){
			if((1<<j) & i){
				ma[mapa[j].first][mapa[j].second] = '.';
			}
		}
		rep(j, 8){
			rep(k, 8){
				if(ma[j][k] == 'W'){
					no = blan[j][k];
					dfs(j, k, (1<<aux) - 1);
					// if(i == 0) printf("%d %d %d\n",j,k,best);
				}
			}
		}
		
		rep(i, 12)
			rep(j, 12) ma[i][j] = gr[i][j];
	}
	
	if(best == 100000){
		if(w == 0) best = aux;
		else best= 0;
	}
	printf("%d\n", best);
}




