#ifndef TRACKER_HPP_
#define TRACKER_HPP_

#include <list>

typedef int Tracker_ID;

template <class T>
class Tracker
{
	std::list<T *> items;
	int nextID;
	int n_Items;

public:
	Tracker();

	Tracker_ID track(T *);
	bool forget(Tracker_ID);
	T * get(Tracker_ID);

	inline typename std::list<T *>::iterator begin() { return items.begin(); }
	inline typename std::list<T *>::iterator end()   { return items.end();   }
	inline int num() { return n_Items; };
};

#endif
