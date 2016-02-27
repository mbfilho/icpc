#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int main(){
	//Poligono
	double larg, x0, y0, x1, y1, x2, y2, area, areaT;
	//Hole
	double raio, largH;
	int poligonos;

	while( cin >> poligonos && poligonos ){
		areaT = 0;

		for( int i = 0; i < poligonos; ++i ){
			area = 0;
			cin >> larg >> x0 >> y0;
			cin >> x2 >> y2;
			x1 = x0;
			y1 = y0;
			while( x2 != x0 || y2 != y0 ){
				area += ( x1 * y2 - x2 * y1 );
				x1 = x2;
				y1 = y2;
				cin >> x2 >> y2;
			}
			area += ( x1 * y2 - x2 * y1 );
			
			if( area < 0 )
				area *= -1;
			areaT += ( area * larg ) / 2;
		}
		cin >> raio >> largH;
		double resposta = areaT / ( M_PI * raio * raio * largH );
		cout << floor( resposta ) << endl;
	}

}
