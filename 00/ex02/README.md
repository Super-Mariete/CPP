# Exercise 02: The Job Of Your Dreams

## 📋 Resumen del Ejercicio

Este es un ejercicio de **ingeniería inversa**. Te dan:
- ✅ `Account.hpp` - El header con la definición de la clase
- ✅ `tests.cpp` - El archivo de pruebas (NO MODIFICAR)
- ✅ `19920104_091532.log` - El output esperado

Tu trabajo:
- ❌ `Account.cpp` - Este archivo estaba "perdido" y tú debes recrearlo

## 🎯 Objetivo

Implementar `Account.cpp` para que el programa produzca **exactamente** el mismo output que el archivo de log (excepto los timestamps que serán diferentes).

## 🔍 ¿Qué hace el programa?

Simula un sistema bancario simple con:
- Creación de 8 cuentas con diferentes saldos iniciales
- Depósitos en todas las cuentas
- Retiros de todas las cuentas (algunos se rechazan por falta de fondos)
- Cierre de todas las cuentas al final

## 📚 Conceptos Clave de C++ que Aprenderás

### 1. **Variables Estáticas (static)**

En C++, `static` en una clase significa que la variable es **compartida por todas las instancias**:

```cpp
class Account {
private:
    static int _nbAccounts;  // Una sola variable para TODAS las cuentas
    int _amount;             // Cada cuenta tiene su propio amount
};
```

**Analogía en C:**
```c
// En C harías algo así con variables globales:
int g_nbAccounts = 0;

struct Account {
    int amount;
};
```

### 2. **Inicialización de Variables Estáticas**

Las variables estáticas se inicializan FUERA de la clase:

```cpp
// En el .cpp (NO en el .hpp):
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
```

### 3. **Métodos Estáticos**

Métodos que NO necesitan una instancia específica:

```cpp
// Puedes llamarlo así:
int total = Account::getTotalAmount();  // Sin crear un objeto Account
```

### 4. **Constructor y Destructor**

```cpp
Account::Account(int initial_deposit)  // Constructor - se llama al crear
{
    // Código de inicialización
}

Account::~Account(void)  // Destructor - se llama al destruir
{
    // Código de limpieza
}
```

### 5. **this pointer**

Apunta a la instancia actual:

```cpp
this->_amount = initial_deposit;  // El amount de ESTA cuenta específica
```

## 🔧 Cómo Compilar y Probar

```bash
# Ir al directorio
cd /Users/marta/Documents/PROJECTS/42-docker-enviroment/CPP/00/ex02

# Compilar
make

# Ejecutar
./account

# Comparar con el log (los timestamps serán diferentes)
./account > my_output.log
diff my_output.log ../docs/19920104_091532.log
```

## 📊 Output Esperado (con timestamps diferentes)

```
[20251005_123456] index:0;amount:42;created
[20251005_123456] index:1;amount:54;created
...
[20251005_123456] accounts:8;total:20049;deposits:0;withdrawals:0
...
[20251005_123456] index:0;p_amount:42;deposit:5;amount:47;nb_deposits:1
...
[20251005_123456] index:0;p_amount:47;withdrawal:refused
...
[20251005_123456] index:0;amount:47;closed
...
```

## 🎓 Lecciones Importantes

1. **Variables Estáticas**: Todas las instancias comparten la misma variable
2. **Constructor/Destructor**: Se llaman automáticamente al crear/destruir objetos
3. **const**: Métodos que no modifican el objeto
4. **Timestamp**: Uso de `<ctime>` para fechas
5. **std::setw() y std::setfill()**: Para formatear números con ceros a la izquierda

## ⚠️ Nota del Subject

> El orden en que se llaman los destructores puede variar según tu compilador/OS.
> Así que tus destructores pueden ser llamados en orden inverso.

Esto es normal y no afecta la evaluación.

## ✅ Criterios de Éxito

- ✓ Compila sin errores ni warnings
- ✓ El output coincide con el log (excepto timestamps)
- ✓ Las operaciones bancarias funcionan correctamente
- ✓ Los retiros se rechazan cuando no hay fondos suficientes

## 🔄 Nota Importante

Este ejercicio es **OPCIONAL** según el subject:
> "Completing exercise 02 is not mandatory to pass this module."

Sin embargo, es excelente para practicar conceptos de C++.
