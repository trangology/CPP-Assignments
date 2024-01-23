#include "doubly_linked_list.h"

int_list_t::node_t* int_list_t::get_node(const size_t pos) {
    if (pos >= size)
    {
        throw std::out_of_range("The position out of range!");
    }

    if (pos <= (size - pos))
    {
        node_t* cur_node = head;
        for (size_t i = 0; i < pos; i++) 
        {
            cur_node = cur_node->next;
        }
        return cur_node;
    }

    node_t* cur_node = tail;
    for (size_t i = size - 1; i >= pos; i--) 
    {
        cur_node = cur_node->prev;
    }
    return cur_node;
};

int_list_t::int_list_t() {
    size = 0;
    head = tail = nullptr;
}

int_list_t::int_list_t(const int_list_t& other) : int_list_t() {
    node_t* new_node = other.head;

    while (new_node)
    {
        push_back(new_node->value);
        new_node = new_node->next;
    }
}

int_list_t::int_list_t(size_t count, int value) : int_list_t()
{
    for (size_t i = 0; i < count; i++) 
    {
        push_back(value);
    }
};

int_list_t::~int_list_t()
{
    clear();
    delete head;
    delete tail;
}

int_list_t& int_list_t::operator=(const int_list_t& other)
{
    if (&other != this) {
        int_list_t tmp(other);
        swap(tmp);
    }

    return *this;
}

int& int_list_t::operator[](const size_t pos)
{
    node_t* cur_node = get_node(pos);

    return cur_node->value;
}

const int int_list_t::operator[](size_t pos) const {
    if (pos >= size)
    {
        throw std::out_of_range("The position out of range!");
    }

    if (pos <= (size - pos))
    {
        node_t* cur_node = head;
        for (size_t i = 0; i < pos; i++) {
            cur_node = cur_node->next;
        }
        return cur_node->value;
    }

    node_t* cur_node = tail;
    for (size_t i = size - 1; i >= pos; i--) {
        cur_node = cur_node->prev;
    }
    return cur_node->value;
}

int& int_list_t::back() {
    return tail->value;
}

const int int_list_t::back() const {
    return tail->value;
}

int& int_list_t::front() {
    return head->value;
}

const int int_list_t::front() const {
    return head->value;
}

void int_list_t::clear() {
    auto cur_node = head;
    while (cur_node)
    {
        node_t* next = cur_node->next;
        delete cur_node;
        cur_node = next;
    }
    size = 0;
    head = nullptr;
    tail = nullptr;
}

size_t int_list_t::_size() const {
    return size;
}

bool int_list_t::empty() const {
    return size == 0;
}

void int_list_t::insert(size_t pos, int new_val)
{
    if (empty() || pos == 0)
    {
        push_front(new_val);
        return;
    }

    if (pos == size - 1) {
        push_back(new_val);
        return;
    }

    // cur_node is the node allocated at the given position.
    // new_node is the node allocated between prev_node and cur_node
    node_t* cur_node = get_node(pos)->next;
    node_t* prev_node = cur_node->prev;

    auto * new_node = new node_t(new_val, prev_node, cur_node);

    cur_node->prev = new_node;
    prev_node->next = new_node;

    size++;
}

void int_list_t::push_front(int new_val) {
    auto* new_node = new node_t(new_val, nullptr, nullptr);

    if (head == nullptr)
    {
        head = new_node;
        tail = head;
    }
    else
    {
        head->prev = new_node;
        new_node->next = head;
        head = new_node;
    }

    size++;
}

void int_list_t::push_back(int new_val) {
    auto* new_node = new node_t(new_val, nullptr, nullptr);

    if (head == nullptr)
    {
        head = new_node;
        tail = head;
    }
    else
    {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }

    size++;
}

void int_list_t::erase(size_t pos) {
    if (pos == 0) {
        pop_front();
    }

    if (pos == size - 1) {
        pop_back();
    }

    // tmp is the node will be deleted
    node_t* tmp = get_node(pos);

    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;

    size--;
}

void int_list_t::pop_front() {
    if (head == nullptr)
    {
        std::cout << "List was not declared!";
        return;
    }

    if (size > 1)
    {
        head = head->next;
        head->prev = nullptr;
    }

    delete head;
    size--;
}

void int_list_t::pop_back() {
    if (tail == nullptr)
    {
        std::cout << "List was not declared!";
        return;
    }

    if (size > 1)
    {
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete tail;
    size--;
}

int_list_t int_list_t::splice(size_t start_pos, size_t count) {
    node_t* cur_node = get_node(start_pos);

    int_list_t new_list;

    for (size_t i = 0; i < count; i++)
    {
        cur_node = cur_node->next;
        new_list.push_back(cur_node->value);
    }

    return new_list;
}

int_list_t& int_list_t::merge(int_list_t& other) {
    node_t* tmp = other.head;
    while (tmp)
    {
        this->push_back(tmp->value);
        tmp = tmp->next;
    }

    this->size += other.size;

    delete& other;
    return *this;
}

void int_list_t::reverse() {
    if (head == nullptr)
    {
        std::cout << "Cannot reverse an empty list!" << std::endl;
        return;
    }

    tail = head;
    node_t* cur_node = head;
    node_t* tmp_node = nullptr;

    while (cur_node)
    {
        tmp_node = cur_node->prev;
        cur_node->prev = cur_node->next;
        cur_node->next = tmp_node;
        cur_node = cur_node->prev;
    }

    if (tmp_node != nullptr)
    {
        head = tmp_node->prev;
    }
}

void int_list_t::swap(int_list_t& other) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}

std::istream& operator>>(std::istream& input, int_list_t& list)
{
    int tmp = 0;

    while (input >> tmp) 
    {
        list.push_back(tmp);
    }
    
    return input;
}

std::ostream& operator<<(std::ostream& output, const int_list_t& list) {
    int_list_t::node_t* cur_node = list.head;

    while (cur_node)
    {
        output << cur_node->value << " ";
        cur_node = cur_node->next;
    }

    return output;
};
