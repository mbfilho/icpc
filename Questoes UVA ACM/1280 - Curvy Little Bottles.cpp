#include <bits/stdc++.h>
using namespace std;
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)

double PI = acos(-1.0);
double P[30];
int inc;
int n;

double eval(double x){
	double r = 0, tmp = x;
	rep(i, n)
		r += x * P[i], x *= tmp;
	return PI * r;
}

vector<double> mks;

double xl, xh;
bool bs(double start){
	double ini = start, fim = xh, tmp = eval(start);
	if(eval(fim) - tmp < inc) return false;
	
	rep(i, 30){
		double mid = (ini+fim)/2;
		if(eval(mid) - tmp > inc) fim = mid;
		else ini = mid;
	}
	
	mks.push_back((ini+fim)/2);
	return true;
}

void faz(){
	double novo[30];
	memset(novo, 0, sizeof novo);
	
	rep(i, n){
		rep(j, n){
			novo[i+j] += P[i] * P[j];
		}
	}
	n *= 2;
	rep(i, n) P[i] = novo[i] / (i+1);
}


int main(){
	int caso = 0;
	while(scanf("%d", &n) == 1){
		++caso;
		++n;
		rep(i, n)
			scanf("%lf", P + i);
		faz();
		
		scanf("%lf %lf %d", &xl, &xh, &inc);
		mks.clear();
		
		double start = xl;
		while(mks.size() < 8 && bs(start)){
			start = mks.back();
		}
		
		printf("Case %d: %.2lf\n", caso, eval(xh) - eval(xl));
		if(!mks.size()){
			printf("insufficient volume\n");
		}else{
			rep(i, mks.size()){
				if(i) printf(" ");
				printf("%.2lf", mks[i] - xl);
			}
			printf("\n");
		}
	}
}





