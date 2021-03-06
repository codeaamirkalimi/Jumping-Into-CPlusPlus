#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int randRange(int low, int high)
{
	// We get a random number, get it to be between 0 and the number of values in our range, 
	// then add the lowest possible value
	return rand() % (high - low + 1) + low;
}

int main()
{
	int sRandSeed = time(nullptr);
	srand(sRandSeed);

	int low = 1;
	int high = 100;
	int randomNumber = randRange(4, 10);
	int guessedNumber = 0;
	bool stillGuessing = true;

	cout << "Guess what random number I have chosen between " << low << " and " << high << '\n';
	do
	{
		cin >> guessedNumber;
		if (guessedNumber > randomNumber)
		{
			cout << "Your guess is too high!\n";
		}
		else if (guessedNumber < randomNumber)
		{
			cout << "Your guess is too low!\n";
		}
		else
		{
			cout << "Correct!\n";
			stillGuessing = false;
		}
	}
	while (stillGuessing);
}