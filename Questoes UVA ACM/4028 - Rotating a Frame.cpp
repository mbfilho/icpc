#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;
#define EPS 1e-7
#define X first
#define Y second
#define mp make_pair
typedef pair<double,double> Ponto;
double const PI = acos(-1);

Ponto ret[4];
Ponto size[4];
double r, t, w;

Ponto operator-(const Ponto& a, const Ponto& b ){
	return mp( a.X - b.X, a.Y - b.Y );
}

Ponto operator+(const Ponto& a, const Ponto& b ){
	return mp( a.X + b.X, a.Y + b.Y );
}

double operator!(const Ponto& p){
	return sqrt(p.X * p.X + p.Y * p.Y);
}

Ponto operator*(const Ponto& p, const double tam){
	return mp(p.X * tam, p.Y * tam);
}

Ponto operator~(const Ponto& p){
	double tam = !p;
	return mp(p.X/tam, p.Y/tam);
}

void faz(){
	double sizeTotal = -8*r;
	
	for( int i = 0; i < 4; ++i ){
		size[i] = ret[(i+1)%4] - ret[i];
		sizeTotal += !size[i];
	}
	
	double andar = fmod( w * t * r, sizeTotal );
//	printf( "Resto %lf\n", andar);
	int lado = 0;
	while( andar > ( !size[lado] - 2 * r ) ){
		andar -= !size[lado] - 2 * r;
		++lado;
	}
//	printf( ">>>> %lf + lado %d\n", andar, lado);
	Ponto centro = (ret[lado] + ((~size[lado]) * (r + andar))) + (~size[(lado+1)%4]) * r;
//	printf( "Centro: %lf %lf\n", centro.X, centro.Y );
	Ponto original = (~size[0]) + ~(size[1]);
	original = ret[0] + (~original) * r * sqrt(2);
//	printf( "Centro original %lf, %lf\n", original.X, original.Y );
	
	
	Ponto desloc = original - centro;
	for( int i = 0; i < 4; ++i ) ret[i] = ret[i] + desloc;
	
	Ponto tmp[4];
	double angulo = fmod(w*t, 2*PI);
	for( int i = 0; i < 4; ++i ){
		tmp[i] = ret[i] - original;
		double x = tmp[i].X * cos(2*PI-angulo) - tmp[i].Y * sin(2*PI-angulo);
		double y = tmp[i].X * sin(2*PI-angulo) + tmp[i].Y * cos(2*PI-angulo);
		tmp[i] = mp(x,y);
	}
	
	for( int i = 0; i < 4; ++i ){
		ret[i] = original + tmp[i];
	}
	
}

int main(){
	int caso = 0;
	while( scanf( "%lf%lf", &ret[0].X, &ret[0].Y ) == 2 ){
		++caso;
		for( int i = 1; i < 4; ++i )
			scanf( "%lf%lf", &ret[i].X, &ret[i].Y );
		scanf( "%lf %lf %lf", &r, &t, &w );
		w = (PI*w)/180.0;
		faz();
		
		printf( "Case %d:", caso );
		for( int i = 0; i < 4; ++i ){
			printf( " %.3lf %.3lf", ret[i].X + EPS, ret[i].Y + EPS);
		}
		printf( "\n" );
	}
}


