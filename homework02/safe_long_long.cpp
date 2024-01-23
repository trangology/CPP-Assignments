#include <iostream>
#include <cmath>
 
class safe_long_long_t {
    public:
 
        safe_long_long_t(long long n) {
            this->num = n;
        }
 
        safe_long_long_t &operator=(const safe_long_long_t &n) {
            *this = n;
            return *this;
        }
 
        long long get_num() {
            return this->num;
        }
 
        void update_num(long long n) {
            this->num = n;
        }

        // safe_long_long_t &operator++();
        // safe_long_long_t &operator--();

        // safe_long_long_t &operator*(const safe_long_long_t &n);
        
        // safe_long_long_t &operator+(const safe_long_long_t &n);
        // safe_long_long_t &operator-(const safe_long_long_t &n);

        // safe_long_long_t &operator+=(const safe_long_long_t &n);
        // safe_long_long_t &operator-=(const safe_long_long_t &n);
        // safe_long_long_t &operator*=(const safe_long_long_t &n);
        // safe_long_long_t &operator/=(const safe_long_long_t &n);
 
        friend std::istream &operator>>(std::istream &in, safe_long_long_t n);
        friend std::ostream &operator<<(std::ostream &out, safe_long_long_t n);
 
    private:
	    long long num;
};

safe_long_long_t operator+=(safe_long_long_t &n1, safe_long_long_t &n2) {
    long long result = n1.get_num() + n2.get_num();
    return safe_long_long_t(result);
}

safe_long_long_t operator-=(safe_long_long_t &n1, safe_long_long_t &n2) {
    return safe_long_long_t(n1.get_num() - n2.get_num());
}

safe_long_long_t operator++(safe_long_long_t &n) {
    return safe_long_long_t(n.get_num() + 1);
}

safe_long_long_t operator--(safe_long_long_t &n) {
    return safe_long_long_t(n.get_num() - 1);
}

safe_long_long_t operator+(safe_long_long_t &n1, safe_long_long_t &n2) {
    return safe_long_long_t(n1.get_num() + n2.get_num());
}

safe_long_long_t operator-(safe_long_long_t &n1, safe_long_long_t &n2) {
    return safe_long_long_t(n1.get_num() - n2.get_num());
}

safe_long_long_t operator*(safe_long_long_t &n1, safe_long_long_t &n2) {
    return safe_long_long_t(n1.get_num() * n2.get_num());
}

safe_long_long_t operator/(safe_long_long_t &n1, safe_long_long_t &n2) {
    return safe_long_long_t(n1.get_num() / n2.get_num());
}
 
bool operator==(safe_long_long_t &n1, safe_long_long_t &n2) {
    return n1.get_num() == n2.get_num();
}
 
bool operator!=(safe_long_long_t &n1, safe_long_long_t &n2) {
    return !(n1.get_num() == n2.get_num());
}
 
bool operator>=(safe_long_long_t &n1, safe_long_long_t &n2) {
    return n1.get_num() >= n2.get_num();
}
 
bool operator<=(safe_long_long_t &n1, safe_long_long_t &n2) {
    return n1.get_num() <= n2.get_num();
}

std::istream &operator>>(std::istream &in, safe_long_long_t n) {
    long long num;
    in >> num;
    n.update_num(num);
    return in;
}
 
std::ostream &operator<<(std::ostream &out, safe_long_long_t n) {
    out << n.get_num(); 
    return out;
}
 
 
int main() {
    safe_long_long_t n1(5);
    safe_long_long_t n2(10);
 
    std::cout << n1 << " + " << n2 << " = " << n1 + n2 << '\n';
    std::cout << n1 << " - " << n2 << " = " << n1 - n2 << '\n';
    std::cout << n1 << " * " << n2 << " = " << n1 * n2 << '\n';
    std::cout << n1 << " / " << n2 << " = " << n1 / n2 << '\n';
    std::cout << n1 << "++ = " << operator++(n1) << '\n';
    std::cout << n2 << "-- =" << operator--(n2) << '\n';

    if (n1 != n2) {
        std::cout << "Are n1 and n2 different? Yes, they are!" << '\n';
    }
 
    return 0;
}
 