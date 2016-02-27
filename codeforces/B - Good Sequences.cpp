#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
#define N 100100
typedef long long ll;

int A[N], primos[N], cont;

void pre(){
	memset(A, -1, sizeof A);
	cont = 0;
	
	fr(i, 2, N){
		if(A[i] == -1){
			A[i] = cont;
			primos[cont++] = i;
		}
		
		rep(j, A[i]+1){
			ll tmp = ll(primos[j]) * i;
			if(tmp >= N) break;
			A[tmp] = j;
		}
	}
}

int val[N], n;
int maior[N];

void update(int num, int pd){
	while(num != 1){
		maior[A[num]] = max(maior[A[num]], pd);
		num /= primos[A[num]];
	}
}

int pega(int num){
	if(num == 1) return 0;
	
	int best = 0;
	
	while(num != 1){
		best = max(best, maior[A[num]]);
		num /= primos[A[num]];
	}
	
	return best;
}

int main(){
	pre();
	scanf("%d", &n);
	rep(i, n) scanf("%d", val + i);
	
	int best = 1;
	update(val[n-1], 1);
	
	for(int i = n - 2; i >= 0; --i){
		int pd = pega(val[i]);
		update(val[i], pd+1);
		best = max(pd+1, best);
	}
	
	printf("%d\n", best);
	
	
}




