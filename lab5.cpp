#include <iostream>
#include <cstring>

template <typename T, class Self>
class Container {
protected:
    T* elements;
    std::size_t size;
    std::size_t allocated;

public:
    const int static ALLOCATION_MAX = 255;

    Container(T* elements, const std::size_t& size, const std::size_t allocated)
    : elements(elements), size(size), allocated(allocated) {
        if (allocated > ALLOCATION_MAX)
            throw std::runtime_error("Allocation limit exceeded");
    }

    virtual bool operator!=(const Self& other) const = 0;

    virtual bool operator>(const Self& other) const = 0;

    virtual Self operator-(const T& t) = 0;

    virtual const T& operator[](const std::size_t& index) const {
        return elements[index];
    }

    virtual operator const T*() const {
        return elements;
    }

    virtual T* begin() const {
        return elements;
    }

    virtual T* end() const {
        return elements + size;
    }

    virtual std::size_t getSize() const {
        return size;
    }

    virtual std::size_t getAllocated() const {
        return allocated;
    }

    virtual ~Container() {
        delete[] elements;
    }
};

class String : public Container<char, String> {
public:
    String(const char* str) : String(str, strlen(str) + 1) {
    }

    String(const char* str, const std::size_t& size, const std::size_t& allocated = 0)
    : Container<char, String>(new char[allocated ? allocated : size], size, allocated ? allocated : size) {
        strncpy_s(elements, size, str, size);
    }

    String(String&& other) noexcept : Container<char, String>(other.elements, other.size, other.allocated) {
        std::cout << "Moved\n";
    }

    bool operator!=(const String& other) const override {
        return strncmp(elements, other.elements, std::min(size, other.size)) != 0;
    }

    bool operator>(const String& other) const override {
        for (std::size_t i = 0, j = 0; i < size; i++) {
            if (elements[i] != other.elements[j++])
                j = 0;

            if (j == other.size - 1)
                return true;
        }

        return false;
    }

    String operator-(const char& c) override {
        auto newString = new char[size];
        std::size_t newSize = 0;

        for (auto& ch : *this)
            if (ch != c)
                newString[newSize++] = ch;

        return {newString, newSize, size};
    }

    friend std::ostream& operator<<(std::ostream& out, const String& str) {
        return out << str.elements;
    }
};

auto main() -> int {
    auto string = String("Hello, world!");
    auto noLs = string - 'l';

    std::cout << string << '\n' // prints "Hello, world!", thanks to the overloaded operator<<
              << noLs << '\n' // removes all 'l' characters
              << std::boolalpha // enables bool output (true/false instead of 1/0)
              << (string > String("world")) << '\n' // checks if string contains "world"
              << (noLs != String("Hello, world!")) << '\n'; // checks if noLs is not equal to "Hello, world!"

    std::cout << "string size: " << string.getSize() << ", allocated: " << string.getAllocated() << '\n'
              << "noLs size:   " << noLs.getSize()   << ", allocated: " << noLs.getAllocated() << '\n';
}
