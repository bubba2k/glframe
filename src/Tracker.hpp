#ifndef TRACKER_HPP
#define TRACKER_HPP

#include <vector>

template <class T>
class Tracker : public std::vector<T>
{

public:
	int  track(T);
	void forget(int);
};

#endif
