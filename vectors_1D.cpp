//looks for decomposition in prime numbers 
#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void decomposition(T num, vector<T>  & dec)
{
	dec.clear();
	int i = 2;
	while (num > 1)
	{
		if (num % i == 0)
		{
			dec.push_back(i); num /= i;
		}
		else
			i++;
	}
}

template<typename T>
void imprime1d(vector<T>  & dec)
{
	for (int i = 0; i < dec.size(); i++) cout << dec[i] << " ";
	cout << endl;
}

int main() 
{
	int u = 1280;
	vector<int> dec;
	decomposition(u, dec);
	cout << u << ":"; imprime1d(dec);

	u = 720;
	decomposition(u, dec);
	cout << u << ":"; imprime1d(dec);

	cout << "=== END ===" << endl;
	getchar();
	return 1;
}


