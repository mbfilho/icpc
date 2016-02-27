#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 600
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)

char ma[N][N];
bool mk[N][N];
int n, m, k;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(int i, int j){
	if(i >= n || j >= m || ma[i][j] != '.' || !k || mk[i][j]) return;
	mk[i][j] = true;
	rep(d, 4) dfs(i+dx[d], j+dy[d]);
	if(k) ma[i][j] = 'X', --k;
}

int main(){
	scanf("%d%d%d", &n, &m, &k);
	memset(mk, false, sizeof mk);
	rep(i, n) scanf("%s", ma[i]);
	rep(i, n) rep(j, m) if(ma[i][j] == '.'){ dfs(i, j); goto sai; }
	
	sai:
	rep(i, n) printf("%s\n", ma[i]);
}
