#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

int bit[1010][1010];
int X, Y;

void update(int x, int y, int val){
	for(int i = x; i <= X; i += i & (-i)){
		for(int j = y; j <= Y; j += j & (-j)){
			bit[i][j] += val;
		}
	}
}

int soma(int x, int y){
	int res = 0;
	
	for(int i = x; i > 0; i -= i & (-i)){
		for(int j = y; j > 0; j -= j & (-j)){
			res += bit[i][j];
		}
	}
	
	return res;
}


int main(){
	int k;
	bool ft = true;
	
	while(scanf("%d %d %d", &X, &Y, &k) == 3 && (X|Y|k)){
		X = max(X, Y);
		Y = X;
		
		
		memset(bit, 0, sizeof bit);
		int q;
		scanf("%d", &q);
		
		char op[10];
		
		while(q--){
			scanf("%s", op);
			
			if(op[0] == 'A'){
				int qtd, x, y;
				scanf("%d%d%d", &qtd, &x, &y);
				++x; ++y;
				update(x,y,qtd);
			}else{
				int x[2], y[2];
				scanf("%d%d%d%d", &x[0], &y[0], &x[1], &y[1]);
				if(x[0] > x[1]) swap(x[0], x[1]);
				if(y[0] > y[1]) swap(y[0], y[1]);
				++x[1], ++y[1];
				
				int res = 0;
				rep(i, 2){
					rep(j, 2){
						if( (i == 1 && j == 1) || (i == 0 && j == 0)){
							res += soma(x[i], y[j]);
						}else{
							res -= soma(x[i], y[j]);
						}
					}
				}
				
				printf("%d\n", k * res);
			}
		}
		
		printf("\n");
	}
}

