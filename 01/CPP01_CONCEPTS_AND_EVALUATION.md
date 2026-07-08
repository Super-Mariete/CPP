# CPP Module 01 - Complete Guide
## Memory Allocation, Pointers to Members, References and Switch Statements

---

## 📚 **CORE CONCEPTS EXPLAINED**

### **1. Stack vs Heap Memory (ex00)**

#### **Stack Allocation**
```cpp
void function() {
    Zombie stackZombie("Stack");  // Created on stack
    // Automatically destroyed when function ends
}
```

**Characteristics:**
- **Automatic** - Created and destroyed automatically
- **Fast** - Just move stack pointer
- **Limited size** - Stack size is limited (usually ~1-8MB)
- **Scope-based** - Dies when scope ends

#### **Heap Allocation**
```cpp
Zombie* heapZombie = new Zombie("Heap");  // Created on heap
// Must manually delete
delete heapZombie;
```

**Characteristics:**
- **Manual** - You control lifetime with `new` and `delete`
- **Slower** - Requires system calls
- **Large size** - Limited only by RAM
- **Persistent** - Survives beyond function scope

#### **When to use what?**

| Situation | Use |
|-----------|-----|
| Object needed only in function | **Stack** |
| Object returned from function | **Heap** |
| Large objects (>1MB) | **Heap** |
| Unknown lifetime | **Heap** |
| Small, temporary objects | **Stack** |

**Example from ex00:**
```cpp
// newZombie() - Returns pointer (HEAP)
// Zombie exists beyond function scope
Zombie* newZombie(std::string name) {
    return new Zombie(name);  // MUST delete later
}

// randomChump() - Creates on STACK
// Zombie dies when function ends
void randomChump(std::string name) {
    Zombie zombie(name);  // Auto-destroyed
    zombie.announce();
}
```

---

### **2. Array Allocation with new[] (ex01)**

#### **Single Object**
```cpp
Zombie* z = new Zombie("Single");
delete z;  // Use delete
```

#### **Array of Objects**
```cpp
Zombie* horde = new Zombie[5];  // Array of 5 zombies
delete[] horde;  // Use delete[] (with brackets!)
```

**Critical Rule:**
```
new    → delete
new[]  → delete[]
```

**Wrong pairing = undefined behavior!**

#### **Why Default Constructor is Needed**
```cpp
class Zombie {
public:
    Zombie();  // REQUIRED for array allocation
    Zombie(std::string name);  // NOT used with new[]
};

// When you do: new Zombie[5]
// C++ calls default constructor 5 times
```

**Implementation:**
```cpp
Zombie* zombieHorde(int N, std::string name) {
    Zombie* horde = new Zombie[N];  // Calls default constructor N times

    for (int i = 0; i < N; i++)
        horde[i].setName(name);  // Then set name

    return horde;
}
```

---

### **3. References vs Pointers (ex02, ex03)**

#### **Pointer**
```cpp
std::string str = "Hello";
std::string* ptr = &str;  // Pointer to str

// Access
std::cout << *ptr;  // Dereference with *
ptr->length();      // Arrow for members
```

**Characteristics:**
- Can be **NULL**
- Can be **reassigned**
- Requires **dereferencing** (*)
- Stored as **address**

#### **Reference**
```cpp
std::string str = "Hello";
std::string& ref = str;  // Reference (alias) to str

// Access
std::cout << ref;    // Direct access, no *
ref.length();        // Dot for members
```

**Characteristics:**
- **Cannot be NULL**
- **Cannot be reassigned** (always refers to same object)
- **No dereferencing** needed
- **Same as original** variable

#### **Memory Addresses (ex02)**
```cpp
std::string brain = "HI THIS IS BRAIN";
std::string* stringPTR = &brain;
std::string& stringREF = brain;

// All three print SAME address
&brain      // 0x7ffd123abc
stringPTR   // 0x7ffd123abc
&stringREF  // 0x7ffd123abc
```

**Key insight:** References are just **syntax sugar** for pointers!

---

### **4. When to Use Reference vs Pointer in Classes (ex03)**

#### **HumanA - Uses Reference**
```cpp
class HumanA {
private:
    Weapon& weapon;  // Reference: ALWAYS armed

public:
    HumanA(std::string name, Weapon& weapon)
        : weapon(weapon)  // MUST initialize in list
    {
    }
};
```

**Why reference?**
- Human **ALWAYS** has a weapon
- Weapon **never changes**
- Passed in constructor
- **Cannot be NULL**

#### **HumanB - Uses Pointer**
```cpp
class HumanB {
private:
    Weapon* weapon;  // Pointer: may NOT have weapon

public:
    HumanB(std::string name)
        : weapon(NULL)  // Starts with no weapon
    {
    }

    void setWeapon(Weapon& weapon) {
        this->weapon = &weapon;  // Set later
    }
};
```

**Why pointer?**
- Human **may NOT** have weapon initially
- Weapon can be **set later**
- Not passed in constructor
- **Can be NULL**

#### **Decision Tree**

```
Does object ALWAYS exist?
├─ YES → Use Reference
│  └─ Set in constructor
│
└─ NO → Use Pointer
   └─ Can be NULL
   └─ Set with setter
```

---

### **5. File Streams (ex04)**

#### **Input File Stream**
```cpp
std::ifstream inputFile("filename.txt");

if (!inputFile.is_open()) {
    // Error handling
}

std::string line;
while (std::getline(inputFile, line)) {
    // Process line
}

inputFile.close();
```

#### **Output File Stream**
```cpp
std::ofstream outputFile("output.txt");

if (!outputFile.is_open()) {
    // Error handling
}

outputFile << "Text to write" << std::endl;

outputFile.close();
```

#### **String Operations**
```cpp
// Find substring
size_t pos = str.find("hello");
if (pos != std::string::npos) {
    // Found at position pos
}

// Substring
std::string sub = str.substr(start, length);

// Length
size_t len = str.length();
```

#### **Replace Implementation (without std::string::replace)**
```cpp
std::string replaceAll(std::string str,
                      const std::string& s1,
                      const std::string& s2)
{
    std::string result;
    size_t pos = 0;
    size_t found;

    while ((found = str.find(s1, pos)) != std::string::npos)
    {
        result += str.substr(pos, found - pos);  // Before s1
        result += s2;                             // Replace with s2
        pos = found + s1.length();                // Skip s1
    }
    result += str.substr(pos);  // Remaining part

    return result;
}
```

---

### **6. Pointers to Member Functions (ex05)**

#### **Concept**
Member functions belong to a class, not standalone. You need **special syntax**.

#### **Declaration**
```cpp
// Pointer to member function
void (ClassName::*functionPtr)(void);

// Example
void (Harl::*ptr)(void) = &Harl::debug;
```

#### **Calling**
```cpp
// Need object instance
Harl harl;
(harl.*ptr)();  // Call via object

// Or with pointer to object
Harl* ptrHarl = &harl;
(ptrHarl->*ptr)();  // Call via pointer
```

#### **Array of Function Pointers (ex05)**
```cpp
void Harl::complain(std::string level)
{
    // Array of level names
    std::string levels[4] = {
        "DEBUG", "INFO", "WARNING", "ERROR"
    };

    // Array of function pointers
    void (Harl::*functions[4])(void) = {
        &Harl::debug,
        &Harl::info,
        &Harl::warning,
        &Harl::error
    };

    // Find matching level
    for (int i = 0; i < 4; i++) {
        if (levels[i] == level) {
            (this->*functions[i])();  // Call function
            return;
        }
    }
}
```

**Why this is better than if/else:**
```cpp
// BAD: Forest of if/else
if (level == "DEBUG")
    debug();
else if (level == "INFO")
    info();
else if (level == "WARNING")
    warning();
else if (level == "ERROR")
    error();

// GOOD: Array lookup (O(n) but cleaner)
// Easy to extend, maintain, and read
```

---

### **7. Switch Statement (ex06)**

#### **Basic Syntax**
```cpp
switch (value) {
    case 0:
        // code
        break;
    case 1:
        // code
        break;
    default:
        // code
}
```

#### **Fall-Through Behavior (ex06)**
```cpp
switch (levelIndex) {
    case 0:  // DEBUG
        harl.complain("DEBUG");
        // NO BREAK - falls through
    case 1:  // INFO
        harl.complain("INFO");
        // NO BREAK - falls through
    case 2:  // WARNING
        harl.complain("WARNING");
        // NO BREAK - falls through
    case 3:  // ERROR
        harl.complain("ERROR");
        break;  // STOP here
    default:
        std::cout << "Invalid" << std::endl;
}
```

**What happens with `./harlFilter "WARNING"`:**
```
1. levelIndex = 2 (WARNING)
2. Enter at case 2
3. Print WARNING
4. Fall through to case 3
5. Print ERROR
6. Break
```

**Output:**
```
[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

---

## ✅ **EVALUATION CHECKLIST**

### **General Requirements**

| Requirement | Check |
|------------|-------|
| C++98 standard | ✅ |
| Compiles with `-Wall -Wextra -Werror -std=c++98` | ✅ |
| No forbidden functions (*printf, *alloc, free) | ✅ |
| No `using namespace` | ✅ |
| No `friend` keyword | ✅ |
| Include guards in all headers | ✅ |
| No memory leaks | ✅ |
| Proper Makefile (all, clean, fclean, re) | ✅ |

---

### **Exercise 00: BraiiiiiiinnnzzzZ**

**Files:** `Makefile, main.cpp, Zombie.{hpp, cpp}, newZombie.cpp, randomChump.cpp`

#### **Requirements:**

✅ **Zombie Class:**
- Private attribute: `std::string name`
- Member function: `void announce(void)`
- Prints: `<name>: BraiiiiiiinnnzzzZ...`

✅ **Functions:**
- `Zombie* newZombie(std::string name)` - creates on heap
- `void randomChump(std::string name)` - creates on stack

✅ **Destructor:**
- Prints message with zombie name

#### **Test:**
```bash
cd 01/ex00
make
./zombie
```

**Expected behavior:**
- Heap zombies live until `delete`
- Stack zombies destroyed at end of scope
- All zombies print destructor message

#### **Questions to Answer:**
- "When should you allocate on stack vs heap?"
  - **Stack:** Temporary, function-local objects
  - **Heap:** Objects that outlive function, returned pointers

---

### **Exercise 01: Moar brainz!**

**Files:** `Makefile, main.cpp, Zombie.{hpp, cpp}, zombieHorde.cpp`

#### **Requirements:**

✅ **Function:**
```cpp
Zombie* zombieHorde(int N, std::string name);
```
- Allocates N zombies in **single allocation** (`new[]`)
- Initializes all with same name
- Returns pointer to first zombie

✅ **Memory Management:**
- Must use `delete[]` (not `delete`)
- No memory leaks

#### **Test:**
```bash
cd 01/ex01
make
./zombie
valgrind ./zombie  # Check for leaks
```

**Expected behavior:**
- Creates array of N zombies
- All announce correctly
- All destructors called with `delete[]`

---

### **Exercise 02: HI THIS IS BRAIN**

**Files:** `Makefile, main.cpp`

#### **Requirements:**

✅ **Variables:**
```cpp
std::string brain = "HI THIS IS BRAIN";
std::string* stringPTR = &brain;
std::string& stringREF = brain;
```

✅ **Output:**
- Memory addresses (all same)
- Values (all same)

#### **Test:**
```bash
cd 01/ex02
make
./brain
```

**Expected output:**
```
=== MEMORY ADDRESSES ===
Address of brain:       0x...
Address in stringPTR:   0x...  (same)
Address of stringREF:   0x...  (same)

=== VALUES ===
Value of brain:         HI THIS IS BRAIN
Value pointed by PTR:   HI THIS IS BRAIN
Value pointed by REF:   HI THIS IS BRAIN
```

#### **Question:**
- "What's the difference between pointer and reference?"
  - **Pointer:** Can be NULL, reassignable, needs dereferencing
  - **Reference:** Cannot be NULL, cannot reassign, no dereferencing

---

### **Exercise 03: Unnecessary violence**

**Files:** `Makefile, main.cpp, Weapon.{hpp, cpp}, HumanA.{hpp, cpp}, HumanB.{hpp, cpp}`

#### **Requirements:**

✅ **Weapon Class:**
- Private: `std::string type`
- `const std::string& getType() const`
- `void setType(std::string type)`

✅ **HumanA:**
- Has `Weapon&` (reference)
- Takes weapon in constructor
- **Always armed**

✅ **HumanB:**
- Has `Weapon*` (pointer)
- Does NOT take weapon in constructor
- Has `setWeapon()` function
- **May not be armed**

✅ **Attack function:**
Prints: `<name> attacks with their <weapon type>`

#### **Test:**
```bash
cd 01/ex03
make
./violence
```

**Expected output:**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

#### **Question:**
- "Why reference for HumanA and pointer for HumanB?"
  - **HumanA:** Always has weapon → reference (cannot be NULL)
  - **HumanB:** Sometimes has weapon → pointer (can be NULL)

---

### **Exercise 04: Sed is for losers**

**Files:** `Makefile, main.cpp, *.{hpp, cpp}` (your choice)

#### **Requirements:**

✅ **Program:**
```bash
./replace <filename> <s1> <s2>
```
- Opens `<filename>`
- Creates `<filename>.replace`
- Replaces all `s1` with `s2`

✅ **Forbidden:**
- `std::string::replace()` - MUST implement manually
- C file functions (fopen, etc.)

✅ **Must handle:**
- File not found
- Empty strings
- No matches
- Multiple occurrences

#### **Test:**
```bash
cd 01/ex04
make

# Create test file
echo -e "hello world\nhello everyone\ngoodbye hello" > test.txt

# Run replacement
./replace test.txt hello hi

# Check output
cat test.txt.replace
```

**Expected:**
```
hi world
hi everyone
goodbye hi
```

#### **Additional Tests:**
```bash
# Empty s1
./replace test.txt "" hi
# Should handle gracefully

# Non-existent file
./replace nonexistent.txt hello hi
# Should print error

# s1 not found
./replace test.txt xyz abc
# Should create empty output
```

---

### **Exercise 05: Harl 2.0**

**Files:** `Makefile, main.cpp, Harl.{hpp, cpp}`

#### **Requirements:**

✅ **Harl Class:**
- Private functions: `debug()`, `info()`, `warning()`, `error()`
- Public function: `void complain(std::string level)`

✅ **Must use pointers to member functions:**
```cpp
void (Harl::*functionPtr)(void) = &Harl::debug;
```

✅ **NO forest of if/else allowed!**

#### **Test:**
```bash
cd 01/ex05
make
./harl
```

**Expected output:**
```
[ DEBUG ]
I love having extra bacon...

[ INFO ]
I cannot believe adding extra bacon...

[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

#### **Code Review:**
Check that implementation uses:
```cpp
void (Harl::*functions[4])(void) = {
    &Harl::debug,
    &Harl::info,
    &Harl::warning,
    &Harl::error
};

// Then calls:
(this->*functions[i])();
```

---

### **Exercise 06: Harl filter**

**Files:** `Makefile, main.cpp, Harl.{hpp, cpp}`

#### **Requirements:**

✅ **Program:**
```bash
./harlFilter <level>
```
- Prints messages from `level` and above
- Uses **switch statement**
- Uses **fall-through** behavior

✅ **Executable name:** `harlFilter`

#### **Test:**
```bash
cd 01/ex06
make
./harlFilter "WARNING"
```

**Expected output:**
```
[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

```bash
./harlFilter "DEBUG"
```

**Expected:** All 4 levels (DEBUG, INFO, WARNING, ERROR)

```bash
./harlFilter "INVALID"
```

**Expected:**
```
[ Probably complaining about insignificant problems ]
```

#### **Code Review:**
Must use switch with fall-through:
```cpp
switch (levelIndex) {
    case 0:
        // DEBUG
        // NO break
    case 1:
        // INFO
        // NO break
    case 2:
        // WARNING
        // NO break
    case 3:
        // ERROR
        break;
    default:
        // Invalid
}
```

---

## 🧪 **COMPREHENSIVE TEST SCRIPT**

Save as `test_all.sh` in `01/` directory:

```bash
#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "=== CPP Module 01 Complete Test ==="
echo ""

# Test ex00
echo -e "${YELLOW}=== Ex00: Stack vs Heap ===${NC}"
cd ex00
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    ./zombie
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

# Test ex01
echo -e "${YELLOW}=== Ex01: Zombie Horde ===${NC}"
cd ex01
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    ./zombie
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

# Test ex02
echo -e "${YELLOW}=== Ex02: References ===${NC}"
cd ex02
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    ./brain
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

# Test ex03
echo -e "${YELLOW}=== Ex03: Weapon ===${NC}"
cd ex03
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    ./violence
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

# Test ex04
echo -e "${YELLOW}=== Ex04: Replace ===${NC}"
cd ex04
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    echo "Test line with hello world" > test.txt
    ./replace test.txt hello hi
    cat test.txt.replace
    rm -f test.txt test.txt.replace
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

# Test ex05
echo -e "${YELLOW}=== Ex05: Harl ===${NC}"
cd ex05
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    ./harl
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

# Test ex06
echo -e "${YELLOW}=== Ex06: HarlFilter ===${NC}"
cd ex06
make fclean > /dev/null 2>&1
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✓ Compilation OK${NC}"
    echo "Test WARNING:"
    ./harlFilter "WARNING"
    echo ""
else
    echo -e "${RED}✗ Compilation FAILED${NC}"
fi
cd ..

echo -e "${GREEN}=== All tests complete ===${NC}"
```

Run with:
```bash
chmod +x test_all.sh
./test_all.sh
```

---

## 📊 **GRADING SUMMARY**

| Exercise | Points | Key Concept |
|----------|--------|-------------|
| ex00 | Mandatory | Stack vs Heap |
| ex01 | Mandatory | Array allocation (new[]) |
| ex02 | Mandatory | References vs Pointers |
| ex03 | Mandatory | When to use ref vs ptr |
| ex04 | Mandatory | File I/O, string manipulation |
| ex05 | Mandatory | Pointers to member functions |
| ex06 | Bonus | Switch statement |

**Minimum to pass:** ex00-ex05 (100%)
**Bonus:** ex06

---

## 🎯 **COMMON MISTAKES TO AVOID**

1. ❌ **Using `delete` instead of `delete[]` for arrays**
   ```cpp
   Zombie* horde = new Zombie[5];
   delete horde;    // WRONG!
   delete[] horde;  // CORRECT!
   ```

2. ❌ **Not initializing pointer to NULL**
   ```cpp
   Weapon* weapon;  // Uninitialized!
   Weapon* weapon = NULL;  // CORRECT
   ```

3. ❌ **Using forest of if/else in ex05**
   ```cpp
   // WRONG - not allowed!
   if (level == "DEBUG")
       debug();
   else if (level == "INFO")
       info();
   ```

4. ❌ **Using `std::string::replace()` in ex04**
   - Forbidden! Must implement manually

5. ❌ **Forgetting to close files**
   ```cpp
   inputFile.close();   // MUST close
   outputFile.close();  // MUST close
   ```

6. ❌ **Not checking file open**
   ```cpp
   std::ifstream file("test.txt");
   if (!file.is_open())  // MUST check
       return error;
   ```

---

## ✅ **FINAL CHECKLIST**

- [ ] All exercises compile without warnings
- [ ] No memory leaks (check with valgrind)
- [ ] No forbidden functions
- [ ] Proper include guards
- [ ] Makefiles work correctly
- [ ] Code is readable and well-commented
- [ ] All test cases pass
- [ ] Can explain all concepts during defense

**Status: ✅ READY FOR EVALUATION**

