include <iostream>
#include <initializer_list>
using namespace std;

template<typename T>
class Stack
{
    private:
        T* _arr;
        T* _end;
        T* _top;

    public:
        explicit Stack(int size)
        {
            _arr = new T[size];
            _end = _arr + size - 1;
            _top = _arr - 1;
        }

        Stack(int size, initializer_list<T> list)
        {
            if (list.size() > size)
                throw "List size is more than Stack size";

            _arr = new T[size];
            for (auto i : list)
            {
                *(_arr++) = i;
            }
            _arr -= list.size();

            _end = _arr + size - 1;
            _top = _end - (size - list.size());
        }

        Stack(const Stack& stack)
        {
            _arr = new T[stack.getStackSize()];
            for (size_t i = 0; i < stack.getStackSize(); i++)
            {
                _arr[i] = stack._arr[i];
            }

            _end = _arr + stack.getStackSize() - 1;
            _top = _end - (stack.getStackSize() - stack.getCurrentSize());
        }

        Stack(Stack&& stack)
        {
            _arr = stack._arr;
            _end = stack._end;
            _top = stack._top;

            stack._arr = nullptr;
            stack._end = nullptr;
            stack._top = nullptr;
        }

        ~Stack()
        {
            delete[] _arr;
            _arr = nullptr;
            _top = nullptr;
            _end = nullptr;
        }

        bool isFull() const
        {
            return _top == _end;
        }

        bool isEmpty() const
        {
            return _top + 1 == _arr;
        }

        Stack& clear()
        {
            _top = _arr - 1;
            return *this;
        }

        Stack& push(T value)
        {
            if (!isFull())
                *++_top = value;

            return *this;
        }

        T peek() const
        {
            if (isEmpty())
                throw "Out if range";

            return *_top;
        }

        T pop()
        {
            if (isEmpty())
                throw "Out if range";

            return *_top--;
        }

        int getCurrentSize() const
        {
            return _top - _arr + 1;
        }

        int getStackSize() const
        {
            return _end - _arr + 1;
        }

        friend ostream& operator<<(ostream& out, const Stack& stack)
        {
            int* current = stack._arr;
            while (current <= stack._top)
            {
                out << *current++ << '\t';
            }
            out << endl;

            return out;
        }
};

int main()
{
    Stack<int> stack{ 4, {1, 2, 3} };

    stack.push(123);

    cout << stack << endl;

    return 0;
}
