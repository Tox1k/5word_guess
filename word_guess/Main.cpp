#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <fstream>
#include <random>


int calcScore(const std::string& word1 , const std::string& word2)
{
	int score = 0;
	std::vector<int> bucket1( 26, 0 );
	std::vector<int> bucket2( 26, 0 );

	for (const auto c : word1) 
	{
		bucket1[c - 'a']++;
	}
	for (const auto c : word2)
	{
		bucket2[c - 'a']++;
	}

	for (int i = 0; i < 26; i++) 
	{
		score += std::min( bucket1[i], bucket2[i] );
	}

	for (int i = 0; i < 5; i++)
	{
		if (word1[i] == word2[i]) score ++;
	}

	return score;
}


bool vecContains( const std::string& word_in, const std::vector<std::string>& vec )
{
	for (std::string word : vec)
	{
		if (word == word_in) return true;
	}

	return false;
}


int main() 
{
	std::vector<std::string> words_container;

	{
		std::ifstream file( "sgb-words.txt" );
		std::string line;
		while ( std::getline( file, line ) ) 
		{
			if ( line.empty() )
			{
				continue;
			}

			words_container.push_back( line );
		}
	}

		std::string target;

	{
		std::mt19937 rnd(std::random_device{}());
		std::uniform_int_distribution<int> dist(0, words_container.size() - 1);
		target = words_container[dist(rnd)];
	}

	while (true)
	{
		std::cout << "Type a 5 letters long word :";
		std::string guess;
		std::getline( std::cin , guess );

		for(auto& c : guess)
		{
			c = std::tolower(c);
		}


		if (guess == "!cheat") 
		{
			std::cout << "the word is " << target << std::endl;
			continue;
		}


		if ( guess.length() != 5)
		{
			std::cout << "Type an exactly 5 letter long word you moron!" << std::endl;
			continue;
		}

		if( !vecContains( guess, words_container ))
		{
			std::cout << guess << "? What the fuck does that mean?" << std::endl;
			continue;
		}
		const int score = calcScore(guess, target);

		if (score == 10)
		{
			std::cout << "You've got it right!"<< std::endl;
			break;
		}
		else
		{
			std::cout << "Oh well... You've got " << calcScore(guess, target) << " points, but you can do even better, can't ya?" << std::endl;
		}
		

	}

	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n' );
	std::cin.get();
	return 0;
}