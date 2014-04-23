/* priority_queue example */
#include <iostream>
#include <queue>        // std::priority_queue

using namespace std;

int main(int argc, char **argv)
{
    std::priority_queue<int, std::vector<int>, std::greater<int> > q;
    cout << "1:sz=" << q.size() << '\n';
    /*3 1 -4 2 8 -1000 2*/
    q.push(3);
    q.push(1);
    q.push(-4);
    q.push(2);
    q.push(8);
    q.push(-1000);
    q.push(2);
    cout << "2:sz=" << q.size() << '\n';
    while (!q.empty()) {
        cout << q.top() << " ";
        q.pop();
    }
    return 0;
}
