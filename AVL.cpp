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
            g << (a.find(x) != nullptr) << "\n";
            break;
        case 4:
            f >> x;
            g << a.predecessor(x)->getKey() << "\n";
            break;
        case 5:
            f >> x;
            g << a.successor(x)->getKey() << "\n";
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