#include "doubly_linked_list.cpp"

int main() {
    // create 2 lists
    size_t size = 5;
    int_list_t list_1(size, 0);
    int_list_t list_2(5,1);

    std::cout << "This is list 1: " << list_1 << std::endl;
    std::cout << "This is list 2: " << list_2 << std::endl;

    // test method merge():
    int_list_t list_3(3,2);
    list_1.merge(list_3);
    std::cout << "This is list 3: " << list_1 << std::endl;

    // test 2 methods push_back() and back()
    std::cout << "Last element of list 1 before using push_back(): " << list_1.back() << std::endl;
    list_1.push_back(20);
    std::cout << "List 1 after push_back(20): " << list_1 << std::endl;

    // test 2 methods push_front() and front()
    std::cout << "First element of list 1 before using push_front(): " << list_1.front() << std::endl;
    list_1.push_front(10);
    std::cout << "List 1 after push_front(10): " << list_1 << std::endl;

    if (!list_1.empty())
    {
        std::cout << "This doubly linked list is not empty!" << std::endl;
    }

    // test method reverse()
    list_1.reverse();
    std::cout << "List 1 after reverse: " << list_1 << std::endl;

    // test method swap()
    std::cout << "List 1 before swap: " << list_1 << std::endl;
    list_1.swap(list_2);
    std::cout << "List 1 after swap with list_2: " << list_1 << std::endl;

    // test method insert()
    list_1.insert(3, 7);
    std::cout << "List 1 after insert 7 at index 3: " << list_1 << std::endl;

    // test method erase()
    list_1.erase(3);
    std::cout << "List 1 after erase element at index 3: " << list_1 << std::endl;

    // test method splice()
    int_list_t list_4 = list_1.splice(3, 2);
    std::cout << "Got list 4 after splice 2 elements from index 3 of list 1: " << list_4 << std::endl;

    // test method clear()
    list_1.clear();
    std::cout << "Size of list 1 after clear: " << list_1._size() << std::endl;

    return 0;
}