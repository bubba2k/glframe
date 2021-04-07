#include "Tracker.hpp"

#include "Mesh.hpp"

template <class T>
int Tracker<T>::track(T object)
{
	int id = this->size();

	this->push_back(object);

	return id;
}

template <class T>
void Tracker<T>::forget(int id)
{
	this->at(id) = nullptr;
}

// explicit instantiations
template class Tracker<Mesh *>;
