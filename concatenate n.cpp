#include <iostream>
#include <vector>

class Node {
   public:
    int value;
    Node *next;

    Node(int value) {
        this->value = value;
        next = nullptr;
    }

    ~Node() {
        if (!next) delete next;
    }
};

class List {
   public:
    Node *first;
    Node *last;

    List() { first = last = nullptr; }

    ~List() {
        if (!first) delete first;
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

    void print() {
        if (!first) {
            std::cout << "List is empty!" << std::endl;
            return;
        }
        Node *temp = first;
        while (temp) {
            std::cout << temp->value << " ";
            temp = temp->next;
        }
        std::cout << "\n";
    }
};

List concatenate(const std::vector<List> &lists) {
  List temp;
  Node *start;
  for (const auto &list : lists) {
    start = list.first;
    while (start) {
      temp.addLast(start->value);
      start = start->next;
    }
  }
  return temp;
}

int main() {
    std::vector<List> v;
    int m, temp;

    std::cin >> m;
    for (int i = 0; i < m; i++) {
        List l;
        int n;

        std::cin >> n;
        for (int j = 0; j < n; j++) {
            std::cin >> temp;
            l.addLast(temp);
        }

        v.push_back(l);
    }

    concatenate(v).print();

    return 0;
}
