#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = (a); i < (b); ++i)
#define rep(i, n) fr(i,0,n)
typedef double MA[2][2];
typedef long long ll;

const double y = sqrt(3.0);
const double x = sqrt(2.0);
const double A = (x-x*y);
const double B = (x+x*y);

int main(){
	// {
	// 	double a1 = 1, b1 = 1;
	// 	fr(i, 2, 300){
	// 		double a = a1 * (x-x*y) + b1*(x+x*y);
	// 		double b = a1*(x+x*y)+b1*(x*y-x);
	// 		// cout << i << ": " << a << " " << b << endl;
	// 		a1 = a, b1 = b;
	// 	}
	// 	cout << (1.94368e+11 +3.36655e+11)/(1<<30) << endl;
	// }

	ll ii, k, ai, bi, s;
	scanf("%lld %lld %lld %lld %lld", &ii, &k, &s, &ai, &bi);
	// scanf("%d%d%lld%d%d", &ii, &k, &s, &ai, &bi);
	double ak, bk;
	ll xp = k - ii;
	MA tmp = {{A,B},{B,-A}};
	int sig = -1;

	if(ii > k){
		double d1 = A/(A*A+B*B), d2 = B/(A*A+B*B), d3 = (1-(A*A/(A*A+B*B)))/B, d4 = -A/(A*A+B*B);	
		MA inve = {{d1, d2}, {d3, d4}};
		rep(i, 2) rep(j, 2) tmp[i][j] = inve[i][j];
		sig = 1;
		xp = -xp;
	}

	{
		//mesma coisa do laço abaixo, mas com menos hipoteses sobre o tamanho de xp 
		//a garantia da entrada esta errada (i.e. i pode ser > 1e9!!!)
		ll xp1 = xp >> 1;
		ll pot = 4;

		while(xp1) {
			if(xp1 & 1){
				s += sig * pot;
			}
			xp1 >>= 1;
			pot *= 2;
		}
	}
	// fr(i, 1, 31) if(xp & (1<<i)) {
	// 	s += sig * (1LL << (i+1));
	// }

	if(xp&1) {
		ak = ai * tmp[0][0] + bi * tmp[0][1];
		bk = ai * tmp[1][0] + bi * tmp[1][1];
	} else ak = ai, bk = bi;

	printf("%lf\n", (ak+bk)/pow(2.0, 1.0*s));

}







