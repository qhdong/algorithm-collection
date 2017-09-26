#include <iostream>
#include <string>
#include <stdexcept>
#include "skiplist.h"

using namespace std;

int main() {
    SkipNode<int, int, 20> node(2, 3);
    cout << node.key << ", " << node.value << endl;
    cout << node.forwards.size() << endl;
}
