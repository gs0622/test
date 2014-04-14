/* queue example */
#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char **argv)
{
    std::queue<int> q;
    cout << "1:sz=" << q.size() << '\n';
    for (int i=0; i<10; i++) q.push(i);
    cout << "2:sz=" << q.size() << '\n';
    while (!q.empty()) {
        cout << q.front() << "-" << q.back() << " ";
        q.pop();
    }
    return 0;
}
