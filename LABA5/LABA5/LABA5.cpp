#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

// ������� ������� ��� �����
class CustomException : public exception {
public:
    const char* what() const noexcept override {
        return "Custom Exception: Something went wrong.";
    }
};

template<typename T>
class TemplateClass {
private:
    vector<T> elements;

public:
    // ������ ������� �� �����
    void insert(const T& element) {
        elements.push_back(element);
    }

    // �������� ������� � �����
    void remove(const T& element) {
        auto it = find(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            elements.erase(it);
        }
    }

    // ������� �������� ����� �� �����
    void print() const {
        for (const auto& element : elements) {
            cout << element << " ";
        }
        cout << endl;
    }

    // �������������� ��������� '+' ��� ��'������� ���� ��'���� �����
    TemplateClass<T> operator+(const TemplateClass<T>& other) const {
        TemplateClass<T> result;
        result.elements = elements;
        result.elements.insert(result.elements.end(), other.elements.begin(), other.elements.end());
        return result;
    }

    // �������������� ��������� '-' ��� �������� ���� ��'���� �����
    TemplateClass<T> operator-(const TemplateClass<T>& other) const {
        TemplateClass<T> result;
        for (const auto& element : elements) {
            if (find(other.elements.begin(), other.elements.end(), element) == other.elements.end()) {
                result.elements.push_back(element);
            }
        }
        return result;
    }

    // �������������� ��������� ��������� '=' ��� �����
    TemplateClass<T>& operator=(const TemplateClass<T>& other) {
        if (this != &other) {
            elements = other.elements;
        }
        return *this;
    }
};

int main() {
    try {
        // ������� ������������ ����� TemplateClass � ����� int
        TemplateClass<int> intClass;
        intClass.insert(1);
        intClass.insert(2);
        intClass.insert(3);
        intClass.print();

        TemplateClass<int> otherIntClass;
        otherIntClass.insert(3);
        otherIntClass.insert(4);
        otherIntClass.insert(5);
        otherIntClass.print();

        // ��'������� ���� ��'���� intClass � otherIntClass
        TemplateClass<int> sum = intClass + otherIntClass;
        sum.print();

        // ³������� �������� otherIntClass �� intClass
        TemplateClass<int> diff = intClass - otherIntClass;
        diff.print();

        // ��������� ������� intClass ��'���� assignedIntClass
        TemplateClass<int> assignedIntClass;
        assignedIntClass = intClass;
        assignedIntClass.print();

        // ������� ������������ ����� TemplateClass � ����� std::string
        TemplateClass<string> stringClass;
        stringClass.insert("Hello");
        stringClass.insert("World");
        stringClass.print();

        // ������� �������
        throw CustomException();
    }
    catch (const exception& e) {
        cout << "Exception caught: " << e.what() << endl;
    }
    catch (...) {
        cout << "Unknown exception caught." << endl;
    }

    return 0;
}
