#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i, n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef pair<double,double> P;
#define N 120
#define pb push_back
#define mp make_pair

int X, Y, Z;
double favo(int x, int A){
	double resp = 2.0 * (x-1.0) * (A - x) + 2.0 * (A-1.0) + 1.0;
	return resp;
}

double getM(int x, int y, int z){
	return (favo(x, X) * favo(y, Y) * favo(z, Z)) / (double(X*X)*double(Y*Y)*double(Z*Z));
}

double expo(double val, int xp){
	double resp = 1;
	while(xp){
		if(xp&1) resp *= val;
		val *= val;
		xp>>=1;
	}
	return resp;
}

int k;
int main(){
	int casos;
	scanf("%d", &casos);
	rep(cas, casos){
		scanf("%d%d%d%d", &X, &Y, &Z, &k);
		double soma = 0;
		
		fr(i, 1, X+1){
			fr(j, 1, Y+1){
				fr(p, 1, Z+1){
					double M = getM(i,j,p);
					double tmp = (1.0 - expo(1-2.0*M, k))/2.0;
					soma += tmp;
				}
			}
		}
		
		printf("Case %d: %.7lf\n",cas+1, soma);
		
	}
}



