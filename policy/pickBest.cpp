#include "pickBest.h"

void pickBestChange(Table& table, SimulatedAnnealing& sa) {
    int originScore = calculateMergedScore(table.getNormalScore(), table.getCountScore());
    int score, maxScore = 0;
    int maxR, maxC, maxN;
    int originN;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 14; c++) {
            originN = table.getDigit(r, c);

            for (int n = 0; n < 10; n++) {
                if (n == originN)
                    continue;
                    
                table.updateTable(r, c, n);
                table.updateScore();
                score = calculateMergedScore(table.getNormalScore(), table.getCountScore());

                if (score > maxScore) {
                    maxScore = score;
                    maxR = r; maxC = c; maxN = n;
                }
            }

            table.updateTable(r, c, originN);
        }
    }

    bool accepted = sa.acceptChange(originScore, maxScore);
    if (accepted) {
        table.updateTable(maxR, maxC, maxN);
        table.updateScore();
    }
    
    return;
}