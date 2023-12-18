// g++ -otest CppExample.cpp -std=c++17
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <sstream>

class ISortStrategy
{
public:
	virtual ~ISortStrategy() {}
	virtual std::vector<int> Sort(std::vector<int> arr) = 0;
};

class SortAcsending : public ISortStrategy
{
public:
	SortAcsending() {}
	~SortAcsending() {}
	std::vector<int> Sort(std::vector<int> arr) override
	{
		std::cout << "In SortAcsending" << std::endl;
		std::sort(arr.begin(), arr.end(), std::less<int>());
		return arr;
	}
};

class SortDescending : public ISortStrategy
{
public:
	SortDescending() {}
	~SortDescending() {}
	std::vector<int> Sort(std::vector<int> arr) override
	{
		std::cout << "In SortDescending" << std::endl;
		std::sort(arr.begin(), arr.end(), std::greater<int>());
		return arr;
	}
};

class Context
{
public:
	Context(std::unique_ptr<ISortStrategy> strategy){ _strategy = std::move(strategy);}
	~Context() {}
	void DoSomething(std::vector<int> &arr)
	{
		std::cout << "Do something before sorting, list: " << Vector2Str(arr) << std::endl;
		std::vector<int> res = _strategy->Sort(arr);
		std::cout << "After something before sorting, list: " << Vector2Str(res) << std::endl;
	}

	void SetStrategy(std::unique_ptr<ISortStrategy> strategy)
	{
		_strategy = std::move(strategy);
	}

private:
	std::unique_ptr<ISortStrategy> _strategy;

	std::string Vector2Str(std::vector<int> &vec)
	{
		std::stringstream ss;
		ss << "[";
		for (auto &i : vec)
		{
			ss << i << " ";
		}
		ss << "]";
		return ss.str();

	}
};

int main(int argc, const char** argv) {
	std::vector<int> dataset({1, 5, 4, 3, 2, 8});
	Context context(std::make_unique<SortAcsending>());
	context.DoSomething(dataset);

	std::cout << "\n=====" << std::endl;
	context.SetStrategy(std::make_unique<SortDescending>());
	context.DoSomething(dataset);
	return 0;
}
