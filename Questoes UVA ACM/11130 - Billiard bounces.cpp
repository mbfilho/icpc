#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double PI = acos( -1 );
#define EPS 1e-7

int main(){
	int a, b, v, A, s;
	
	while( scanf( "%d %d %d %d %d", &a, &b, &v, &A, &s ) != EOF && ( a | b | v | A | s ) ){
		int h = 0, ver = 0;
		double angulo = PI * A / 180.0;
		
		//horizontal
		double dist = s * v * sin( angulo ) / 2;
//		printf( ">> %lf\n", dist );
		if( dist - ( b / 2.0 ) > EPS ){
			++h;
			h += int( ( dist - b / 2.0 ) / b );
		}
		
		dist = s * v * cos( angulo ) / 2;
//		printf( ">> %lf\n", dist );

		if( dist - ( a / 2.0 ) >= EPS ){
			++ver;
			ver += int( ( dist - a / 2.0 ) / a );
		}
		
		printf( "%d %d\n", ver, h );
	}
}




