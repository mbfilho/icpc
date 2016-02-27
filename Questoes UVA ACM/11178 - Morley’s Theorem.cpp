#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <stack>
#include <string>
#include <cmath>
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;
#define mp make_pair
#define X first
#define Y second
#define pb push_back
#define fr(i,a,b) for(int i = a; i < b; ++i)
#define rep(i,n) fr(i,0,n)
#define each(it, m) for(__typeof(m.begin()) it = m.begin(); it != m.end(); ++it)
typedef pair<double, double> P;
#define EPS 1e-7
int cmpEps(double a, double b){
	if(abs(a-b) < EPS) return 0;
	return 1;
}

P operator+(const P a, const P b){
	return mp(a.X + b.X, a.Y + b.Y);
}
P operator-(const P a, const P b){
	return mp(a.X - b.X, a.Y - b.Y);
}

P operator*(const P a, const double k){
	return mp(a.X * k, a.Y * k);
}

double operator*(const P a, const P b){
	return a.X * b.X + a.Y * b.Y;
}

double operator!(const P a){
	return sqrt(a*a);
}


P inter(P p1, P v1, P p2, P v2){
	double k2, k1;
	if(cmpEps(v1.Y, 0.0)){
		k2 = p2.X - p1.X - (v1.X/v1.Y) * (p2.Y-p1.Y);
		k2 /= ((v1.X*v2.Y)/v1.Y - v2.X);
		k1 = (p2.Y - p1.Y + k2*v2.Y)/v1.Y;
	}else{
		k2 = p2.X - p1.X - (v1.X * (p2.Y - p1.Y))/v1.Y;
		k2 /= ((v1.X * v2.Y)/v1.Y - v2.X);
		k1 = (p2.Y - p1.Y + k2 * v2.Y)/v1.Y;
	}
	return p1 + v1 * k1;
}

P rotate(P p1, double teta){
	return mp(p1.X * cos(teta) - p1.Y * sin(teta), sin(teta) * p1.X + cos(teta) * p1.Y);
}

double angle(P a, P b){
	return acos((a*b)/(!a*!b));
}

P faz(P a, P b, double alfa, P c, P d, double teta){
	P p1 = a, p2 = c;
	P v1 = rotate(b - a, alfa), v2 = rotate(d - c, teta);
	
	return inter(p1, v1, p2, v2);
}

int main(){
	int t;
	scanf("%d", &t);
	P a, b, c;
	P d, e, f;
	while(t--){
		scanf("%lf %lf %lf %lf %lf %lf", &a.X, &a.Y, &b.X, &b.Y, &c.X, &c.Y);
		
		double abc = angle(c-b, a-b);
		double acb = angle(b-c, a-c);
		double cab = angle(b-a, c-a);
		d = faz(b, c, abc/3.0, c, a, (acb * 2)/3);
		e = faz(c, a, acb/3.0, a, b, (cab * 2)/3);
		f = faz(a, b, cab/3.0, b, c, (abc * 2)/3);
		printf("%lf %lf %lf %lf %lf %lf\n", d.X, d.Y, e.X, e.Y, f.X, f.Y);
	}
}




