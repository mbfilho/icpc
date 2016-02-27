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
#define N 200200

int num[N], n;

double get(int fat, double x) {
	double sum = 0, best = 0;
	int t = 0;

	rep(i, n) {
		double c = fat * (num[i] - x);
		while(t && sum + c <= 0) sum -= fat * (num[i-t] - x), --t;

		if(sum + c > 0) sum += c, ++t;
		best = max(best, sum);
	}
	

	return best;
}

double getBest(double x){
	return max(get(1, x), get(-1, x));
}

int main(){
	ios::sync_with_stdio(false);

	cin >> n;
	_(n) cin >> num[i];

	double ini = -3*1e9, fim = 3*1e9;
	_(210) {
		double a = (fim-ini) / 3 + ini, b = fim - (fim-ini)/3;
		double besta = getBest(a), bestb = getBest(b);

		// rep(i, n) besta = max(besta, getSize(i+1, a)), bestb = max(bestb, getSize(i+1,b));
		if(besta > bestb) ini = a;
		else fim = b;
	}
	// printf("K: %lf x %lf\n", testa(-6.812500), getBest(-6.812500));

	// double b = 0;
	// rep(i, n) b = max(b, getSize(i+1, 113.875000000000000));
	double ans = getBest(ini);
	printf("%.6lf\n", ans);
	// printf("%lf %lf %lf\n", ini, fim, ans);

}
