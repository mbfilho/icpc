#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;
typedef long long ll;
#define EPS 1e-7
double PI = acos(-1);

char buf[100];

double rad(double deg){
	return (deg * PI) / 180.0;
}

int main(){
	double a, s;
	while(scanf("%lf%lf%s", &s, &a, buf) ==  3){
		if(a > 180) a = 360 - a; //nao faz sentido se for minutos, mas...
		
		s += 6440.0;
		double arc, cord;
		
		if(buf[0] == 'm' || buf[0] == 'M')
			a /= 60.0;
		
		arc = (a * 2.0 * PI * s) / (360.0);
		
		if(abs(a - 180) < EPS)
			cord = s*2;
		else
			cord = (s * sin(rad(a))) / (sin(rad((180.0 - a) / 2.0)));
		
		
		printf( "%.6lf %.6lf\n", arc, cord);
		
	}
}
