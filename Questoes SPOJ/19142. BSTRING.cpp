#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define _(n) rep(i, n)
#define pb push_back
#define ft first
#define sd second
#define mp make_pair
#define SIZE(x) int(x.size())
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned long long hash;
#define N 50100

char str[N];
vector<int> ones;
int n, m;

int main(){
	int t;
	scanf("%d", &t);

	while(t--){
		ones.clear();
		scanf("%d%s", &m, str);
		n = strlen(str);
		_(n) if(str[i] == '1') ones.pb(i);

		int ft = 0, sd = m-1;
		ll sR = 0, sL = 0, r = 0, l = 0, best = 0;
		_(m) best += ones[i] - 0 - i, sR += ones[i], ++r;

		fr(i, 1, n) {
			if(str[i-1] == '1' && ones[ft] <= i-1 && i-1 <= ones[sd]) sR -= (i-1), sL += (i-1), --r, ++l;
			ll cost = sR - r * i - (r * (r-1))/2;
			cost += l * i - sL - l - (l * (l-1))/2;

			while(ones[ft] < i && sd + 1 < ones.size() && ones[sd+1] >= i){
				ll delta = ones[sd+1] - i - r;
				delta -= i - ones[ft] - 1 - (l - 1);
				if(delta < 0) cost += delta, sL -= ones[ft], --l, sR += ones[sd+1], ++r, ++ft, ++sd;
				else break;
			}

			best = min(best, cost);
		}

		printf("%lld\n", best);
	}
}