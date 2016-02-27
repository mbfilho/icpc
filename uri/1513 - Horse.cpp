#include <cstdio>
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>	
#include <queue>
using namespace std;
#define mp make_pair
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 101
#define ft first
#define sd second

typedef pair<int,int> pii;

int n, m, k;
pii pos[N];
int mapa[N][N];
char ma[N][N];
int pd[15][1<<15];
int dist[15][N][N];
int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
int dy[] = {-1, 1, -1, 1, 2, -2, 2, -2};
int x, y;

int memo(int last, int mask){
	if(mask == ((1 << k) - 1)) return dist[last][x][y] == -1 ? 1000000000 : dist[last][x][y];
	int &rec = pd[last][mask];
	if(~rec) return rec;
	rec = 1000000000;

	rep(i, k){
		if(mask & (1 << i)) continue;
		if(dist[last][pos[i].ft][pos[i].sd] == -1) continue;
		rec = min(rec, dist[last][pos[i].ft][pos[i].sd] + memo(i, mask | (1 << i)));
	}
	
	return rec;	
}


void bfs(int c){
	queue<pii> fila;
	fila.push(pos[c]);
	dist[c][pos[c].ft][pos[c].sd] = 0;
	
	while(!fila.empty()){
		pii at = fila.front();
		fila.pop();
		
		rep(d, 8){
			pii nt = mp(at.ft + dx[d], at.sd + dy[d]);
			if(nt.ft >= 0 && nt.ft < n && nt.sd >= 0 && nt.sd < m && ma[nt.ft][nt.sd] != '#' && dist[c][nt.ft][nt.sd] == -1){
				fila.push(nt);
				dist[c][nt.ft][nt.sd] = dist[c][at.ft][at.sd] + 1;
			}
		}
	}
}


int main(){		
	while(cin >> n >> m >> k && (n|m|k)){
	
		rep(i, n) cin >> ma[i];
	
		int tmp = 0;
		rep(i, n) rep(j, m){
			if(ma[i][j] == 'P') pos[tmp++] = mp(i, j);
			if(ma[i][j] == 'C') x = i, y = j;
		}
		memset(dist, -1, sizeof dist);
		rep(i, tmp) bfs(i);
		
		memset(pd, -1, sizeof pd);
		int ans = 1000000000;
		
		rep(i, tmp){
			ans = min(ans, memo(i, 1 << i) + dist[i][x][y]);
		}
		
		cout << ans << endl;
		
	}
}
