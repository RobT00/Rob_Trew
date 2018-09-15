#ifdef TEST
#include "../Functions.h"
#include "../HashMap.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

using namespace std;

class Integer {
  private:
    int i;

  public:
    Integer(int initial) : i(initial) {}
    Integer() : Integer(0) {};
    int get() const { return i; }
    void increment() { i++; }
};

static Integer * const handlerResult = new Integer();

/**
 * Ensures that the hash function produces no collisions for the commands used
 * in the project
 */
int main() {
  const vector<const char*> commands = {
    "PING",
    "PONG",
    "SYN",
    "GO",
    "STOP",
    "STRAIGHT",
    "PARK"
  };

  HashMap map;
  for (unsigned int i = 0; i < commands.size(); i++) {
    map.add(commands[i], [] { handlerResult->increment(); });
  }

  assert(map.size() == commands.size());

  for (unsigned int i = 0; i < commands.size(); i++) {
    VoidFunction f = map.get(commands[i]);
    assert(f != nullptr);
    f();
    assert(handlerResult->get() == i + 1);
  }

  cout << "Tests passed" << endl;

  return 0;
}
#endif
