#include <iostream>
#include <unordered_map>
using namespace std;

class Node {
public:
  int value;
  Node *next;

  Node(int value) {
    this->value = value;
    next = nullptr;
  }

  Node(const Node& other) {
    value = other.value;
    next = other.next;
  }

  ~Node() {
    if (!next)
      delete next;
  }
};

class List {
public:
  Node *first;
  Node *last;

  List() { first = last = nullptr; }

  ~List() {
    if (!first)
      delete first;
  }

  void addLast(int value) {
    if (!first) {
      first = new Node(value);
      last = first;
    } else {
      Node *temp = new Node(value);
      last->next = temp;
      last = temp;
    }
  }

};


bool IsPermutation(List &first_list, List &second_list, int &n, int &m) {
    if (n != m) {
        return false;
    }

    unordered_map<int, int> hash_table;
    int x;
    int count_distinct = 0;
    for (Node* p = first_list.first; p != nullptr; p = p->next) {
        x = p->value;
        if (hash_table.count(x)) {
            hash_table[x] = hash_table[x] + 1;
        } else {
            hash_table[x] = 1;
            count_distinct++;
        }
    }

    for (Node* p = second_list.first; p != nullptr; p = p->next) {
        x = p->value;
        if (hash_table.count(x)) {
            hash_table[x] = hash_table[x] - 1;
            if (hash_table[x] < 0) {
                return false;
            } else {
                if (hash_table[x] == 0) {
                    count_distinct--;
                }
            }
        } else {
            return false;
        }
    }
    return count_distinct == 0;
}


int main()
{

    int n, m;
    cin >> n >> m;

    List first_list, second_list;
    int x;

    for (int i = 0; i < n; ++i) {
        cin >> x;
        first_list.addLast(x);
    }

    for (int i = 0; i < m; ++i) {
        cin >> x;
        second_list.addLast(x);
    }

    cout << IsPermutation(first_list, second_list, n, m);

    return 0;
}
