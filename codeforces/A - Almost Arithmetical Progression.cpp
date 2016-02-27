#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define fr(i,a,b) for(int i = a; i <  b; ++i)
#define rep(i,n) fr(i,0,n)
#define mp make_pair
#define pb push_back
#define X first
#define Y second
#define N 4010

int pd[N][N][2];

int input[N];
int n;

int pos[1000010];

int geta(int j, int val, int p, int k){
	int nt = val + (k ? 1 : -1) * p;
	if(nt > 1000000 || nt < 0) return 1;
	int ind = pos[nt];
	
	if(ind > j)
		return pd[j][ind][k];
	else 
		return 1;
}

int best;
void faz(){
	best = 1;
	int it = 1;
	memset(pos, -1, sizeof pos);
	
	for(int i = n - 2; i >= 0; --i){
		
		for(int j = n-1; j > i; --j){
			rep(k, 2){
				int fat = k ? 1 : -1, p = (input[j] - input[i]) / fat;
				
				int val = geta(j, input[j], p, 1-k);
				pd[i][j][k] = 1 + val;
				if(!k) best = max(best, pd[i][j][k]);
			}
			pos[input[j]] = j;
		}
	}
}


int main(){
	scanf("%d", &n);
	rep(i, n) scanf("%d", input + i);
	
	faz();
	printf("%d\n", best);
}




