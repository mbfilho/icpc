#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for( __typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef pair<int,int> pii;
typedef long long ll;
#define oo 100000000
#define X first
#define Y second
#define mp make_pair
#define N 700
char buf[N];
int cont[N];

int n, k;
int main(){
	int t;
	scanf("%d", &t);
	rep(cas, t){
		scanf("%d%d%s", &n, &k, buf);
		memset(cont, 0, sizeof cont);
		int resp = 0;
		
		rep(i, n){
			if(i - k - 1 >= 0) --cont[buf[i-k-1]];
			if(cont[buf[i]]){
				++resp;
			}
			++cont[buf[i]];
		}
		
		printf("Case %d: %d\n", cas+1, resp);
	}
	
}


