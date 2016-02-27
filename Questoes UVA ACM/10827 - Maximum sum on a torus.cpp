#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define oo 50000000

int n, pre[100][100], ma[100][100];
int maior[100];

int maxsum(int i, int di){
	int best = -oo, soma = 0, total = 0;
	maior[0] = -oo;
	
	for(int j = 1; j <= n; ++j){
		int ele = pre[i+di][j] - pre[i-1][j] - pre[i+di][j-1] + pre[i-1][j-1];
		if(soma + ele < ele) soma = ele;
		else soma += ele;
		
		total += ele;
		maior[j] = max(maior[j-1], total);
		
		best = max(best, soma);
	}
	
	for(int j = 1; j <= n; ++j){
		best = max(best, maior[j-1] + total);
		total -= pre[i+di][j] - pre[i-1][j] - pre[i+di][j-1] + pre[i-1][j-1];
	}
	
	return best;
}

int main(){
	int casos;
	scanf("%d", &casos);
	
	while(casos--){
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				scanf("%d", &ma[i][j]);
			}
		}
		
		int best = -oo;
			
		for(int k = 0; k < 2; ++k){
			memset(pre, 0, sizeof pre);
			for(int i = 1; i <= n; ++i){
				for(int j = 1; j <= n; ++j)
					pre[i][j] = pre[i][j-1] + pre[i-1][j] - pre[i-1][j-1] + ma[i][j];
			}
			for(int i = 1; i <= n; ++i){
				for(int di = 0; i + di <= n; ++di){
					best = max(best, maxsum(i, di));
				}
			}
			
			for(int i = 1; i <= n; ++i){
				for(int j = i; j <= n; ++j){
					int tmp = ma[i][j];
					ma[i][j] = ma[j][i];
					ma[j][i] = tmp;
				}
			}
		}

		
		for(int j = 1; j <= n; ++j){
			for(int dj = 0; j + dj <= n; ++dj){
				maior[0] = -oo;
				for(int i = 1; i <= n; ++i){
					int ele = (pre[i][j]) + (pre[i][n] - pre[i][j+dj]);
					maior[i] = max(ele, maior[i-1]);
				}
				int total = pre[n][j] + (pre[n][n] - pre[n][j+dj]);
				for(int i = 1; i <= n; ++i){
					int soma = total - (pre[i-1][j] + (pre[i-1][n] - pre[i-1][dj+j]));
					best = max(best, maior[i-1] + soma);
					soma -= (pre[i][j]) + (pre[i][n] - pre[i][j+dj]);
				}
			}
		}
		
		printf("%d\n", best);
	}
}






