#pragma once

#include <vector>

#include "export.hpp"

class DLL_EXPORT RandomEngine
{
public:
	RandomEngine(RandomEngine const&) = delete;
	void operator=(RandomEngine const&) = delete;
	static RandomEngine& GetInstance()
	{
		static RandomEngine instance;
		return instance;
	}

	int RandomInt(int min, int max) const;
	double RandomDouble(double min, double max) const;
	double RandomDouble() const;
	bool RandomBool() const;

	template<class T>
	const T& RandomElement(const std::vector<T>& list) const
	{
		return list[RandomInt(0, list.size())];
	}

private:
	RandomEngine();
};

