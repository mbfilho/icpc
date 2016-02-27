#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
typedef pair<int,int> Ponto;
#define mp make_pair
#define X first
#define Y second
#define oo 1000000

#define N 1000

vector<int> D;
int K[N];
int d, k, n;
int open[N];

int calc(int key, int left, int right, int ini){
	int custo = 0;
	if(left){
		custo += (1-open[key-1]);
		custo += D[ini + left - 1] - K[key-1];
	}
	
	if(right){
		custo += 1 - open[key];
		custo += K[key] - D[ini+left];
	}
	
	return custo;
}

int faz(){
	int dist = 0;
	memset(open, 0, sizeof open);
	
	sort(D.begin(), D.end());
	sort(K, K + k);
		
	if(D[0] <= K[0]){
		open[0] = 1;
		dist += K[0] - D[0] + 1;
		while(d && D[0] <= K[0]){
			D.erase(D.begin());
			--d;
		}
	}
	
	if(d && D[d-1] >= K[k-1]){
		dist += D[d-1] - K[k-1] + (1-open[k-1]);
		open[k-1] = 1;
		
		while(d && D[d-1] >= K[k-1]){
			--d;
			D.pop_back();
		}
	}
	
	for(int i = 1; i < k; ++i){
		int best = oo;
		Ponto op;
		int a = 0, b;
		
		while(a < d && D[a] <= K[i-1]) ++a;
		b = a;
		while(b < d && D[b] <= K[i]) ++b;

		if(a < b){
			//qts vao ficar com o 1o
			for(int q = 0; q <= b - a; ++q){
				int custo = calc(i, q, (b-a) - q, a);
//				printf( "%d %d Custo %d\n", q, b-a-q, custo);
				if(custo < best || (custo == best && (b-a)-q) ){
					best = custo;
					op = mp(q != 0, (b-a-q) != 0);
				}
			}
		}
		
		if(best != oo){
			if(best < 0) throw 2;
			
			open[i-1] |= op.X;
			open[i] |= op.Y;
			dist += best;
		}
	}
	
	return dist;
}

int main(){
	while(scanf("%d%d%d", &n, &k, &d) != EOF && (n|k|d)){
		D.clear();
		for(int i = 0; i < k; ++i) scanf("%d", K + i);
		
		int tmp;
		for(int i = 0; i < d; ++i){
			scanf("%d", &tmp);
			D.push_back(tmp);
		}
		
		if(!d) printf("0\n");
		else
			printf( "%d\n", faz());
	}
}







