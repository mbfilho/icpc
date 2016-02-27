#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
typedef pair<int,int> pii;
#define mp make_pair
typedef long long ll;
#define N 100100
#define X first
#define Y second
#define pb push_back

int bob[N], alice[N];
int n, m, k;

int main(){
	scanf("%d%d%d", &n, &m, &k);
	rep(i, n) scanf("%d", alice+i);
	rep(i, m) scanf("%d", bob+i);
	
	sort(alice, alice+n);
	sort(bob, bob+m);
	--n, --m;
	while(n >= 0 && m >= 0){
		if(alice[n] > bob[m]){
			m = -1;
			break;
		}
		if(bob[m] >= alice[n]){
			--n, --m;
		}
	}
	
	if(n >= 0) printf("YES\n");
	else printf("NO\n");
}

