#include <iostream>

using namespace std;

class safe_c_array_t {
    private:
        int size;  
        int *arr;

    public:
        // constructor
        safe_c_array_t(int size) {  
            this->size = size;
            this->arr = new int [size];
        };

        // destructor
        ~safe_c_array_t() {     
            delete [] arr; 

            cout << "Destroyed " << this << endl;
        };

        // finds element at the specified position
        int operator[](int pos) {  
            if (pos >= size) {
                cout << "The position out of range." << endl;
                return -1;
            }

            return arr[pos];
        }

        safe_c_array_t operator=(const safe_c_array_t &other) {  
            if (this != &other) {   
                delete [] this->arr;
                this->arr = new int [other.size]; 
                for (int i = 0; i < other.size; i++) {
                    arr[i] = other.arr[i];
                }
            } 
        }

};

int main() {
    safe_c_array_t array_1 = safe_c_array_t(5);
    safe_c_array_t array_2 = array_1; 

    array_1[2];

    for (int i = 0; i < 5; i++) {
        cout << array_1[i] << " ";
    } 
    cout << endl;

    array_1.~safe_c_array_t();

    // makes sure that all values of array_2 equal array_1 
    for (int i = 0; i < 5; i++) {
        cout << array_2[i] << " ";
    }
    cout << endl;
}