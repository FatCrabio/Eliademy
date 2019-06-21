#include <iostream>
#include "pch.h"
#include "threadpool.h"
#include "CustomContainer.h"

int main()
{
  Container container;
  ThreadPool threadpool;

  for (auto i: {1,2,3,4,5})
  {
      threadpool.run([&container, i]{ container.Register(i, std::unique_ptr<IObject>(new Object())); });
      threadpool.run([&container]{ container.for_each([&](IObject* obj) { obj->someAction();}); });
  }

  threadpool.run([&container]{ container.Query(2);});
  threadpool.run([&container]{ container.Query(3);});

  threadpool.run([&container]{ container.for_each([&](IObject* obj) { obj->someAction();}); });

  threadpool.run([&container]{ container.Unregister(4);});

  threadpool.run([&container]{ container.for_each([&](IObject* obj) { obj->someAction();}); });

  return 0;
}
