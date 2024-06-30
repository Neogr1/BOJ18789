#include "randomNChange.h"

bool isInVector(vector<pair<int,int>>& positions, int r, int c, int maxIndex) {
    for (int i = 0; i < maxIndex; i++)
        if (positions[i].first == r && positions[i].second == c)
            return true;

    return false;
}

// 일반적으로 작은 N에 대해 사용하므로 O(N^2)으로 작성함
void getRandomPositions(vector<pair<int,int>>& positions) {
    int r, c;
    for (size_t i = 0; i < positions.size(); i++) {
        do {
            r = rand() % 8;
            c = rand() % 14;
        } while (isInVector(positions, r, c, i));

        positions[i] = make_pair(r, c);
    }
}

void randomChange(Table& table, SimulatedAnnealing& sa) {
    int originScore = calculateMergedScore(table.getNormalScore(), table.getCountScore());
    vector<int> originNumber(N);

    vector<pair<int,int>> positions(N);
    getRandomPositions(positions);

    for (int i = 0; i < N; i++) {
        int r = positions[i].first;
        int c = positions[i].second;

        originNumber[i] = table.getDigit(r, c);
        table.updateTable(positions[i].first, positions[i].second, rand() % 10);
    }

    table.updateScore();
    int newScore = calculateMergedScore(table.getNormalScore(), table.getCountScore());

    bool accepted = sa.acceptChange(originScore, newScore);
    if (accepted) {
        return;
    } else {
        for (int i = 0; i < N; i++) {
            table.updateTable(positions[i].first, positions[i].second, originNumber[i]);
        }
        table.updateScore();
    }
}