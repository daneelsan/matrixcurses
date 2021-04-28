
- [matrixcurses](#matrixcurses)
  - [Run](#run)
  - [Build](#build)
  - [Modify](#modify)
  - [ToDo](#todo)


# matrixcurses
A Matrix-style dripping text (source: https://youtu.be/K8dCh3ZMLN8)

## Run

```console
$ ./matrix
```
![./matrix output](/example.png)

## Build

```console
$ make
clang -g -Wall -c main.c -o main.o
clang -g -Wall -c matrix.c -o matrix.o
clang -g -Wall -c ui.c -o ui.o
clang -g -Wall -o matrix main.o matrix.o ui.o -lncurses
```

## Modify

To change the number of iterations, modify `ITERATIONS` in `main.c`.

To change the refresh delay, modify `REFRESH_DELAY` in `main.c`.

## ToDo

- [ ] Accept `ITERATIONS` and `REFRESH_DELAY` as arguments.
