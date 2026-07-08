# CPP Module 02 - Evaluation Guide

## ✅ CHECKLIST DE EVALUACIÓN

### **Preliminaries**

✅ **C++98 Standard Compliance**
- No external libraries used
- No C++11 features
- No `using namespace`
- No `friend` keyword
- No STL (this is module 02)
- Compiled with: `c++ -Wall -Wextra -Werror -std=c++98`

✅ **File Structure**
```
02/
├── ex00/
│   ├── Makefile
│   ├── Fixed.hpp
│   ├── Fixed.cpp
│   └── main.cpp
├── ex01/
│   ├── Makefile
│   ├── Fixed.hpp
│   ├── Fixed.cpp
│   └── main.cpp
├── ex02/
│   ├── Makefile
│   ├── Fixed.hpp
│   ├── Fixed.cpp
│   └── main.cpp
└── ex03/
    ├── Makefile
    ├── Fixed.hpp
    ├── Fixed.cpp
    ├── Point.hpp
    ├── Point.cpp
    ├── bsp.cpp
    └── main.cpp
```

✅ **Include Guards**
All `.hpp` files have:
```cpp
#ifndef CLASSNAME_HPP
# define CLASSNAME_HPP
// ...
#endif
```

✅ **Makefile Rules**
All Makefiles have: `all`, `clean`, `fclean`, `re`
No unnecessary relinking

---

## **EXERCISE 00: Orthodox Canonical Form**

### **How to Test**

```bash
cd 02/ex00
make
./fixed
```

### **Expected Output**

```
Default constructor called
Copy constructor called
Copy assignment operator called
getRawBits member function called
Default constructor called
Copy assignment operator called
getRawBits member function called
getRawBits member function called
0
getRawBits member function called
0
getRawBits member function called
0
Destructor called
Destructor called
Destructor called
```

### **Checklist**

✅ **Private Members**
- `int value;` - stores fixed-point value
- `static const int fractionalBits = 8;` - always 8

✅ **Orthodox Canonical Form (4 functions)**
1. Default constructor - initializes to 0
2. Copy constructor
3. Copy assignment operator
4. Destructor

✅ **Member Functions**
- `int getRawBits(void) const;`
- `void setRawBits(int const raw);`

✅ **Constructor/Destructor Messages**
Each prints when called

### **Verification Commands**

```bash
# Check include guards
grep -n "#ifndef FIXED_HPP" Fixed.hpp

# Check static const member
grep -n "static const int.*fractionalBits.*=.*8" Fixed.hpp

# Check all 4 canonical functions exist
grep -n "Fixed()" Fixed.hpp
grep -n "Fixed(const Fixed" Fixed.hpp
grep -n "operator=" Fixed.hpp
grep -n "~Fixed()" Fixed.hpp

# Run and verify output
./fixed | grep "Default constructor called" | wc -l  # Should be 2
./fixed | grep "Copy constructor called" | wc -l     # Should be 1
./fixed | grep "Destructor called" | wc -l           # Should be 3
```

---

## **EXERCISE 01: Useful Fixed-Point Class**

### **How to Test**

```bash
cd 02/ex01
make
./fixed
```

### **Expected Output**

```
Default constructor called
Int constructor called
Float constructor called
Copy constructor called
Copy assignment operator called
Float constructor called
Copy assignment operator called
Destructor called
a is 1234.43
b is 10
c is 42.4219
d is 10
a is 1234 as integer
b is 10 as integer
c is 42 as integer
d is 10 as integer
Destructor called
Destructor called
Destructor called
Destructor called
```

### **Checklist**

✅ **Additional Constructors**
- `Fixed(const int n);` - converts int to fixed-point
- `Fixed(const float f);` - converts float to fixed-point
- Both print messages

✅ **Conversion Functions**
- `float toFloat(void) const;` - converts to float
- `int toInt(void) const;` - converts to int

✅ **Stream Operator**
- `std::ostream& operator<<(std::ostream&, const Fixed&);`
- Declared outside class
- Prints floating-point representation

### **Additional Tests**

```bash
# Create test file
cat > test_ex01.cpp << 'EOF'
#include <iostream>
#include "Fixed.hpp"

int main(void) {
    // Test int constructor
    Fixed a(42);
    std::cout << "a (42) = " << a << std::endl;
    std::cout << "a.toInt() = " << a.toInt() << std::endl;

    // Test float constructor
    Fixed b(3.14f);
    std::cout << "b (3.14f) = " << b << std::endl;
    std::cout << "b.toFloat() = " << b.toFloat() << std::endl;

    // Test precision
    Fixed c(42.42f);
    std::cout << "c (42.42f) = " << c << std::endl;
    std::cout << "c.toInt() = " << c.toInt() << std::endl;

    return 0;
}
EOF

# Compile and run
c++ -Wall -Wextra -Werror -std=c++98 test_ex01.cpp Fixed.cpp -o test_ex01
./test_ex01
rm test_ex01.cpp test_ex01
```

---

## **EXERCISE 02: Operator Overloading**

### **How to Test**

```bash
cd 02/ex02
make
./fixed
```

### **Expected Output**

```
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
```

### **Checklist**

✅ **6 Comparison Operators**
- `operator>`
- `operator<`
- `operator>=`
- `operator<=`
- `operator==`
- `operator!=`

✅ **4 Arithmetic Operators**
- `operator+`
- `operator-`
- `operator*`
- `operator/`

✅ **4 Increment/Decrement Operators**
- `operator++(void)` - pre-increment
- `operator++(int)` - post-increment
- `operator--(void)` - pre-decrement
- `operator--(int)` - post-decrement

Increment by smallest epsilon: **1/256 = 0.00390625**

✅ **4 Static Functions**
- `static Fixed& min(Fixed& a, Fixed& b);`
- `static const Fixed& min(const Fixed& a, const Fixed& b);`
- `static Fixed& max(Fixed& a, Fixed& b);`
- `static const Fixed& max(const Fixed& a, const Fixed& b);`

### **Comprehensive Tests**

```bash
# Create comprehensive test
cat > test_ex02.cpp << 'EOF'
#include <iostream>
#include "Fixed.hpp"

int main(void) {
    Fixed a(10.5f);
    Fixed b(5.25f);

    // Test comparison operators
    std::cout << "=== COMPARISON OPERATORS ===" << std::endl;
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "a > b: " << (a > b) << std::endl;
    std::cout << "a < b: " << (a < b) << std::endl;
    std::cout << "a >= b: " << (a >= b) << std::endl;
    std::cout << "a <= b: " << (a <= b) << std::endl;
    std::cout << "a == b: " << (a == b) << std::endl;
    std::cout << "a != b: " << (a != b) << std::endl;

    // Test arithmetic operators
    std::cout << "\n=== ARITHMETIC OPERATORS ===" << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;

    // Test increment/decrement
    std::cout << "\n=== INCREMENT/DECREMENT ===" << std::endl;
    Fixed c(5.0f);
    std::cout << "c = " << c << std::endl;
    std::cout << "++c = " << ++c << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "c++ = " << c++ << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "--c = " << --c << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "c-- = " << c-- << std::endl;
    std::cout << "c = " << c << std::endl;

    // Test min/max
    std::cout << "\n=== MIN/MAX FUNCTIONS ===" << std::endl;
    std::cout << "Fixed::min(a, b) = " << Fixed::min(a, b) << std::endl;
    std::cout << "Fixed::max(a, b) = " << Fixed::max(a, b) << std::endl;

    Fixed const d(100.5f);
    Fixed const e(50.25f);
    std::cout << "Fixed::min(d, e) = " << Fixed::min(d, e) << std::endl;
    std::cout << "Fixed::max(d, e) = " << Fixed::max(d, e) << std::endl;

    return 0;
}
EOF

# Compile and run
c++ -Wall -Wextra -Werror -std=c++98 test_ex02.cpp Fixed.cpp -o test_ex02
./test_ex02
rm test_ex02.cpp test_ex02
```

### **Expected Test Output**

```
=== COMPARISON OPERATORS ===
a = 10.5, b = 5.25
a > b: 1
a < b: 0
a >= b: 1
a <= b: 0
a == b: 0
a != b: 1

=== ARITHMETIC OPERATORS ===
a + b = 15.75
a - b = 5.25
a * b = 55.125
a / b = 2

=== INCREMENT/DECREMENT ===
c = 5
++c = 5.00391
c = 5.00391
c++ = 5.00391
c = 5.00781
--c = 5.00391
c = 5.00391
c-- = 5.00391
c = 5

=== MIN/MAX FUNCTIONS ===
Fixed::min(a, b) = 5.25
Fixed::max(a, b) = 10.5
Fixed::min(d, e) = 50.25
Fixed::max(d, e) = 100.5
```

---

## **EXERCISE 03: BSP (Binary Space Partitioning)**

### **How to Test**

```bash
cd 02/ex03
make
./bsp
```

### **Expected Output**

```
Triangle vertices: A(0,0), B(10,0), C(5,10)

Point (5, 5): Inside the triangle
Point (15, 5): Outside the triangle
Point (0, 0) [vertex]: Outside the triangle
Point (5, 0) [edge]: Outside the triangle
```

### **Checklist**

✅ **Point Class**
- Private: `Fixed const x;` and `Fixed const y;`
- Default constructor (initializes to 0,0)
- Constructor with 2 floats
- Copy constructor
- Copy assignment operator (cannot reassign const members)
- Destructor

✅ **BSP Function**
```cpp
bool bsp(Point const a, Point const b, Point const c, Point const point);
```
- Returns `true` if point is **strictly inside** triangle
- Returns `false` if point is on edge or vertex
- Uses area method or barycentric coordinates

### **Comprehensive BSP Tests**

```bash
# Create comprehensive BSP test
cat > test_bsp.cpp << 'EOF'
#include <iostream>
#include "Point.hpp"

int main(void) {
    // Triangle: A(0,0), B(10,0), C(5,10)
    Point a(0.0f, 0.0f);
    Point b(10.0f, 0.0f);
    Point c(5.0f, 10.0f);

    std::cout << "Triangle: A(0,0), B(10,0), C(5,10)\n" << std::endl;

    // Test cases
    struct TestCase {
        const char* name;
        Point point;
        bool expected;
    };

    TestCase tests[] = {
        {"Center (5, 5)", Point(5.0f, 5.0f), true},
        {"Inside upper (5, 7)", Point(5.0f, 7.0f), true},
        {"Inside lower (5, 2)", Point(5.0f, 2.0f), true},
        {"Inside left (3, 3)", Point(3.0f, 3.0f), true},
        {"Inside right (7, 3)", Point(7.0f, 3.0f), true},
        {"Outside right (15, 5)", Point(15.0f, 5.0f), false},
        {"Outside left (-5, 5)", Point(-5.0f, 5.0f), false},
        {"Outside above (5, 15)", Point(5.0f, 15.0f), false},
        {"Outside below (5, -5)", Point(5.0f, -5.0f), false},
        {"Vertex A (0, 0)", Point(0.0f, 0.0f), false},
        {"Vertex B (10, 0)", Point(10.0f, 0.0f), false},
        {"Vertex C (5, 10)", Point(5.0f, 10.0f), false},
        {"Edge AB midpoint (5, 0)", Point(5.0f, 0.0f), false},
        {"Edge AC midpoint (2.5, 5)", Point(2.5f, 5.0f), false},
        {"Edge BC midpoint (7.5, 5)", Point(7.5f, 5.0f), false},
    };

    int passed = 0;
    int total = sizeof(tests) / sizeof(tests[0]);

    for (int i = 0; i < total; i++) {
        bool result = bsp(a, b, c, tests[i].point);
        bool correct = (result == tests[i].expected);

        std::cout << (correct ? "✓" : "✗") << " "
                  << tests[i].name << ": "
                  << (result ? "inside" : "outside")
                  << " (expected: " << (tests[i].expected ? "inside" : "outside") << ")"
                  << std::endl;

        if (correct) passed++;
    }

    std::cout << "\nPassed: " << passed << "/" << total << std::endl;

    return 0;
}
EOF

# Compile and run
c++ -Wall -Wextra -Werror -std=c++98 test_bsp.cpp Fixed.cpp Point.cpp bsp.cpp -o test_bsp
./test_bsp
rm test_bsp.cpp test_bsp
```

### **Expected BSP Test Output**

```
Triangle: A(0,0), B(10,0), C(5,10)

✓ Center (5, 5): inside (expected: inside)
✓ Inside upper (5, 7): inside (expected: inside)
✓ Inside lower (5, 2): inside (expected: inside)
✓ Inside left (3, 3): inside (expected: inside)
✓ Inside right (7, 3): inside (expected: inside)
✓ Outside right (15, 5): outside (expected: outside)
✓ Outside left (-5, 5): outside (expected: outside)
✓ Outside above (5, 15): outside (expected: outside)
✓ Outside below (5, -5): outside (expected: outside)
✓ Vertex A (0, 0): outside (expected: outside)
✓ Vertex B (10, 0): outside (expected: outside)
✓ Vertex C (5, 10): outside (expected: outside)
✓ Edge AB midpoint (5, 0): outside (expected: outside)
✓ Edge AC midpoint (2.5, 5): outside (expected: outside)
✓ Edge BC midpoint (7.5, 5): outside (expected: outside)

Passed: 15/15
```

---

## **QUICK VERIFICATION SCRIPT**

Save this as `verify_all.sh`:

```bash
#!/bin/bash

echo "=== CPP Module 02 Verification ==="
echo ""

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Check forbidden keywords
echo -e "${YELLOW}Checking for forbidden keywords...${NC}"
if grep -r "using namespace\|friend" 02/ex*/*.cpp 02/ex*/*.hpp 2>/dev/null; then
    echo -e "${RED}✗ Found forbidden keywords!${NC}"
else
    echo -e "${GREEN}✓ No forbidden keywords${NC}"
fi

# Test each exercise
for ex in ex00 ex01 ex02 ex03; do
    echo ""
    echo -e "${YELLOW}=== Testing $ex ===${NC}"
    cd 02/$ex

    # Clean and compile
    make fclean > /dev/null 2>&1
    if make > /dev/null 2>&1; then
        echo -e "${GREEN}✓ Compilation successful${NC}"

        # Run test
        echo "Output:"
        ./*

        echo -e "${GREEN}✓ Execution successful${NC}"
    else
        echo -e "${RED}✗ Compilation failed${NC}"
    fi

    cd ../..
done

echo ""
echo -e "${GREEN}=== Verification Complete ===${NC}"
```

Run with:
```bash
chmod +x verify_all.sh
./verify_all.sh
```

---

## **EVALUATION TIPS**

### **Common Issues to Check**

1. **Include guards missing** → Check all `.hpp` files
2. **Const correctness** → Getters should be `const`
3. **Self-assignment protection** → `if (this != &other)` in operator=
4. **Return by reference** → operator= returns `Fixed&`
5. **Static functions** → min/max should be callable as `Fixed::min(...)`
6. **Pre/post increment** → Different behavior and return types
7. **BSP edge cases** → Points on edges/vertices return false
8. **No relinking** → Run `make` twice, second time should say "nothing to do"

### **Questions to Ask During Defense**

1. **ex00**: "Why do we need the Orthodox Canonical Form?"
2. **ex01**: "How does the bit shift work in int to fixed-point conversion?"
3. **ex02**: "What's the difference between pre and post increment?"
4. **ex03**: "Why are x and y const in Point class?"
5. **General**: "What would happen if we didn't check for self-assignment?"

---

## **GRADING**

Each exercise is worth points. To pass:
- All exercises must compile
- All required functions must be present
- All tests must produce correct output
- Orthodox Canonical Form must be respected
- No forbidden functions/keywords

**Minimum passing grade: 80/100**

