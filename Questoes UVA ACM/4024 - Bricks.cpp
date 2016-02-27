#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
#define mp make_pair
#define X first
#define Y second
#define N 15
struct Frac{
	int num, dem;
	
	Frac(int a, int b = 1){
		num = a;
		dem = b;
	}
	Frac(){}
	
	bool operator<( const Frac& f)const{
		return num * f.dem < f.num * dem;
	}
	bool operator>=( const Frac& f) const{
		return num * f.dem >= f.num * dem;
	}
	bool operator>( const Frac& f) const{
		return num * f.dem > f.num * dem;
	}
	
	Frac operator+(const Frac& f) const{
		int nd = dem * f.dem;
		
		return Frac( f.dem * num + dem * f.num, nd );
	}
	
	Frac operator/(const Frac& f) const{
		return Frac( num * f.dem, dem * f.num );
	}
	
	Frac operator/(const int& a ) const{
		return *this / Frac( a, 1 );
	}
};

typedef pair<Frac,Frac> Ponto;
Ponto p0[N], p1[N], c0[N], c1[N];
int pot[N];

int n; //baixo
int m; //cima;
char linha[10000];

struct No{
	Ponto a0, a1;
};

bool inter(No& arg, int forbid){
	for( int i = 0; i < n; ++i ){
		if(forbid & pot[i]) continue;
		bool s = true;
		
		No tmp;
		tmp.a0.X = max( arg.a0.X, p0[i].X );
		tmp.a0.Y = max( arg.a0.Y, p0[i].Y );
		tmp.a1.X = min( arg.a1.X, p1[i].X );
		tmp.a1.Y = min( arg.a1.Y, p1[i].Y );
		
		if(tmp.a0.X >= tmp.a1.X) s = false;
		if(tmp.a0.Y >= tmp.a1.Y) s = false;
		
		if(s) return true;
	}
	
	return false;
}

bool vaiCair(int retirados){
	//todos os de cima
	for( int i = 0; i < m; ++i ){
		No tmp;
		
		//| |A|
		tmp.a0 = mp( (c0[i].X + c1[i].X) / 2, c0[i].Y );
		tmp.a1 = c1[i];
		if(!inter(tmp,retirados)) return true;
		
		//|A| |
		tmp.a0 = c0[i];
		tmp.a1 = mp( (c0[i].X + c1[i].X) / 2, c1[i].Y );
		if(!inter(tmp,retirados)) return true;
		
		//cima
		tmp.a0 = mp( c0[i].X, (c0[i].Y + c1[i].Y) / 2 );
		tmp.a1 = c1[i];
		if(!inter(tmp,retirados)) return true;
		
		//baixo
		tmp.a0 = c0[i];
		tmp.a1 = mp( c1[i].X, (c0[i].Y + c1[i].Y) / 2 ); 
		if(!inter(tmp,retirados)) return true;	
	}
	
	return false;
}
int contar(int mask){
	int c = 0;
	while(mask){
		mask -= (mask & -mask);
		++c;
	}
	return c;
}

bool podeRetirar(int mask){
	int retirados = 0;
	while(1){
		int antes = retirados;		
		for( int i = 0; i < n; ++i ){
			if( !(mask & pot[i]) ) continue;
			No tmp;
		
			//DIR
			tmp.a0 = p0[i];
			tmp.a1 = mp(10000, p1[i].Y);
			if(!inter(tmp, retirados | pot[i])){
				retirados |= pot[i];
				
				continue;
			}
			
			//ESQ
			tmp.a0 = mp(-10000, p0[i].Y);
			tmp.a1 = mp(p0[i].X, p1[i].Y);
//			tmp.print("Esquerda " );
			if(!inter(tmp, retirados | pot[i])){
				retirados |= pot[i];
				continue;
			}
		
			//CIMA
			tmp.a0 = p0[i];
			tmp.a1 = mp(p1[i].X, 10000);
			if(!inter(tmp, retirados | pot[i])){
				retirados |= pot[i];
				continue;
			}
		
			//Baixo
			tmp.a0 = mp(p0[i].X, -10000);
			tmp.a1 = mp(p1[i].X, p0[i].Y);
			if( !inter(tmp, retirados | pot[i])){
				retirados |= pot[i];
				continue;
			}
		}
		if(retirados == antes) break;
	}
	
	return retirados == mask;
}

int testar(){
	int resp = 0;
	for( int mask = 1; mask < pot[n]; ++mask ){
		if(contar(mask) < resp) continue;
		
		if(podeRetirar(mask)){
			if(!vaiCair(mask))
				resp = max( resp, contar(mask));
		}
	}
	
	return resp;
}

No getPonto(char* tmp){
	No resp;
	
	int x, qtd, y;
	while( !(*tmp >= '0' && *tmp <= '9') ) ++tmp;
	sscanf( tmp, "%d%n", &x, &qtd );
	tmp += qtd;
	while( !(*tmp >= '0' && *tmp <= '9') ) ++tmp;
	sscanf( tmp, "%d%n", &y, &qtd );
	tmp += qtd;
	resp.a0.X = x;
	resp.a0.Y = y;	
	
	while( !(*tmp >= '0' && *tmp <= '9') ) ++tmp;
	sscanf( tmp, "%d%n", &x, &qtd );
	tmp += qtd;
	while( !(*tmp >= '0' && *tmp <= '9') ) ++tmp;
	sscanf( tmp, "%d%n", &y, &qtd );
	tmp += qtd;
	resp.a1.X = x;
	resp.a1.Y = y;
	
	return resp;
}

int main(){
	pot[0] = 1;
	for(int i = 1; i < 15; ++i ) pot[i] = 2 * pot[i-1];
	int caso = 0;
	
	while( scanf( "%d%d", &n, &m ) != EOF && n ){
		++caso;
		
		for( int i = 0; i < n; ++i ){
			scanf( "%s", linha );
			No tmp = getPonto(linha);
			p0[i] = tmp.a0;
			p1[i] = tmp.a1;
		}
		
		for( int i = 0; i < m; ++i ){
			scanf( "%s", linha );
			No tmp = getPonto(linha);
			c0[i] = tmp.a0;
			c1[i] = tmp.a1;
		}
		
		printf( "Case %d: %d\n", caso, testar() );
	}	
}



