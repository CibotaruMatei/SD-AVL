#include <fstream>
#include "AVL.h"

int main()
{
    AVL a;
    int q;
    std::fstream f("abce.in", std::ios::in);
    std::fstream g("abce.out", std::ios::out);

    f >> q;

    for (int i = 0; i < q; i++) {
        int x;
        f >> x;
        switch (x) {
        case 1:
            f >> x;
            a.insert(x);
            break;
        case 2:
            f >> x;
            a.remove(x);
            break;
        case 3:
            f >> x;
            g << (a.find(x) == nullptr);
            break;
        case 4:
            f >> x;
            g << a.find(x)->predecessor();
            break;
        case 5:
            f >> x;
            g << a.find(x)->succesor();
            break;
        case 6:
            int y;
            f >> x >> y;
            a.print(g, x, y);
            break;
        }
    }

    f.close();
    g.close();
    return 0;
}