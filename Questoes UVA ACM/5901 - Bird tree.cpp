#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef pair<int,int> Frac;
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define N 200000
char resp[N];

int main(){
	int casos;
	scanf( "%d", &casos );
	
	while(casos--){
		scanf( "%s", resp );
		
		int a = 0, b = 0;
		
		int prt = 0;
		while(resp[prt] && resp[prt] != '/') ++prt;
		
		resp[prt] = 0;
		sscanf( resp, "%d", &a );
		sscanf( resp + prt + 1, "%d", &b );
		
		Frac ini = mp(a,b);
		
		prt = 0;
		while(ini.X != ini.Y){
			if(ini.X > ini.Y){
				resp[prt++] = 'R';
				ini.X -= ini.Y;
				swap(ini.X, ini.Y);
			}else{
				resp[prt++] = 'L';
				swap(ini.X, ini.Y);
				ini.X -= ini.Y;
			}
		}
		
		resp[prt] = 0;
		printf( "%s\n", resp );
		
	}
}




