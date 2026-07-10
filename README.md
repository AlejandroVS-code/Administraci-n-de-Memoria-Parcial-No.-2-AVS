# Parcial No. 2 - Sistemas Operativos
## Simuladores de Gestion de Memoria

**Autor:** Alejandro Valencia Sandoval
**Codigo:** 2515411
**Universidad del Valle**

Este proyecto contiene dos simuladores independientes:

- **Implementacion 1 (`allocation_simulator`)**: simulador de asignacion de memoria con las estrategias First Fit, Best Fit y Worst Fit.
- **Implementacion 2 (`translation_simulator`)**: simulador de traduccion de direcciones virtuales a fisicas, con Paginacion y Segmentacion.

Ambos simuladores ofrecen dos formas de uso: un menu de consola (CLI) y una interfaz web (GUI), disponibles simultaneamente durante la ejecucion.

---

## Requisitos

- Tener [Docker](https://www.docker.com/) instalado y corriendo.
- Un navegador web (Chrome, Firefox, Edge, etc.) para usar la interfaz grafica.

---

## 1. Clonar el repositorio

```bash
git clone https://github.com/AlejandroVS-code/Administraci-n-de-Memoria-Parcial-No.-2-AVS.git
```

Una vez termine la descarga, entra a la carpeta del proyecto:

```bash
cd Administraci-n-de-Memoria-Parcial-No.-2-AVS
```

---

## 2. Construir la imagen de Docker

Desde la raiz del proyecto (donde esta el archivo `Dockerfile`), ejecuta:

```bash
docker build -t simulator .
```

Este paso compila ambos simuladores dentro del contenedor. Puede tardar unos minutos la primera vez.

---

## 3. Levantar el contenedor

```bash
docker run -it -p 8080:8080 -p 8081:8081 simulator
```

Esto abre una terminal interactiva **dentro** del contenedor. Los puertos 8080 y 8081 quedan mapeados hacia tu maquina, para poder usar la interfaz web desde el navegador.

---

## 4. Ejecutar un simulador

Ya dentro de la terminal del contenedor, para correr **Implementacion 1** (asignacion de memoria):

```bash
bin/allocation_sim
```

Para correr **Implementacion 2** (traduccion de direcciones):

```bash
bin/translation_sim
```

Puedes correr los dos al mismo tiempo si abres una segunda terminal y te conectas al mismo contenedor (`docker exec -it <nombre_del_contenedor> bash`), ya que cada uno usa un puerto distinto (8080 y 8081 respectivamente).

---

## 5. Usar el simulador: consola (CLI)

Al ejecutar cualquiera de los dos binarios, aparece un menu por consola con opciones numeradas. Se navega escribiendo el numero de la opcion deseada y presionando Enter.

Para **salir del programa**, selecciona la opcion correspondiente a "Salir" dentro del menu (es la ultima opcion numerada de la lista que se muestra en pantalla). Esto termina el programa completo, incluyendo el servidor web que corre en paralelo.

---

## 6. Usar el simulador: interfaz web (GUI)

Al arrancar cualquiera de los dos binarios, en la consola aparece un mensaje indicando que la interfaz web ya esta disponible, junto con la direccion a usar:

- **Implementacion 1**: abre en tu navegador `http://localhost:8080`
- **Implementacion 2**: abre en tu navegador `http://localhost:8081`

Desde ahi puedes crear/liberar procesos, cambiar de estrategia, cargar archivos de prueba y reiniciar el estado de la memoria, todo desde el navegador, sin necesidad de tocar la consola.

---

## ⚠️ Importante: no usar la consola y la web al mismo tiempo

Aunque tecnicamente ambas interfaces corren en paralelo sobre el mismo estado de memoria, **se recomienda usar una sola interfaz a la vez** (o solo consola, o solo web) durante cada prueba. Usar ambas simultaneamente para modificar el estado (crear procesos, cambiar estrategia, etc.) al mismo tiempo puede generar condiciones de carrera, ya que ambas comparten el mismo objeto de memoria sin mecanismos de sincronizacion explicitos.

Es seguro, por ejemplo, dejar la web abierta solo para *ver* el estado mientras usas la consola para actuar, pero no se recomienda actuar desde ambas al mismo tiempo.

---

## 7. Archivos de prueba

Los archivos de entrada para cargar (opcion "Cargar y ejecutar archivo" tanto en consola como en web) deben ubicarse en:

- `data/allocation/` para Implementacion 1 (`example1.txt`, `example2.txt`, `example3.txt`)
- `data/translation/` para Implementacion 2 (`example1.txt`, `example2.txt`, `example3.txt`)

Al cargarlos, solo se debe escribir el nombre del archivo (por ejemplo `example1.txt`), no la ruta completa.

**Nota para `example3.txt` de Implementacion 2**: antes de cargarlo, hay que cambiar la estrategia activa a Segmentacion con `maxSegmentSize = 100` desde el menu o la interfaz web. Los comandos de traduccion de ese archivo estan calculados asumiendo ese valor exacto.

Los resultados de cada ejecucion se guardan automaticamente en:

- `allocation_simulator/tests/` para Implementacion 1
- `translation_simulator/tests/` para Implementacion 2

---

## 8. Reiniciar el estado de la simulacion

Como el servidor web corre en un solo proceso de larga duracion, el estado (procesos creados, mapeos de pagina, segmentos, etc.) se mantiene entre distintas cargas de archivo. Si quieres volver a un estado limpio antes de probar algo nuevo:

- **Desde la web**: usa el boton "Reiniciar memoria" (Implementacion 1) o "Reiniciar traductor" (Implementacion 2).
- **Desde la consola**: cierra el simulador con la opcion de "Salir" y vuelve a ejecutar el binario (`bin/allocation_sim` o `bin/translation_sim`).

---

## 9. Salir del contenedor de Docker

Una vez termines de usar los simuladores, sal del contenedor con:

```bash
exit
```

Si quieres volver a usarlo despues sin reconstruir la imagen, puedes listar los contenedores detenidos con `docker ps -a` y reiniciar el mismo con `docker start -ai <nombre_o_id_del_contenedor>`.