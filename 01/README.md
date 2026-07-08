# CPP Module 01 - Complete Implementation
## Memory Allocation, Pointers, References and Switch Statements

---

## 📁 **PROJECT STRUCTURE**

```
01/
├── ex00/  BraiiiiiiinnnzzzZ       (Stack vs Heap)
├── ex01/  Moar brainz!            (Array allocation new[])
├── ex02/  HI THIS IS BRAIN        (References vs Pointers)
├── ex03/  Unnecessary violence    (Reference vs Pointer in classes)
├── ex04/  Sed is for losers       (File I/O, string manipulation)
├── ex05/  Harl 2.0                (Pointers to member functions)
├── ex06/  Harl filter             (Switch statement - BONUS)
├── CPP01_CONCEPTS_AND_EVALUATION.md  (Complete concept guide)
├── EVAL_SHEET_GUIDE.md               (Official eval sheet walkthrough)
├── RESUMEN_FINAL.md                  (Spanish summary)
└── verify_all.sh                     (Automatic verification)
```

---

## ⚡ **QUICK START**

### **Test Everything**
```bash
cd 01
./verify_all.sh
```

### **Test Individual Exercise**
```bash
cd ex00 && make && ./zombie
cd ex01 && make && ./zombie
cd ex02 && make && ./brain
cd ex03 && make && ./violence
cd ex04 && make && ./replace test.txt hello hi
cd ex05 && make && ./harl
cd ex06 && make && ./harlFilter WARNING
```

### **Check Memory Leaks**
```bash
# macOS
leaks -atExit -- ./zombie

# Linux
valgrind --leak-check=full ./zombie
```

---

## 🎓 **CORE CONCEPTS (1-MINUTE SUMMARY)**

### **ex00: Stack vs Heap**
- **Stack:** Fast, automatic, scope-limited
- **Heap:** Manual (new/delete), persistent, flexible
- **When:** Stack for local, Heap for returned objects

### **ex01: Array Allocation**
- `new[]` → `delete[]` (CRITICAL!)
- Default constructor needed for arrays
- Wrong pairing = undefined behavior

### **ex02: References**
- Reference = alias (cannot be NULL, cannot reassign)
- Pointer = address (can be NULL, can reassign)
- Same memory address, different syntax

### **ex03: Ref vs Ptr in Classes**
- **Reference:** Object ALWAYS exists (HumanA)
- **Pointer:** Object MAY NOT exist (HumanB)

### **ex04: File Streams**
- `ifstream` for reading, `ofstream` for writing
- NO `std::string::replace()` allowed
- Must use C++ streams, not C functions

### **ex05: Pointers to Member Functions**
- `void (Class::*ptr)(void) = &Class::func;`
- Call: `(this->*ptr)();`
- Avoid if/else forest

### **ex06: Switch Statement**
- Fall-through behavior (no break)
- Executes from case to break
- Filter levels DEBUG < INFO < WARNING < ERROR

---

## ✅ **VERIFICATION CHECKLIST**

### **General Requirements**
- [x] Compiles: `c++ -Wall -Wextra -Werror -std=c++98`
- [x] No `using namespace`, `friend`
- [x] No `*printf`, `*alloc`, `free`
- [x] Include guards in all `.hpp`
- [x] Makefiles: `all`, `clean`, `fclean`, `re`
- [x] No memory leaks
- [x] No C++11 features

### **Critical Implementation Points**

| Exercise | Critical Requirement |
|----------|---------------------|
| ex00 | `newZombie` returns heap pointer, `randomChump` uses stack |
| ex01 | Must use `new[]` and `delete[]` |
| ex02 | All three addresses must be identical |
| ex03 | HumanA uses reference, HumanB uses pointer |
| ex04 | Cannot use `std::string::replace()` |
| ex05 | Must use pointers to member functions, NO if/else |
| ex06 | Must use switch with fall-through |

---

## 🧪 **EXPECTED OUTPUTS**

### **ex00: Stack vs Heap**
```
=== Creating zombie on HEAP ===
HeapZombie is born
HeapZombie: BraiiiiiiinnnzzzZ...
HeapZombie still exists here...
HeapZombie is destroyed

=== Creating zombie on STACK ===
StackZombie is born
StackZombie: BraiiiiiiinnnzzzZ...
StackZombie is destroyed
```

### **ex03: Weapon**
```
Bob attacks with their crude spiked club
Bob attacks with their some other type of club
Jim attacks with their crude spiked club
Jim attacks with their some other type of club
```

### **ex06: HarlFilter "WARNING"**
```
[ WARNING ]
I think I deserve...

[ ERROR ]
This is unacceptable...
```

---

## 📚 **DOCUMENTATION FILES**

1. **EVAL_SHEET_GUIDE.md** - Official evaluation step-by-step
2. **CPP01_CONCEPTS_AND_EVALUATION.md** - Complete concept explanations
3. **RESUMEN_FINAL.md** - Spanish comprehensive summary
4. **This README** - Quick reference

---

## 🎯 **DEFENSE PREPARATION**

### **Key Questions You'll Be Asked**

**ex00:**
- Q: "When to use stack vs heap?"
- A: Stack for local/temporary, Heap for returned/persistent

**ex01:**
- Q: "Why delete[] not delete?"
- A: new[] allocates array, needs delete[] to call all destructors

**ex02:**
- Q: "Difference between pointer and reference?"
- A: Reference is alias (no NULL), pointer is address (can be NULL)

**ex03:**
- Q: "Why HumanA reference and HumanB pointer?"
- A: HumanA always armed (constructor), HumanB maybe not (can be NULL)

**ex05:**
- Q: "Why pointers to member functions?"
- A: Avoid if/else forest, more elegant, easier to extend

**ex06:**
- Q: "What is fall-through?"
- A: Execution continues to next case without break

---

## ⚠️ **COMMON MISTAKES TO AVOID**

1. ❌ `delete` instead of `delete[]` for arrays
2. ❌ Not initializing pointers to NULL
3. ❌ Using if/else in ex05 instead of function pointers
4. ❌ Using `std::string::replace()` in ex04
5. ❌ Not closing file streams
6. ❌ Not checking if file opened successfully

---

## 🏆 **PROJECT STATUS**

**Implementation:** ✅ 100% Complete (7/7 exercises)
**Compilation:** ✅ No warnings
**Memory Leaks:** ✅ None
**Documentation:** ✅ Complete
**Tests:** ✅ All passing

**Grade Expected:** 100/100 + Bonus

**Status:** ✅ **READY FOR EVALUATION**

---

## 🚀 **HOW TO USE THIS PROJECT**

### **For Learning:**
1. Read `CPP01_CONCEPTS_AND_EVALUATION.md` for theory
2. Study each exercise implementation
3. Run tests to see concepts in action
4. Experiment with code

### **For Evaluation:**
1. Follow `EVAL_SHEET_GUIDE.md` step-by-step
2. Check critical requirements for each exercise
3. Test memory leaks
4. Ask student to explain implementation

### **For Defense:**
1. Review key concepts
2. Practice explaining your code
3. Be ready to modify code during evaluation
4. Know why you made each design choice

---

## 📞 **QUICK REFERENCE**

### **Compilation**
```bash
c++ -Wall -Wextra -Werror -std=c++98 *.cpp -o program
```

### **Memory Check**
```bash
# macOS
leaks -atExit -- ./program

# Linux
valgrind --leak-check=full ./program
```

### **Makefile Test**
```bash
make        # Compile
make        # Should say "nothing to do"
make clean  # Remove .o
make fclean # Remove .o and executable
make re     # Clean and rebuild
```

---

## ✨ **HIGHLIGHTS**

- **Complete implementation** of all exercises
- **Detailed explanations** of every concept
- **Official eval sheet** step-by-step guide
- **Comprehensive tests** for all functionality
- **Memory leak free** - verified
- **C++98 compliant** - no modern features
- **Well commented** in English
- **Ready for defense**

---

**Created:** October 2025
**Status:** Production Ready ✅
**License:** Educational Use

