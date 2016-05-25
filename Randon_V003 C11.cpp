#include <iostream>
#include <random>
//Valido solo para C++11 !!

using namespace std;

long genera(long primero, long penultimo)
{
	static random_device rd;
	static default_random_engine eng{ rd() };
	static uniform_int_distribution<> dist(primero, penultimo);
	return dist(eng);
}

int main()
{
	const long primero = 10, penultimo = 19;
	random_device rd;
	default_random_engine eng{ rd() };
	uniform_int_distribution<> dist(primero, penultimo);

	long i;
	cout << "\nGeneration of 10 samples between " << primero << " and " << penultimo << " using dist:\n";
	for (i = 0; i < 10; ++i)
		cout << dist(eng) << '\n';
	cout <<"\n==== FIN ====" << endl;

	cout << "\nGeneration of 100 samples between "<<primero<<" and "<<penultimo<<" using the function genera():\n";
	for (i = 0; i < 100; ++i)
	{
		cout << genera(primero, penultimo) << ' ';
	}
	cout << "\n==== FIN ====" << endl;

	long distribution[penultimo + 1]; memset(distribution, 0, (penultimo + 1) * sizeof(long));
	for ( i = 0; i < 200000; ++i)
	{
		long j=genera(primero, penultimo);
		distribution[j]++;
	}
	long expected_distribution = i / (penultimo - primero + 1);
	double max_error=-1e133,xx;

	cout << "\nDistribution after obtaining " << i << " samples:\n";
	for ( i = primero; i <= penultimo; ++i)
	{
		xx = distribution[i] - expected_distribution; if (xx < 0) xx =- xx;
		if (max_error < xx) max_error = xx;
		cout << distribution[i] << '\n';
	}
	cout << "=== Maximum distribution error = " << 100.0*xx / expected_distribution << " ./. \n";


	cout << "\n=== FIN ====" << endl; getchar(); getchar();
	return 0;
}