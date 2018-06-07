#include <iostream>
#include <vector>
#include <string>

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

List merge(const List &a, const List &b) {
    List temp;
    Node *x = a.first, *y = b.first;
    if (!x) return b;
    if (!y) return a;

    while (x && y) {
        if (x->value >= y->value) {
            temp.addLast(y->value);
            y = y->next;
        } else {
            temp.addLast(x->value);
            x = x->next;
        }
    }

    if (!x)
        while (y) {
            temp.addLast(y->value);
            y = y->next;
        }

    if (!y)
        while (x) {
            temp.addLast(x->value);
            x = x->next;
        }

    return temp;
}

List unique(const List &list) {
    List temp;
    Node *start = list.first;

    while (start) {
        while (start && temp.last && temp.last->value == start->value)
            start = start->next;
        if (start) {
            temp.addLast(start->value);
            start = start->next;
        }
    }

    return temp;
}

List reunion(const List &a, const List &b) {
    List c = merge(a, b);
    return unique(c);
}

List intersection(const List &a, const List &b) {
    List temp;
    Node *x = a.first, *y = b.first;
    if (!x || !y) return temp;

    while (x && y) {
        if (x->value == y->value) {
            temp.addLast(x->value);
            x = x->next;
            y = y->next;
        }
        while (x && y && x->value > y->value) y = y->next;

        while (x && y && x->value < y->value) x = x->next;
    }
    return temp;
}

List difference(const List &a, const List &b) {
    List temp;
    Node *x = a.first, *y = b.first;
    if (!x) return temp;
    if (!y) return a;

    while (x && y) {
        if (x->value == y->value) {
            x = x->next;
            y = y->next;
        }
        while (x && y && x->value > y->value) y = y->next;

        while (x && y && x->value < y->value) {
            temp.addLast(x->value);
            x = x->next;
        }
    }

    while (x) {
        temp.addLast(x->value);
        x = x->next;
    }

    return temp;
}

int main() {
    List l1, l2;
    std::string operation_type;
    int m, n;
    int temp;

    std::cin >> operation_type;

    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> temp;
        l1.addLast(temp);
    }

    std::cin >> m;
    for (int i = 0; i < m; i++) {
        std::cin >> temp;
        l2.addLast(temp);
    }

    if (operation_type == "reuniune") {
        reunion(l1, l2).print();
    } else if (operation_type == "diferenta") {
        difference(l1, l2).print();
    } else if (operation_type == "intersectie") {
        intersection(l1, l2).print();
    } else if (operation_type == "all") {
        reunion(l1, l2).print();
        difference(l1, l2).print();
        intersection(l1, l2).print();
    }

    return 0;
}
