#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <thread>
#include <mutex>
#include <iterator>
#include <string>
#include <functional>

std::mutex m_mutex;

using namespace std;

int Is_equal(char a, char b);

void Search_Substring(std::string main_string, std::string substring, std::vector<size_t>& Iterators, size_t left, size_t right);



int main()
{
	return 0;
}

int Is_equal(char a, char b)
{
    if (a == b)
    {
        return 1;
    }
    else
        return 0;
}

void Search_Substring(std::string main_string, std::string substring, std::vector<size_t>& Iterators, size_t left, size_t right)
{
    m_mutex.lock();
    int count = 0;
    for (size_t i = left; i < right; i++)
    {
        for (size_t j = 0; j < substring.size(); j++)
        {
            if (i + j < main_string.size())
            {
                count += Is_equal(main_string[i + j], substring[j]);
            }
        }
        if (count == substring.size())
        {
            Iterators.push_back(i);
        }
        count = 0;
    }
    m_mutex.unlock();
}