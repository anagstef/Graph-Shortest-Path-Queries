#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char** argv){
  queue<uint32_t> q;

  q.push(10);
  q.push(3432);
  q.push(345345);
  q.push(56565);
  q.push(47467);
  q.push(324);
  q.pop();
  q.push(1343242);
  q.push(2343240);
  q.push(2340);
  q.push(3420);
  q.push(1233334);
  q.push(1234);
  q.push(340);
  q.push(5550);
  q.push(16666);

  while (!q.empty()) {
    uint32_t i = q.front();
    q.pop();
    cout << i << endl;

  }




    return 0;

}
