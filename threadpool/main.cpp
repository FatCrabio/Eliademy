#include <iostream>
#include "threadpool.h"
using namespace std;

std::mutex io_mutex;

void piy()
{
  std::vector<int> vec(1000000);
  for (auto& it : vec)
  {
    std::unique_lock<std::mutex> lock(io_mutex);
    std::cout << it;
  }
}

int main()
{
  cout << "Hello World!" << endl;
  ThreadPool threadpool;
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  threadpool.run([]{piy();});
  std::cin.get();
  return 0;
}

