#include "Tracker.hpp"
#include <algorithm>

#include "Mesh.hpp"
#include "Entity.hpp"

template <class T>
Tracker<T>::Tracker() : nextID(0), n_Items(0) {}

template <class T>
Tracker_ID Tracker<T>::track(T *ptr)
{
    items.push_front(ptr);

	++n_Items;

    return nextID++;
}

template <class T>
bool Tracker<T>::forget(Tracker_ID id)
{
    auto it = std::find_if(items.begin(), items.end(),
            [=](T *ptr)
            { return id == ptr->getID(); });

    if(it == items.end())
    {
        return false;
    }
    else
    {
        items.erase(it);
		--n_Items;
        return true;
    }
}

template <class T>
T * Tracker<T>::get(Tracker_ID id)
{
    auto it = std::find_if(items.begin(), items.end(),
            [=](T *ptr)
            { return id == ptr->getID(); });

    if(it == items.end())
        return nullptr;
    else
        return *it;
}

template class Tracker<Mesh>;
template class Tracker<Entity>;
template class Tracker<EntityInstance>;
