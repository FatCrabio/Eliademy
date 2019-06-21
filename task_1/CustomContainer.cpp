#include "CustomContainer.h"

void Container::Register(int objectId, std::unique_ptr<IObject> pObject)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_mtx);
    m_map.emplace(objectId, pObject.release());
}

void Container::Unregister(int objectId)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_mtx);
    m_map.erase(objectId);
}

IObject* Container::Query(int objectId)
{
    std::shared_lock<std::shared_timed_mutex> lock(m_mtx);
    auto it = m_map.find(objectId);
    return it != m_map.end()? it->second: nullptr;
}

void Container::for_each(std::function<void(IObject*)> func)
{
    ObjectsMap traverse_map(m_map);
    std::shared_lock<std::shared_timed_mutex> lock(m_mtx);
    for (auto& item: traverse_map)
    {
        func(item.second);
    }
}

Container::iterator Container::begin()
{
    return m_map.begin();
}

Container::iterator Container::end()
{
    return m_map.end();
}

Container::const_iterator Container::cbegin() const
{
    return m_map.cbegin();
}


Container::const_iterator Container::cend() const
{
    return m_map.cend();
}
