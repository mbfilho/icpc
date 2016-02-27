#include <cstdio>
#include <cstring>
#include <algorithm>
#define fr(i,a,b) for(int i=a;i<b;i++)
#define rep(i,b) fr(i,0,b)
#define pb push_back
#define mp make_pair
#include <string>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<int,int> pii;
#define N 7
#define L 0
#define R 1
#define U 2
#define D 3
int ma[N][N];
  // 2
// 0   1
  // 3
  
int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0};
bool mk[N][N][2];
bool mk2[N][N];

// cara, baixo/cima, dir
vector<pii> adj[2][2][4];
// cara, pos

void pre(){
	adj[0][0][R].pb(mp(1, 0));
	adj[0][0][R].pb(mp(0, 1));
	adj[0][0][D].pb(mp(0, 1));
	adj[0][0][D].pb(mp(1, 1));
	adj[0][1][U].pb(mp(0, 0));
	adj[0][1][U].pb(mp(1, 0));
	adj[0][1][L].pb(mp(0, 0));
	adj[0][1][L].pb(mp(1, 1));
	
	adj[1][0][L].pb(mp(0, 0));
	adj[1][0][L].pb(mp(1, 1));
	adj[1][0][D].pb(mp(0, 1));
	adj[1][0][D].pb(mp(1, 1));
	adj[1][1][U].pb(mp(1, 0));
	adj[1][1][U].pb(mp(0, 0));
	adj[1][1][R].pb(mp(1, 0));
	adj[1][1][R].pb(mp(0, 1));
}

bool valid(int i, int j){
	return i >= 0 && i < 5 && j >= 0 && j < 5 && ma[i][j] != -1;
}

bool reach(int src, int i, int j, int pos, int cont, int h = 0){
	if(mk[i][j][pos]) return false;
	mk[i][j][pos] = true;
	int aux = 1 - mk2[i][j];
	mk2[i][j] = true;	
	
	bool achou = false;
	int cara = ma[i][j];
	rep(k, 4){
		int nx = i + dx[k], ny = j + dy[k];
		if(!valid(nx, ny)){
			bool vale = cont + 1 >= 3;
			int lado = src;
			if(nx < 0){//U
				vale &= pos;
				lado = U;
			}else if(nx >= 5){//D
				vale &= (!pos);
				lado = D;
			}else if(ny < 0){//L
				vale &= (cara == 0 && pos) || (cara && !pos);
				lado = L;
			}else if(ny >= 5){//R
				vale &= (!cara && !pos) ||(cara && pos);
				lado = R;
			}
			vale &= lado != src;
			achou |= vale;
			continue;
		}
		
		rep(g, adj[cara][pos][k].size()){
			pii nt = adj[cara][pos][k][g];
			if(nt.first == ma[nx][ny]) achou |= reach(src, nx, ny, nt.second, cont + aux, h + 1);
		}
	}
	
	return achou;
}

void clear(){
	memset(mk, false, sizeof mk); memset(mk2, false, sizeof mk2);
}

bool ehWin(){
	rep(i, 5){
		rep(pos, 2){
			if(valid(i, 0)){
				clear();
				if((ma[i][0] == 0 && pos) || (ma[i][0] == 1 && !pos)){
					if(reach(L, i, 0, pos, 0)) return true;
				}
			}
			
			if(valid(0, i)){
				clear();
				if(pos){
					if(reach(U, 0, i, pos, 0)) return true;
				}
			}
			
			if(valid(4, i)){
				clear();
				if(!pos){
					if(reach(D, 4, i, pos, 0)) return true;
				}
			}
			
			if(valid(i, 4)){
				clear();
				if((ma[i][4] == 0 && pos == 0) || (ma[i][4] == 1 && pos)){
					if(reach(R, i, 4, pos, 0)) return true;
				}
			}
		}
	}
	
	return false;
}

int _ma[N][N];
string tenta(){
	if(ehWin()) return "WIN";
	
	rep(i, 5) rep(j, 5) _ma[i][j] = ma[i][j];
	pii pos;
	
	rep(k, 4){
		rep(i, 5) rep(j, 5) ma[i][j] = _ma[i][j];
		rep(i, 5) rep(j, 5) if(ma[i][j] == -1) pos = mp(i, j);
		
		rep(q, 4){
			int nx = pos.first + dx[k], ny = pos.second + dy[k];
			if(!valid(nx, ny)) break;
			swap(nx, pos.first); swap(ny, pos.second);
			swap(ma[nx][ny], ma[pos.first][pos.second]);
			
			if(ehWin()){
				string dir;
				if(k == R) dir = "L";
				else if(k == L) dir = "R";
				else if(k == U) dir = "D";
				else if(k == D) dir = "U";
				
				char tmp[100];
				sprintf(tmp, "%d", q+1);
				dir += tmp;
				return dir;
			}
		}
	}
	
	return "FAIL";
}

char linha[100];

int main(){
	pre();
	rep(i, 5){
		scanf("%s", linha);
		rep(j, 5){
			if(linha[j] == '\\') ma[i][j] = 1;
			else if(linha[j] == '/') ma[i][j] = 0;
			else ma[i][j] = -1;
		}
	}
	
	string resp = tenta();
	printf("%s\n", resp.c_str());
}
