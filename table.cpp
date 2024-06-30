#include "table.h"

void Table::fillTableRandomly() {

}

void Table::dfs(int r, int c, int num, int depth, int route[4][2]) {
    num = num * 10 + digits[r][c];
    route[depth][0] = r;
    route[depth][1] = c;

    if (depth == 3) {
        numberCounts[num]++;
        madeNumbers.push_back(num);
        int idx = madeNumbers.size() - 1;
        for (; depth >= 0; depth--)
            usedIndices[route[depth][0]][route[depth][1]][depth].push_back(idx);

        return;
    }

    if (r > 0) dfs(r-1, c, num, depth+1, route);
    if (r < 7) dfs(r+1, c, num, depth+1, route);
    if (c > 0) dfs(r, c-1, num, depth+1, route);
    if (c < 13) dfs(r, c+1, num, depth+1, route);
    if (r > 0 && c > 0) dfs(r-1, c-1, num, depth+1, route);
    if (r > 0 && c < 13) dfs(r-1, c+1, num, depth+1, route);
    if (r < 7 && c > 0) dfs(r+1, c-1, num, depth+1, route);
    if (r < 7 && c < 13) dfs(r+1, c+1, num, depth+1, route);
}

void Table::initScore() {
    int route[4][2];

    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 14; c++)
            dfs(r, c, 0, 0, route);
    
    updateScore();
}

int Table::getNewNumber(int num, int depth, int newDigit) {
    return num + (newDigit - num / base[depth] % 10) * base[depth];
}

Table::Table(string input) {
    if (input.size() == 0) {
        fillTableRandomly();
        initScore();
        return;
    }

    int idx = 0;
    for (char c: input) {
        if (idx == 8*14) {
            cout << "INVALID INPUT\n";
            exit(0);    
        }

        if ('0' <= c && c <= '9') {
            digits[idx/14][idx%14] = c - '0';
            idx++;
        }
    }

    if (idx != 8*14) {
        cout << "INVALID INPUT\n";
        exit(0);
    }

    initScore();
}

void Table::updateTable(int r, int c, int newDigit) {
    int newNumber;

    for (int d = 3; d >= 0; d--) {
        for (auto idx: usedIndices[r][c][d]) {
            numberCounts[madeNumbers[idx]]--;
            newNumber = getNewNumber(madeNumbers[idx], d, newDigit);

            numberCounts[newNumber]++;
            madeNumbers[idx] = newNumber;
        }
    }
    
    digits[r][c] = newDigit;
}

void Table::updateScore() {
    // evaluate normal score
    nScore = 9999;
    for (int num = 1000; num < 10000; num++) {
        if (numberCounts[num] == 0) {
            nScore = num - 1;
            break;
        }
    }

    // evaluate count score
    cScore = 0;
    for (int num = 1000; num < 10000; num++)
        cScore += (numberCounts[num] > 0);
}

int Table::getDigit(int r, int c) {
    return digits[r][c];
}

int Table::getNormalScore() {
    return nScore;
}

int Table::getCountScore() {
    return cScore;
}

string Table::getTableAsString() {
    string tableString;
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 14; c++) {
            tableString += to_string(digits[r][c]);
        }
        tableString += '\n';
    }

    return tableString;
}