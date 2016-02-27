#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define N 1600
#define pb push_back

/*
O plano é composto por varias copias de mazes. Faça uma dfs e guarde em qual copia vc esta. Caso 
alcance um vertice ja visitado, so que em uma copia diferente da dele (a copia na qual ele foi visitado)
entao um loop foi encontrado de modo que dá para se distanciar da origem.
*/
char ma[N][N];
int marc[N][N];
Ponto pos[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m;

bool dfs(int x, int y, Ponto a){
	marc[x][y] = true;
	pos[x][y] = a;
	
	for(int i = 0; i < 4; ++i){
		int nx = x + dx[i], ny = y + dy[i];
		Ponto nt = a;
		
		if(nx < 0){
			nx += n;
			--nt.X;
		}else if(nx >= n){
			nx -= n;
			++nt.X;
		}
		
		if(ny < 0){
			ny += m;
			--nt.Y;
		}else if(ny >= m){
			ny -= m;
			++nt.Y;
		}
		
		if(ma[nx][ny] == '#') continue;
		if(marc[nx][ny]){
			if(pos[nx][ny] != nt) return true;
			continue;
		}
		
		if(dfs(nx, ny, nt)) return true;
	}
	
	return false;
}

int main(){
	memset(marc, 0, sizeof marc);
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i) scanf("%s", ma[i]);
	
	int x, y;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(ma[i][j] == 'S'){
				x = i; y = j;
				break;
			}
		}
	}
	
	bool pode = false;
	pode = dfs(x,y, mp(0,0));
	
	if(pode) printf("Yes\n");
	else printf("No\n");
}







