Una reserva de memoria consiste en la zona de memoria reservada y un header con la información de esta zona de memoria

-----------------------------------------------------------
|  HEADER (Metadatos)   |  DATOS UTILIZABLES (100 bytes)
-----------------------------------------------------------
^                       ^
|                       |
PunteroHeader           PunteroUsuario
(Punt_User - sizeof)    (Punt_Header + sizeof)

Cuando hacemos malloc, el puntero apunta a la zona de datos utilizables (el inicio de la zona reservada + el tamaño del header)

Cuando hacemos free, le damos la zona de memoria de los datos. Es decir, debemos retroceder el tamaño del header para ir a la zona de los metadatos, y ahí tendremos la información del bloque de memoria.

Explicación de la estructura:

- t_zone (Contenedor mmap)
  ┌────────────────────────────────────────────────────────┐
  │ type       = TINY                                      │
  │ total_size = 16384 (bytes totales del mmap)            │
  │ next       ───► Apunta a la siguiente Zona (o NULL)    │
  │ blocks     ───► Apunta al primer t_block de abajo      │
  └──────────────────┬─────────────────────────────────────┘
                     │
                     ▼
  ┌──────────────────┴─────────────────────────────────────┐
  │ [t_block 1] ──next──► [t_block 2] ──next──► [t_block 3]│
  │  (128 B)               (64 B)                (100 B)   │
  └────────────────────────────────────────────────────────┘
