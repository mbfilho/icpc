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


double getHour(int minu) {
	return minu / 2.0;
}

double getMin(int minu) {
	return minu * 6;
}

double getAngle(int h, int m) {
	double ah = getHour(h * 60 + m), am = getMin(m);

	return min(abs(ah - am), 360 - abs(ah - am));
}

int main() {
	int t;
	scanf("%d", &t);

	while(t--) {
		double a;
		scanf("%lf", &a);

		fr(h, 0, 12) fr(m, 0, 60) {
			double a1 = getAngle(h, m);
			if(abs(a1 - a) < 1.0/120) printf("%02d:%02d\n", h, m);
		}
	}
}



