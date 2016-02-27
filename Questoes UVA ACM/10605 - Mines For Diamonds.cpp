#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < (b); ++i)
#define rep(i,n) fr(i,0,n)
#define N 12
typedef pair<int,int> pii;
#define mp make_pair
#define oo 100000000
int best[1<<N];
char ma[N][N];
int caras[N][N];

int mk[N][N][1<<N], it;
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int n, m;

int st;

struct no{
	int x, y, usados, d;
	no(){}
	
	no(int a, int b, int c, int e):x(a), y(b), usados(c), d(e){}
};

void bfs(int x, int y){
	queue<no> fila;
	fila.push(no(x,y,0,0));
	
	while(!fila.empty()){
		x = fila.front().x, y = fila.front().y;
		int usados = fila.front().usados, dist = fila.front().d;
		fila.pop();
		
		if(x < 0 || x == n || y < 0 || y >= m || ma[x][y] == '#'){
			best[usados] = min(best[usados], dist);
			continue;
		}
		if(dist > 22) continue;
		
		if(~caras[x][y]) usados |= 1 << caras[x][y];
		if(mk[x][y][usados] == it) continue;
		mk[x][y][usados] = it;
		
		rep(i, 4){
			fila.push(no(x+dx[i], y+dy[i], usados, dist+1));
		}
	}
}

int pd[1<<N];
int juntar(int mask){
	if(mask == 0) return 0;
	if(pd[mask] != -1) return pd[mask];
	int& resp = pd[mask];
	resp = oo;
	
	int ori = mask;
	while(mask > 0){
		resp = min(resp, best[mask] + juntar(ori & (~mask)));
		mask = (mask-1) & ori;
	}
	
	return resp;
}

int main(){
	it = 0;
	memset(mk, 0, sizeof mk);
	
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d%d", &n, &m);
		rep(i, n) scanf("%s", ma[i]);
		
		int cont = 0;
		rep(i, n){
			rep(j, m){
				if(ma[i][j] == '*') caras[i][j] = cont++;
				else caras[i][j] = -1;
			}
		}
		
		rep(i, (1 << cont)){
			best[i] = oo;
			pd[i] = -1;
		}
		
//		rep(i, n){
//			rep(j, m){
//				if(ma[i][j] != '*') printf("%c", ma[i][j]);
//				else printf("%d", caras[i][j]);
//			}
//			printf("\n");
//		}
		rep(i, n){
			rep(j, m){
				if(ma[i][j] == '*'){
					st = caras[i][j];
					++it;
					bfs(i, j);	
				}
			}
		}
//		printf(">> %d\n", best[3]);
		int resp = juntar((1<<cont) -1);
		printf("%d\n", resp);
	}
}





