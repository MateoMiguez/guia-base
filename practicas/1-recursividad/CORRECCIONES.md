# Correcciones — Práctica 1: Recursividad

**Fecha de corrección:** 2026-04-20
**Tag/Branch evaluado:** `main`
**Repositorio:** `MateoMiguez/guia-base`

---

## Integrantes del equipo

| Integrante (README) | Líneas aportadas (+/-) | % estimado por líneas | Commits (referencia) | Committers unificados |
|---------------------|------------------------|-----------------------|----------------------|-----------------------|
| Mateo Miguez        | —                      | —                     | —                    | Sin mapeo confiable   |
| Santino Morrone     | —                      | —                     | —                    | Sin mapeo confiable   |

---

## Método aplicado

- Tests del grupo: Ejecutados
- Tests de cátedra: No ejecutados
- Revisión estática del código: Sí
- Evidencia breve: se ejecutó `cmake --build cmake-build-debug --target test_capicua test_palindromos test_producto test_fibonacci test_resto test_separador_miles test_mafia_china test_onda_digital test_divisible_por_7 test_explosion --parallel` y `ctest --test-dir cmake-build-debug -R 'test_(capicua|palindromos|producto|fibonacci|resto|separador_miles|mafia_china|onda_digital|divisible_por_7|explosion)' --output-on-failure`; no hay en el repo una batería separada de tests de cátedra. El build global del repo falla además en `practicas/0-repaso/tests/test_04_jugadores.c`, fuera del alcance de esta corrección.

---

## Corrección de la práctica

### Ejercicio 1 — `esCapicua()`

**Estado: 🚫 NO IMPLEMENTADO**

La función existe en `recursividad.c`, pero el cuerpo está vacío. No hay caso base ni paso recursivo para resolver el problema.

### Ejercicio 2 — `esPalindromo()`

**Estado: 🚫 NO IMPLEMENTADO**

La función está declarada y definida con cuerpo vacío. No implementa la comparación recursiva del string ni contempla strings vacíos o de longitud 1.

### Ejercicio 3 — `productoRecursivo()`

**Estado: 🚫 NO IMPLEMENTADO**

La función tiene cuerpo vacío. Falta resolver el producto mediante sumas sucesivas y manejar signos correctamente, como pide el enunciado.

### Ejercicio 4 — `terminoSerieDeFibonacci()`

**Estado: 🚫 NO IMPLEMENTADO**

La función está vacía. No hay implementación recursiva ni casos base para `n`.

### Ejercicio 5 — `restoRecursivo()`

**Estado: 🚫 NO IMPLEMENTADO**

La función figura en `recursividad.h`, pero no tiene implementación en `recursividad.c`. Tampoco hay lógica para el cálculo recursivo por restas sucesivas.

### Ejercicio 6 — `agregarSeparadorMiles()`

**Estado: 🚫 NO IMPLEMENTADO**

La función principal y su auxiliar `agregarSeparadoresRecursivo()` están vacías. No reserva ni construye el string resultado, por lo que además queda pendiente el manejo correcto de memoria.

### Ejercicio 7 — `chinos()`

**Estado: 🚫 NO IMPLEMENTADO**

La función existe con cuerpo vacío. No genera la estructura recursiva pedida para el nivel de reunión.

### Ejercicio 8 — `ondaDigital()`

**Estado: 🚫 NO IMPLEMENTADO**

La función está declarada en `recursividad.h`, pero no aparece implementada en `recursividad.c`. No hay generación de la salida con `_`, `|` y segmentos altos/bajos.

### Ejercicio 9 — `esDivisiblePor7()`

**Estado: 🚫 NO IMPLEMENTADO**

La función está definida con cuerpo vacío. No aplica el algoritmo recursivo indicado en el enunciado.

### Ejercicio 10 — `explosion()`

**Estado: 🚫 NO IMPLEMENTADO**

`explosion()` y la auxiliar `explosionRecursiva()` están vacías. No construyen el arreglo de fragmentos ni actualizan `size`, así que el ejercicio completo quedó sin desarrollar.

---

## Revisión de tests

| Test | Estado | Observaciones |
|------|--------|---------------|
| `test_capicua.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `esCapicua()` ni hace aserciones. |
| `test_palindromos.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `esPalindromo()` ni hace aserciones. |
| `test_producto.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `productoRecursivo()` ni hace aserciones. |
| `test_fibonacci.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `terminoSerieDeFibonacci()` ni hace aserciones. |
| `test_resto.c` | 🚫 No entregado | El `main()` está vacío y retorna `0`; no hay ninguna prueba sobre `restoRecursivo()`. |
| `test_separador_miles.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `agregarSeparadorMiles()` ni valida memoria o resultado. |
| `test_mafia_china.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `chinos()` ni compara salidas. |
| `test_onda_digital.c` | 🚫 No entregado | El archivo contiene solo un `main()` vacío; no hay llamadas ni verificaciones. |
| `test_divisible_por_7.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `esDivisiblePor7()` ni hace aserciones. |
| `test_explosion.c` | 🚫 No entregado | El `main()` solo imprime un título y retorna `0`; no llama a `explosion()` ni valida el arreglo devuelto. |

### Tests con casos de borde faltantes

- Todos los archivos `test_*.c` de `practicas/1-recursividad/tests/` carecen de casos nominales, borde, inválidos y de más de un nivel de recursión porque no ejecutan ninguna verificación real.

---

## Resumen

| Categoría | Estado |
|-----------|--------|
| Archivos `.h` sin modificar (contenido) | ✅ |
| `esCapicua` | 🚫 No implementado |
| `esPalindromo` | 🚫 No implementado |
| `productoRecursivo` | 🚫 No implementado |
| `terminoSerieDeFibonacci` | 🚫 No implementado |
| `restoRecursivo` | 🚫 No implementado |
| `agregarSeparadorMiles` | 🚫 No implementado |
| `chinos` | 🚫 No implementado |
| `ondaDigital` | 🚫 No implementado |
| `esDivisiblePor7` | 🚫 No implementado |
| `explosion` | 🚫 No implementado |
| Ejercicios correctos | 0 de 10 correctos; 0 con mejoras opcionales; 0 incorrectos; 10 no implementados |
| Tests entregados | 0 de 10 |
| Tests con buena cobertura | 0 de 10 |

Observación sobre headers: hubo historial de commits sobre `practicas/1-recursividad/recursividad.h`, pero el contenido actual solo difiere en formato respecto del commit base del repositorio; no se detectó cambio semántico.
