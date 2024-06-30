#include "util.h"

void forcedRandomSwap(Table& table) {
    int r1 = rand() % 8;
    int c1 = rand() % 14;
    int r2 = rand() % 8;
    int c2 = rand() % 14;
    int temp = table.getDigit(r1, c1);

    table.updateTable(r1, c1, table.getDigit(r2, c2));
    table.updateTable(r2, c2, temp);
}

void forcedRandomChange(Table& table) {
    int r = rand() % 8;
    int c = rand() % 14;
    int n = rand() % 10;

    table.updateTable(r, c, n);
}

int calculateMergedScore(int nScore, int cScore) {
    return cScore;
    // return cScore * cScore;
    // return nScore * nScore;
    // return nScore * nScore * cScore;
    // return (nScore + cScore) * (nScore + cScore);
    // return nScore * nScore + cScore * cScore;
}