#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
 
using namespace std;
typedef pair<int,int> pii;
#define mp make_pair
#define ft first
#define sd second
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define N 16
vector <int> G[20];
 
void pushall()
{
    G[0].push_back(1);
    G[0].push_back(2);
    G[0].push_back(8);
    G[0].push_back(4);
 
    G[1].push_back(3);
    G[1].push_back(5);
    G[1].push_back(0);
    G[1].push_back(9);

    G[2].push_back(3);
    G[2].push_back(6);
    G[2].push_back(10);
    G[2].push_back(0);
 
    G[3].push_back(11);
    G[3].push_back(7);
    G[3].push_back(1);
    G[3].push_back(2);
 
    G[4].push_back(0);
    G[4].push_back(6);
    G[4].push_back(5);
    G[4].push_back(12);
 
    G[5].push_back(7);
    G[5].push_back(13);
    G[5].push_back(1);
    G[5].push_back(4);

    G[6].push_back(2);
    G[6].push_back(4);
    G[6].push_back(7);
    G[6].push_back(14);
 
    G[7].push_back(15);
    G[7].push_back(3);
    G[7].push_back(6);
    G[7].push_back(5);
 
    G[8].push_back(0);
    G[8].push_back(12);
    G[8].push_back(10);
    G[8].push_back(9);
 
    G[9].push_back(8);
    G[9].push_back(1);
    G[9].push_back(11);
    G[9].push_back(13);
 
    G[10].push_back(2);
    G[10].push_back(14);
    G[10].push_back(8);
    G[10].push_back(11);
 
    G[11].push_back(10);
    G[11].push_back(15);
    G[11].push_back(3);
    G[11].push_back(9);
 
    G[12].push_back(8);
    G[12].push_back(4);
    G[12].push_back(13);
    G[12].push_back(14);
 
    G[13].push_back(5);
    G[13].push_back(12);
    G[13].push_back(9);
    G[13].push_back(15);
 
    G[14].push_back(12);
    G[14].push_back(15);
    G[14].push_back(10);
    G[14].push_back(6);
 
    G[15].push_back(7);
    G[15].push_back(14);
    G[15].push_back(13);
    G[15].push_back(11);
 
    return;
}

int dist[1<<17];

void bfs(){
	queue<int> fila;
	
    memset(dist, -1, sizeof dist);
	rep(i, N) fila.push(0xff00), dist[0xff00] = 0;
	
	while(!fila.empty()){
		int msk = fila.front();
		fila.pop();
		
        rep(at, N) if(msk & (1<<at)){
            rep(i, G[at].size()){
                int nt = G[at][i];
                if(msk & (1<<nt)) continue;
                int nmsk = msk ^ (1<<nt) ^ (1<<at);
                if(dist[nmsk] != -1) continue;
                dist[nmsk] = 1 + dist[msk];
                fila.push(nmsk);    
            }
        }
	}
}

int main(){
	pushall();
    bfs();

	int t;
	scanf("%d", &t);
	
	fr(c, 1, t+1){
		int ini = 0;
		rep(i, 16){
			int a;
			scanf("%d", &a);
			if(a) ini |= 1 << i;
		}
		printf("Case #%d: ", c);
		int ans = dist[ini];
		if(ans == -1 || ans > 3) printf("more\n");
		else printf("%d\n",ans);
	}
}
