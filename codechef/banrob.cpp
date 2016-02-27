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

int m;
double p;

double expo(double a, int xp){
	double res = 1;

	while(xp){
		if(xp&1) res *= a;
		a *= a;
		xp >>= 1;
	}
	return res;
}

double sum(double a1, double q, int t){
	if(q == 1){
		return a1 * t;
	}

 	return a1 * (1 - expo(q, t)) / (1 - q);
}

int main(){
	int t;
	scanf("%d", &t);

	while(t--){
		scanf("%d %lf", &m, &p);
		double ini = 1;

		// double soma = 0;
		// for(int i = m - 1; i >= 0; --i){
		// 	// printf("> %d %lf %lf\n", i, expo(p, i), soma);
		// 	soma = expo(p, i) - soma;
		// }
		// printf("> %.4lf %.4lf\n", soma*(1e9), (1e9)*(1-soma));

		if(m & 1){
			if(m>1)
				ini -= sum(p, p*p, (m-1)>>1) - sum(p*p, p*p, (m-1)>>1);
		}else{
			if(m>2)
				ini += sum(p*p, p*p, (m-2)>>1);
			if(m>1)
				ini -= sum(p, p*p, (m-1) - ((m-2)>>1));
		}

		printf("%.4lf %.4lf\n", (1e9)*ini, (1e9)*(1-ini));
	}
}

