#pragma once
#include "pch.h"

class IObject
{
    virtual void someAction() = 0;
    virtual ~IObject();
};
class Object : public IObject
{
    virtual void someAction() override {}
    virtual Object() = default;
};

class Container
{
    using ObjectsMap = std::map<int, IObject*>;
    using iterator = ObjectsMap::iterator;
    using const_iterator = ObjectsMap::const_iterator;
public:
    void Register(int objectId, std::unique_ptr<IObject> pObject);
    void Unregister(int objectId);
    IObject* Query(int objectId);
    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;
private:
    std::shared_timed_mutex m_mtx;
    ObjectsMap m_map;
};

