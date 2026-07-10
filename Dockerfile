# ---------- Etapa de compilación ----------
FROM ubuntu:22.04 AS build

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    g++ \
    curl \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/*

# Descargo cpp-httplib (libreria de un solo header, fijada a una version especifica)
# para que la interfaz web tenga con que compilar sin que nadie descargue nada a mano
RUN curl -sL -o /usr/local/include/httplib.h \
    https://raw.githubusercontent.com/yhirose/cpp-httplib/v0.49.0/httplib.h

WORKDIR /app
COPY . .

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --parallel

# ---------- Etapa final (imagen liviana de ejecución) ----------
FROM ubuntu:22.04

RUN apt-get update && apt-get install -y --no-install-recommends \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=build /app/build/allocation_simulator/allocation_sim ./bin/allocation_sim
COPY --from=build /app/build/translation_simulator/translation_sim ./bin/translation_sim
COPY data/ ./data/
COPY --from=build /app/allocation_simulator/tests ./allocation_simulator/tests
COPY --from=build /app/translation_simulator/tests ./translation_simulator/tests
COPY --from=build /app/allocation_simulator/web ./allocation_simulator/web
COPY --from=build /app/translation_simulator/web ./translation_simulator/web

ENV PATH="/app/bin:${PATH}"

# 8080 para allocation_sim, 8081 para translation_sim (los usamos cuando conectemos
# el servidor web dentro de cada main.cpp, en el siguiente paso)
EXPOSE 8080 8081

CMD ["/bin/bash"]