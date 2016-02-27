#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
#define ft first
#define sd second
#define pb push_back
#define N 2000

//trick. Veja que a linha r1 so multiplica com a coluna r1. Mas elas são contadas 2x, contribuindo com zero na soma total.
//A unica parte de r1xc1 que é contada uma unica vez é o elemento [1][1]. Logo, o unusual product é a soma
// da diagonal principal

int pts[N];

int main(){
	int n;
	int cnt[] = {0, 0}, sum = 0;
	scanf("%d", &n);

	rep(i, n) rep(j, n){
		int ma;
		scanf("%d", &ma);
		if(i == j) pts[i] = ma, cnt[ma]++;
	}

	sum = cnt[1] % 2;

	int q;
	cin >> q;
	while(q--){
		int t, i;
		scanf("%d", &t);
		if(t != 3){
			scanf("%d", &i);
			--cnt[pts[i]], ++cnt[1-pts[i]];
			pts[i] = 1 - pts[i];
			sum = cnt[1] % 2;
		}else printf("%d", sum);

	}
	printf("\n");
}
