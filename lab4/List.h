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

        List(const std::initializer_list<T>& list = {}) {
            for (auto& i : list) {
                append(i);
            }
        }

        List(const List& other) {
            for (auto& i : other) {
                append(i);
            }
        }

        void append(const T& value) {
            auto node = new Node{
                .previous = tail,
                .next = nullptr,
                .value = value,
            };

            if (head == nullptr && tail == nullptr) {
                head = node;
            } else if (tail != nullptr) {
                tail->next = node;
                tail = node;
            } else {
                head->next = node;
                node->previous = head;
                tail = node;
            }

            count++;
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

        template <typename P>
        int removeIf(P predicate) {
            int removedCount = 0;

            for (auto node = head; node != nullptr;) {
                if (predicate(node->value)) {
                    auto next = node->next;

                    if (node->previous != nullptr)
                        node->previous->next = node->next;
                    else
                        head = node->next;

                    if (node->next != nullptr)
                        node->next->previous = node->previous;
                    else
                        tail = node->previous;

                    delete node;
                    node = next;
                    removedCount++;
                } else {
                    node = node->next;
                }
            }

            return removedCount;
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

        std::size_t size() {
            return count;
        }

        ~List() {
            for (auto node = head; node != nullptr; node = node->next) {
                delete node->previous;
            }
        }
    private:
        Node *head{}, *tail{};
        std::size_t count{};
    };
}

#endif //OPERATING_SYSTEMS_LABS_LIST_H
