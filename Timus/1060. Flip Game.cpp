#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <queue>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

int adj[20];

int get(int i, int j){
	return i * 4 + j;
}

void pre(){
	int dx[] = {0, 0, 1, -1, 0};
	int dy[] = {-1, 1, 0, 0, 0};
	
	rep(i, 4){
		rep(j, 4){
			rep(k, 5){
				int nx = i + dx[k], ny = j + dy[k];
				if(nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
				adj[get(i,j)] |= 1 << get(nx,ny);
			}
		}
	}
}

int dist[1<<17];

int main(){
	ios_base::sync_with_stdio(false);
	pre();
	char buf[10];
	int ini = 0;
	rep(i, 4){
		cin >> buf;
		rep(j, 4){
			if(buf[j] == 'b') ini |= 1 << get(i,j);
		}
	}
	memset(dist, -1, sizeof dist);
	queue<int> fila;
	fila.push(ini);
	dist[ini] = 0;
	int goal = -1;
	while(!fila.empty()){
		int at = fila.front(); fila.pop();
		if(!at || (at == (1<<16) - 1)){
			goal = dist[at];
			break;
		}
		
		rep(i, 4){
			rep(j, 4){
				int nt = at ^ adj[get(i,j)];
				if(dist[nt] == -1){
					dist[nt] = 1 + dist[at];
					fila.push(nt);
				}
			}
		}
	}
	
	if(~goal){
		cout << goal << "\n";
	}else
		cout << "Impossible\n";

}

