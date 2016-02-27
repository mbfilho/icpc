#include <cstdio>
#include <cmath>
int a, b, c;

const double PI = acos(-1);

double heron(){
	double p = (a+b+c)/2.0;
	return sqrt(p*(p-a)*(p-b)*(p-c));
}

double inner(){
	double r = heron() / ((a+b+c)/2.0);
	
	return r * r * PI;
}

double outter(){
	double seno = (2.0*heron()) / (a*b);
	double r = c / (seno*2.0);
	
	return r * r * PI;
}

int main(){
	while(scanf("%d%d%d", &a,&b,&c) == 3 && (a|b|c)){
		printf( "%.4lf %.4lf %.4lf\n", outter() - heron(), heron() - inner(), inner());
	}
}

