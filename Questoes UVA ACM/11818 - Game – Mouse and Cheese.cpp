#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
struct no{
	pii a, b;
	
	no(int x1, int y1, int x2, int y2):a(mp(x1,y1)), b(mp(x2,y2)){}
	
};

no sti[] = {no(1,0,1,1), no(2,0,2,1),
	no(0,1,1,1), no(1,1,2,1), no(2,1,3,1),
	no(1,1,1,2), no(2,1,2,2),
	no(0,2,1,2), no(1,2,2,2), no(2,2,3,2),
	no(1,2,1,3), no(2,2,2,3)
};

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
int bar[][4] = { {2,0}, {3,0,1}, {4,1},
				{7,2,5}, {8,5,3,6}, {9,6,4},
				{7,10}, {10,8,11}, {11,9}
			  };

pii rato, queijo;

int get(int i, int j){
	return i * 3 + j;
}

void busca(bool mk[3][3], int mask, int x, int y){
//	printf("(%d,%d)\n", x, y);
	int qual = 0;
	mk[x][y] = true;
	
	rep(i, 4){
		int nx = x + dx[i], ny = y + dy[i];
		if(nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
		int barreira = mask & (1<<bar[get(x,y)][qual]);
//		printf("%d %d ? %d %d \n", nx, ny, barreira, qual);
		++qual;
//		if(nx == queijo.first && ny == queijo.second){
//			printf("Bora ver: %d %d %d [%d]\n", x, y, i, barreira);
//		}
		if(!barreira && !mk[nx][ny])
			busca(mk, mask, nx, ny);
	}
}

int pd[1<<13];
bool mk[3][3];
int memo(int mask){
	if(~pd[mask]) return pd[mask];
	rep(i, 12){
		if(mask & (1<<i)){
			memset(mk, false, sizeof mk);
			int nmask = mask ^(1<<i);
			busca(mk, nmask, rato.first, rato.second);
			bool win = mk[queijo.first][queijo.second] || (memo(mask ^ (1<<i)) == 0);
//			if(mask == 597) printf("Rec :: %d %d\n", mk[queijo.first][queijo.second], i); 
//			if(mask == 596) printf("Win? %d\n", win);
			if(win){
//				if(mask == 597) printf("Rec %d > %d\n", i, mask ^(1<<i));
				return pd[mask] = 1;
			}
		}
	}
	
	return pd[mask] = 0;
}


int main(){
	int t;
	scanf("%d", &t);
	rep(cas, t){
		int s,c,r;
		scanf("%d%d%d", &s, &c, &r);
		--s;
		rato = mp(s/3, s % 3);
		--c;
		queijo = mp(c/3, c%3);
		
		int mask = (1<<12)-1;
		while(r--){
			pii pts[2];
			rep(i, 2)
				scanf("%d%d", &pts[i].first, &pts[i].second);
			sort(pts, pts+2);
			
			rep(i, 12){
				if(sti[i].a == pts[0] && sti[i].b == pts[1]){
					mask = mask & (~(1<<i));
//					printf("Tirei %d\n", i);
					break;
				}
			}
		}
//		printf(">>> %d Rato %d %d X %d %d\n", mask, rato.first, rato.second, queijo.first, queijo.second);
		memset(mk, false, sizeof mk);
		busca(mk, mask, rato.first, rato.second);
		if(mk[queijo.first][queijo.second])
			printf("Case %d: No Cheese!\n", cas+1);
		else{
//			continue;
			memset(pd, -1, sizeof pd);
			printf("Case %d: ", cas+1);
			if(memo(mask) == 1)
				printf("SOHA\n");
			else 
				printf("TARA\n");
		}
			
	}
}



