#include "CustomContainer.h"

void Container::Register(int objectId, std::unique_ptr<IObject> pObject)
{
    std::unique_lock<std::shared_timed_mutex> lock(m_mtx);
    m_map.emplace(objectId, pObject);
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
    return it->second;
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
