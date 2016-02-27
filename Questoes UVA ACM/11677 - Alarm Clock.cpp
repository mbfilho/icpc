#include <iostream>
using namespace std;

class hora{
	public:
		int h, m;
	
		bool operator< ( const hora& outra ){
			bool retorno = false;
			if( h < outra.h ){
				retorno = true;
			}else if( outra.h == h && m < outra.m ){
				retorno = true;
			}
			
			return retorno;
		}
		
		int getMin(){
			return h * 60 + m;
		}
};

int main(){
	hora ini, fim;
	int min1, min2, dife;
	cin >> ini.h >> ini.m >> fim.h >> fim.m;
	
	while( ini.h | ini.m | fim.h | fim.m ){
		min1 = ini.getMin();
		min2 = fim.getMin();
		
		if( fim < ini )
			dife = min2 - min1 + ( 24 * 60 );
		else
			dife = min2 - min1;

		cout << dife << endl;
		cin >> ini.h >> ini.m >> fim.h >> fim.m;	
	}
}
