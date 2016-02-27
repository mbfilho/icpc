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
#define LIM 5000100
bool can[LIM];

//Pitagorean triples:
//c2 = a2 + b2 => c = k * (m2 + n2), a = k * (m2 - n2), b = k * 2mn. With m > n, m-n odd, and gcd(m,n)=1
void pre(){
	int m = 1, n = 1, k;

	while(m * m < LIM) {
		n = 1;
		while(n < m) {
			k = 1;
			while(k * (n*n + m*m) < LIM){
				can[k*(n*n+m*m)] = true;
				++k;
			}
			++n;
		}
		++m;
	}
}

int main(){
	pre();
	int t;
	scanf("%d", &t);

	while(t--){
		int n;
		scanf("%d", &n);
		if(can[n]) printf("YES\n");
		else printf("NO\n");
	}
}