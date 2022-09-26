#ifndef E01_DATA_H
#define E01_DATA_H

typedef struct{
    int gg;
    int mm;
    int aaaa;
}data;

int dataCmp(data x1, data x2);

data setData(data *x, int aa, int m, int g);
#endif
