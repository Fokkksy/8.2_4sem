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

void parallel_search(std::string main_string, std::string substring, std::vector<size_t>& Iterators);

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

void parallel_search(std::string main_string, std::string substring, std::vector<size_t>& Iterators)
{
    const std::size_t num_core = std::thread::hardware_concurrency();
    int hardware_threads = num_core != 0 ? num_core : 4;
    int thread_x_size = main_string.size() / hardware_threads;
    int residue = main_string.size() % hardware_threads;
    std::vector<std::thread> threads(hardware_threads);
    double left = 0, right = thread_x_size;
    for (size_t i = 0; i < threads.size(); i++)
    {
        threads[i] = std::thread(Search_Substring, main_string, substring, std::ref(Iterators), left, right);
        left += thread_x_size;
        right += thread_x_size;
    }

    if (residue != 0)
    {
        threads.push_back(std::thread(Search_Substring, main_string, substring, std::ref(Iterators), left, main_string.size()));
    }
    std::for_each(threads.begin(), threads.end(), std::mem_fn(&std::thread::join));
}