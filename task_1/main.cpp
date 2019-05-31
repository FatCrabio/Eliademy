#include <iostream>
#include "pch.h"
#include "threadpool.h"
#include "CustomContainer.h"

int main()
{
  Container cont;
  ThreadPool threadpool;

  for (auto i: {1,2,3,4,5})
  {
      threadpool.run([&cont, i]{ cont.Register(i, std::unique_ptr<IObject>(new Object())); });
  }

  threadpool.run([&cont]{ cont.Query(2);});
  threadpool.run([&cont]{ cont.Query(2);});

  threadpool.run([&cont]{ cont.Unregister(4);});

  // traverse over container
  threadpool.run([&cont]{ cont.for_each([&](IObject* obj) { obj->someAction();}); });

  return 0;
}
