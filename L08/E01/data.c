#include "data.h"

int dataCmp(data x1, data x2) {
    if (x1.aaaa > x2.aaaa)
        return 1;
    if (x1.aaaa == x2.aaaa && x1.mm > x2.mm)
        return 1;
    if (x1.aaaa == x2.aaaa && x1.mm == x2.mm && x1.gg > x2.gg)
        return 1;
    if (x1.aaaa == x2.aaaa && x1.mm == x2.mm && x1.gg == x2.gg)
        return 0;
    return -1;

}

data setData(data *x, int aa, int m, int g) {
    x->aaaa = aa;
    x->mm = m;
    x->gg = g;
    return *x;
}