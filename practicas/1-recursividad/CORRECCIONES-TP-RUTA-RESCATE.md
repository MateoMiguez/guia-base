# Correcciones — TP Integrador: Ruta de Rescate en Mina

**Fecha de corrección:** 2026-05-06
**Referencia evaluada:** `origin/main` (commit `dc52083`)
**Repositorio:** https://github.com/MateoMiguez/guia-base

---

## Integrantes del equipo

Según `README.md` de la raíz del repo:

- Mateo Miguez
- Santino Morrone

| Integrante (README) | Líneas aportadas (+/-) | % estimado por líneas | Commits (referencia)     | Committers unificados                      |
|---------------------|------------------------|-----------------------|--------------------------|--------------------------------------------|
| Mateo Miguez        | +232/-103              | 53.86%                | 2 (`a174bf3`, `55910a4`) | `Mateo Miguez <mateojosemiguez@gmail.com>` |
| Santino Morrone     | +287/-0                | 46.14%                | 1 (`8e83e45`)            | `sanntiism <santinomorrone05@gmail.com>`   |

Observación: alcance considerado = `tp_ruta_mina.c`, `tests/test_tp_ruta_mina.c`, `prueba1_entrada.txt`,
`prueba1_salidaesperada.txt`, `prueba2_entrada.txt`, `prueba2_salidaesperada.txt`. Ambos integrantes contribuyen al TP
integrador. El primer commit (`8e83e45`) de Santino agrega la implementación inicial; los commits posteriores de Mateo (
`a174bf3` y `55910a4`) refactorizan/extienden la solución y agregan los archivos de prueba. No hay committers sin
mapear.

---

## Método aplicado

- Tests del grupo: **Ejecutados** y pasaron (exit 0).
- Tests de cátedra (verificación cruzada con `ruta_mina_prueba1..3` de `guia-de-ejercicios-2023-profesores`): *
  *Ejecutados** y pasaron (diff vacío en los 3 casos).
- Revisión estática del código: Sí.
- Evidencia breve:
    - Configuración y build con `cmake` en un directorio out-of-source temporal (configuración OK).
    - Build: `cmake --build <build-dir> --target test_tp_ruta_mina` (compila; un único warning no relacionado:
      `recursividad.c:149` sin `return` en función no-void de la práctica general).
    - Ejecución del test del grupo: `./test_tp_ruta_mina` desde un layout que reproduce el path relativo
      `../../../practicas/1-recursividad/...` que usa el test → `Test 1 pasado`, `Test 2 pasado`, exit 0.
    - Verificación cruzada: runner mínimo que `#include "tp_ruta_mina.c"` y llama a
      `resolver_ruta_mina(argv[1], argv[2])`; ejecutado contra las 3 entradas/salidas de cátedra. `diff`
      salida-vs-esperada → vacío en las 3 pruebas.

---

## Verificación cruzada con entradas de cátedra

Tres pruebas oficiales de la referencia de cátedra:

| Caso                | Tipo                      | Resultado                |
|---------------------|---------------------------|--------------------------|
| `ruta_mina_prueba1` | Camino válido con tesoros | ✅ Coincide línea a línea |
| `ruta_mina_prueba2` | Grilla 3x3 sin tesoros    | ✅ Coincide línea a línea |
| `ruta_mina_prueba3` | Sin camino (`SIN_CAMINO`) | ✅ Coincide línea a línea |

La salida del grupo coincide exactamente, incluyendo formato (`RESULTADO:`, `PUNTAJE:`, `PASOS:`, `MOVIMIENTOS:`,
`CAMINO:`), coordenadas en base 1 y separador `->`.

---

## Corrección de la práctica

### `cargar_mapa()` (mapea a `leer_mapa()`)

**Estado: ⚠️ ADVERTENCIA**

La función `leer_mapa` cumple el rol de cargar el mapa desde el archivo de entrada al struct `Mapa`:

- Abre el archivo, lee dimensiones (`filas`, `columnas`) con `sscanf` y reserva `celdas` en 2D con `malloc`.
- Recorre filas y columnas, copia el carácter a `celdas[i][j]` y registra las posiciones de `I` y `S` durante la
  lectura.
- Funciona correctamente para todos los inputs probados (los del grupo y los 3 de cátedra).

Problemas reales (no opcionales) que se observan respecto del enunciado:

- Validación de entrada inexistente: no valida dimensiones (`filas`/`columnas` no positivas o desproporcionadas con el
  contenido), no valida símbolos (no rechaza caracteres fuera de `# . 0-9 I S`), no detecta falta o duplicación de `I` o
  `S`. La consigna pide manejar entradas inválidas.
- Manejo de error si `fopen` falla: imprime a stdout y hace `return` sin avisar al caller, que entonces invocará
  `resolver_ruta`/`escribir_resultado` sobre un `Mapa` no inicializado (UB potencial: `mapa->filas`, `mapa->columnas`,
  `mapa->celdas` quedan con valores indeterminados). Aun así no escribe nada en el archivo de salida, queda mudo frente
  a una entrada inaccesible.
- `printf` de depuración remanentes ("Archivo abierto con éxito", línea de guiones) que el propio comentario marca
  como "BORRAR".
- Buffer fijo `linea[100]`: aceptable para los casos esperados, pero queda como riesgo si se prueba con anchos cercanos
  al límite.

Sugerencia: separar el parsing de la validación; devolver un código de estado para que el caller pueda escribir el
archivo de salida o liberar recursos.

### `buscar_ruta()` (mapea a `resolver_ruta()` + `resolver_ruta_rec()`)

**Estado: ✅ CORRECTO**

`resolver_ruta` orquesta la búsqueda y `resolver_ruta_rec` implementa la exploración recursiva:

- Recursión real con backtracking: marca `visitados[fila][col] = true` antes de explorar y la desmarca al volver.
- Caso base: si la posición actual coincide con la salida, evalúa si la solución actual mejora a la mejor encontrada (
  criterio jerárquico: puntaje > pasos < lexicográfico) y la actualiza con copia profunda del camino y de la cadena de
  movimientos.
- Orden de exploración respeta el lexicográfico exigido: `A` (Arriba), `B` (Abajo), `D` (Derecha), `I` (Izquierda).
- Restricciones aplicadas correctamente: límites de la grilla, celdas `#` bloqueadas, no revisita celdas (vía
  `visitados`).
- Suma de puntajes: convierte celdas con dígito (`'0'..'9'`) a entero. Las celdas `I` y `S` no suman (no son dígitos),
  consistente con el enunciado y con las salidas esperadas verificadas.
- Comparación de mejor solución vía `strcmp(movimientos_actuales, mejor.movimientos)`; al ser cadenas de igual
  longitud (mismo `pasos`) cuando se evalúa el criterio lexicográfico, equivale a la comparación pedida.

Sugerencia (no afecta correctitud): el `malloc` de `nuevos_movimientos` por cada paso de la exploración multiplica las
reservas; alcanzaría con un único buffer crecido in-place y restaurado al volver. Es una mejora de eficiencia, no de
comportamiento.

Sugerencia: la función `resolver_ruta_rec` tiene 9 parámetros; varios podrían vivir en una struct de "estado de
exploración" para reducir ruido en la firma.

### `resolver_ruta_mina()`

**Estado: ✅ CORRECTO**

`resolver_ruta_mina(const char *entrada, const char *salida)` cumple el rol de orquestador del programa:

- Llama a `leer_mapa`, `resolver_ruta`, `escribir_resultado` y `liberar_memoria` en el orden esperado.
- El formato de salida producido (`escribir_resultado`) respeta exactamente lo pedido: encabezados `RESULTADO:`,
  `PUNTAJE:`, `PASOS:`, `MOVIMIENTOS:`, `CAMINO:`, coordenadas en base 1, separador ` -> `, y `RESULTADO: SIN_CAMINO` en
  caso negativo.
- Verificado contra 5 casos (2 propios + 3 de cátedra): salida idéntica byte a byte (excepto saltos finales triviales) a
  los esperados.

Sugerencia: si `escribir_resultado` no puede abrir el archivo de salida hace `exit(1)` directamente. Sería preferible
propagar el error y permitir liberar memoria.

Sugerencia: `liberar_memoria` no libera el array `solucion->camino` ni `solucion->movimientos` correctamente cuando no
se encontró solución (depende de los `malloc(1)` iniciales — sí los libera, OK), pero no libera `mapa->celdas[i]`
después de `mapa->filas`. Revisado el flujo: sí lo hace en el loop. La función está correcta. (Se mantiene por
completitud documental).

---

## Revisión de tests

| Test                  | Estado        | Observaciones                                                                                                                              |
|-----------------------|---------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| `test_tp_ruta_mina.c` | ⚠️ Incompleto | Compila y pasa los 2 casos del grupo. Pero solo cubre 2 escenarios (camino válido con tesoros y sin camino) de los 4 que pide la consigna. |

Los archivos de prueba (`prueba1_entrada.txt`, `prueba1_salidaesperada.txt`, `prueba2_entrada.txt`,
`prueba2_salidaesperada.txt`) están presentes en el repo y se cargan correctamente vía la ruta relativa que usa el
test (`../../../practicas/1-recursividad/...`), asumiendo que el binario corre desde un layout
`cmake-build-debug/practicas/1-recursividad/`. La función `file_eq` compara archivo por archivo línea por línea,
equivalente a la verificación pedida.

### Tests con casos de borde faltantes

Faltan los dos casos pedidos por la consigna:

- Empate por puntaje que se resuelva por menor cantidad de pasos.
- Empate por puntaje y pasos que se resuelva por menor secuencia lexicográfica.

Aunque la implementación los maneja correctamente (verificado contra cátedra), no hay test que los ejercite
explícitamente.

---

## Hallazgos / observaciones

- **`recursividad.h` modificado**: hay 3 cambios en firmas de funciones (`chinos`, `ondaDigital`, `explosion`), pero son
  **solo cambios de formato** (estilo `*` pegado al tipo vs al identificador). `git diff -w` lo confirma. Clasificación:
  `SOLO_FORMATO`. No se considera modificación crítica del archivo de cátedra.
- **CMakeLists OK**: `practicas/1-recursividad/CMakeLists.txt` con `file(GLOB tests/test_*.c)` ya levanta el target
  `test_tp_ruta_mina` automáticamente; no hace falta tocar nada. El test resuelve `tp_ruta_mina.c` vía
  `#include "../tp_ruta_mina.c"` (no por linkado), que funciona aunque no es la práctica más limpia.
- **Path relativo en el test**: `../../../practicas/1-recursividad/...` solo resuelve correctamente si el binario corre
  desde `<repo>/cmake-build-debug/practicas/1-recursividad/`. Cualquier otra ubicación de build hace que `fopen` falle
  silenciosamente y la salida quede como "SIN_CAMINO" (verificado durante la corrección al cambiar de directorio). Es
  una fragilidad del test, no de la solución.
- **README**: declara los integrantes (`Mateo Miguez, Santino Morrone`) — OK. El alcance del TP integrador refleja
  contribución de ambos.
- **Sin memory leaks observables en el flujo principal**: las reservas de `mov_inicial`, `camino_buffer`, `visitados`,
  `mapa->celdas`, `solucion->movimientos`, `solucion->camino` se liberan correctamente. Sí hay reservas+liberaciones por
  iteración de `nuevos_movimientos` en la recursión, costoso pero correcto.

---

## Resumen

| Categoría                                                     | Estado                                                                                   |
|---------------------------------------------------------------|------------------------------------------------------------------------------------------|
| Archivos `.h` sin modificar (contenido)                       | ✅ (solo cambios de formato; sin cambio semántico)                                        |
| `cargar_mapa` (mapea a `leer_mapa`)                           | ⚠️ Advertencia (carga funciona; sin validación de entrada y con manejo débil de errores) |
| `buscar_ruta` (mapea a `resolver_ruta` + `resolver_ruta_rec`) | ✅ Correcto                                                                               |
| `resolver_ruta_mina`                                          | ✅ Correcto                                                                               |
| Tests del grupo                                               | ✅ Compilan y pasan (2 de 4 casos de la consigna)                                         |
| Tests con buena cobertura                                     | ⚠️ 2 de 4 casos pedidos por la consigna (faltan los dos casos de empate)                 |
| Verificación cruzada con cátedra                              | ✅ Coincide línea a línea en las 3 pruebas oficiales                                      |

Estado global: la entrega **es funcional y resuelve correctamente el problema** según los criterios de la cátedra,
incluyendo desempates por puntaje, pasos y orden lexicográfico de movimientos. Los puntos a mejorar son no triviales
pero no comprometen la corrección: validación de entrada en `leer_mapa` y cobertura de los dos casos de empate en los
tests.
