#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;
typedef long long ll;
typedef pair<int, int> Ponto;
#define N 1500
#define X first
#define Y second
#define mp make_pair
#define pb push_back


int dist[N][N];
int e;
Ponto pts[20000];

int n, m;
Ponto ini, fim;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void pre(){
	memset(dist, -1, sizeof dist);
	queue<Ponto> fila;
	
	for(int i = 0; i < e; ++i){
		dist[pts[i].X][pts[i].Y] = 0;
		fila.push(pts[i]);
	}
	
	while(!fila.empty()){
		Ponto at = fila.front();
		fila.pop();
		
		for(int i = 0; i < 4; ++i){
			int nx = at.X + dx[i], ny = at.Y + dy[i];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m || dist[nx][ny] != -1) continue;
			dist[nx][ny] = dist[at.X][at.Y] + 1;
			fila.push(mp(nx,ny));
		}
	}
}

int marc[N][N];
void bfs(int lim){
	if(dist[ini.X][ini.Y] < lim){
		marc[fim.X][fim.Y] = -1;
		return;
	}

	memset(marc, -1, sizeof marc);
	queue<Ponto> fila;
	
	fila.push(ini);
	marc[ini.X][ini.Y]=0;
	
	while(!fila.empty()){
		Ponto at = fila.front();
		fila.pop();
		
		for(int i = 0; i < 4; ++i){
			int nx = at.X + dx[i], ny = at.Y + dy[i];
			if(nx < 0 || nx >= n || ny < 0 || ny >= m || marc[nx][ny] != -1 || dist[nx][ny] < lim) continue;
			marc[nx][ny] = marc[at.X][at.Y] + 1;
			fila.push(mp(nx,ny));
		}
	}
	
}

Ponto faz(){
	int inic = 0, fimc = dist[ini.X][ini.Y] + 5;
	Ponto best = mp(-1,-1);
	
	while(inic <= fimc){
		int meio = (inic+fimc) / 2;
		bfs(meio);
		
		if(marc[fim.X][fim.Y] != -1){
			best = mp(meio, marc[fim.X][fim.Y]);
			inic = meio + 1;

		}else
			fimc = meio - 1;
	}
	
	return best;
}





int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		scanf("%d%d%d", &e, &n, &m);
		scanf("%d%d%d%d", &ini.X, &ini.Y, &fim.X, &fim.Y);
		for(int i = 0; i < e; ++i){
			scanf("%d %d", &pts[i].X, &pts[i].Y);
		}
		
		pre();
		Ponto resp = faz();
		printf("%d %d\n", resp.X, resp.Y);
	}
	
}



