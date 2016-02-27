#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define N 700
#define X first
#define Y second

struct No{
	Ponto pt;
	int val;
	
	bool operator<(const No& a)const{
		return val < a.val;
	}
}nos[N*N];
int prt;

int marc[N][N];
int mapa[N*N];
int h[N][N];
int n, m, d;
int dx[] = {0,0,-1,1};
int dy[] = {-1,1,0,0};

void dfs(int x, int y, int lim, int region){
	marc[x][y] = region;
	mapa[region] = max(mapa[region], lim + d);
	
	for(int i =0; i < 4; ++i){
		int nx = x + dx[i], ny = y + dy[i];

		if(nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
		
		if(~marc[nx][ny]) mapa[region] = max(mapa[region], mapa[marc[nx][ny]]);
		
		else if(marc[nx][ny] == -1 && h[nx][ny] > lim) dfs(nx, ny, lim, region);
	}
}

int faz(){
	memset(marc, -1, sizeof marc);
	sort(nos, nos + prt);
	int cont = 0, res = 0;
	
	for(int i = prt - 1; ~i; --i){
		Ponto at = nos[i].pt;
		int ind = marc[at.X][at.Y];
		if(ind == -1){
			mapa[res] = nos[i].val;
			dfs(at.X, at.Y, h[at.X][at.Y] - d, res);
			ind = res++;
		}
		if(mapa[ind] <= nos[i].val)
			++cont;
	}
	
	return cont;	
}

int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		prt = 0;
		scanf("%d%d%d", &n, &m, &d);
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < m; ++j){
				scanf("%d", &h[i][j]);
				nos[prt].pt = mp(i,j);
				nos[prt].val = h[i][j];
				++prt;
			}
		}
		
		printf( "%d\n", faz());
	}
}



