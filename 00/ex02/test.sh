#!/bin/bash

# Script para probar el ejercicio 02

echo "=========================================="
echo "  Testing Exercise 02: Account Class"
echo "=========================================="
echo ""

# Compilar
echo "📦 Compiling..."
make re
if [ $? -ne 0 ]; then
    echo "❌ Compilation failed!"
    exit 1
fi
echo "✅ Compilation successful!"
echo ""

# Ejecutar y guardar output
echo "🚀 Running program..."
./account > my_output.log
echo "✅ Program executed!"
echo ""

# Mostrar el output
echo "📄 Program output:"
echo "=========================================="
cat my_output.log
echo "=========================================="
echo ""

# Comparar (ignorando timestamps)
echo "🔍 Comparing with expected output..."
echo "(Ignoring timestamps - they will be different)"
echo ""

# Extraer solo la parte después de los timestamps para comparar
sed 's/\[.*\] //' my_output.log > my_output_clean.log
sed 's/\[.*\] //' ../docs/19920104_091532.log > expected_clean.log

if diff -q my_output_clean.log expected_clean.log > /dev/null; then
    echo "✅ Output matches perfectly! (ignoring timestamps)"
else
    echo "⚠️  Output differences found (ignoring timestamps):"
    diff my_output_clean.log expected_clean.log
fi

# Cleanup
rm -f my_output_clean.log expected_clean.log

echo ""
echo "=========================================="
echo "  Test Complete!"
echo "=========================================="
