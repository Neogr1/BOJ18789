#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <vector>
using namespace std;

class Table {

private:
    int digits[8][14];
    int nScore;
    int cScore;

    int numberCounts[10000]; // 각 수의 만들 수 있는 개수
    vector<int> madeNumbers; // 만들어진 수들. 각 수의 인덱스는 dfs로 찾은 순서에 해당
    vector<int> usedIndices[8][14][4]; // 그 칸의 수가 [3,2,1,0]번째 자리로 사용되어 만들어진 수의 인덱스들(dfs로 찾은 순서)

    void fillTableRandomly();
    void dfs(int r, int c, int num, int depth, int route[4][2]);
    void initScore();

    // 속도 증가 위해 함수 없앨 수도 있음
    int base[4] = {1000, 100, 10, 1};
    int getNewNumber(int num, int depth, int newDigit);


public:

    Table(string input);

    void updateTable(int r, int c, int newDigit);
    void updateScore();

    int getDigit(int r, int c);
    int getNormalScore();
    int getCountScore();
    string getTableAsString();
};

#endif