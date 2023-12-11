#ifndef OPERATING_SYSTEMS_LABS_LIST_H
#define OPERATING_SYSTEMS_LABS_LIST_H

#include <initializer_list>

namespace app {
    template <typename T>
    class List {
    public:
        struct Node {
            Node *previous, *next;
            T value;
        };

        List(std::initializer_list<T> list = {}) {
            for (auto& i : list) {
                append(i);
            }
        }

        void append(const T& value) {
            auto node = new Node();
            node->value = value;
            node->previous = tail;
            node->next = nullptr;

            if (tail != nullptr)
                tail->next = node;
            else
                head = node;

            tail = node;
        }

        void prepend(const T& value) {
            auto node = new Node();
            node->value = value;
            node->previous = nullptr;
            node->next = head;

            if (head != nullptr)
                head->previous = node;
            else
                tail = node;

            head = node;
        }

        void pop() {
            if (tail == nullptr)
                return;

            auto node = tail;
            tail = tail->previous;

            if (tail != nullptr)
                tail->next = nullptr;
            else
                head = nullptr;

            delete node;
        }

        void push() {
            if (head == nullptr)
                return;

            auto node = head;
            head = head->next;

            if (head != nullptr)
                head->previous = nullptr;
            else
                tail = nullptr;

            delete node;
        }

        void insert(const T& value, const std::size_t& index) {
            if (index == 0) {
                prepend(value);
                return;
            }

            auto node = head;
            for (std::size_t i = 0; i < index; i++) {
                if (node == nullptr)
                    return;

                node = node->next;
            }

            auto newNode = new Node();
            newNode->value = value;
            newNode->previous = node->previous;
            newNode->next = node;

            node->previous->next = newNode;
            node->previous = newNode;
        }

        void remove(const std::size_t& index) {
            if (index == 0) {
                push();
                return;
            }

            auto node = head;
            for (std::size_t i = 0; i < index; i++) {
                if (node == nullptr)
                    return;

                node = node->next;
            }

            node->previous->next = node->next;
            node->next->previous = node->previous;

            delete node;
        }

        class Iterator {
            Node* node;
        public:
            Iterator(Node* node) : node(node) {
            }

            Iterator& operator++() {
                node = node->next;
                return *this;
            }

            Iterator& operator--() {
                node = node->previous;
                return *this;
            }

            T& operator*() {
                return node->value;
            }

            bool operator==(const Iterator& other) const {
                return node == other.node;
            }

            bool operator!=(const Iterator& other) const {
                return node != other.node;
            }
        };

        Iterator begin() const {
            return Iterator(head);
        }

        Iterator end() const {
            return Iterator(nullptr);
        }

        template <typename P>
        List<T> filter(P predicate) {
            auto list = List<T>();

            for (auto& value : *this) {
                if (predicate(value)) {
                    list.append(value);
                }
            }

            return list;
        }

        template <class R, typename F>
        R reduce(F reducer, R initialValue) const {
            R result = initialValue;

            for (auto& value : *this) {
                result = reducer(result, value);
            }

            return result;
        }

        template <typename F>
        void forEach(F consumer) const {
            for (auto& value : *this) {
                consumer(value);
            }
        }

        ~List() {
            for (auto node = head; node != nullptr;) {
                auto next = node->next;
                delete node;
                node = next;
            }
        }
    private:
        Node *head{}, *tail{};
    };
}

#endif //OPERATING_SYSTEMS_LABS_LIST_H
