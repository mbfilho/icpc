#include <cstdio>
#include <cmath>

double PI = acos(-1);

double calc(double d, double D){
	double inner = (2.0/3.0)*PI*(D*D*D - d*d*d) + PI * (d*d*d);
	double total = PI*D*D*D;
	
	return total - inner;
}

int main(){
	int v, D;
	
	while(scanf("%d%d", &D, &v) == 2 && (D|v)){
		double ini = 0, fim = D;
		
		for(int i = 0; i < 55; ++i){
			double d = (ini+fim)/2.0;
			if(calc(d,D) > 2*v)
				ini = d;
			else
				fim = d;
		}
		
		printf("%.3lf\n", (ini+fim)/2);
	}
}

