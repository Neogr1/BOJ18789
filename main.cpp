#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "table.h"
#include "util.h"
#include "sa/sa.h"
#include "policy/randomNChange.h"
#include "policy/pickBest.h"

#define BASE_EPOCH 1000000

// 숫자 한번 변경할 때 최대 2048번의 count의 변화 생김 (updateTable)
// 숫자 변경 후 updateScore 사용해야 점수 업데이트 함

int maxNormalScore;
int maxCountScore;
string maxNormalScoreTable;
string maxCountScoreTable;
int maxNormalScoreAt;
int maxCountScoreAt;


string readInput(string path) {
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

// 이 부분을 수정해서 step마다의 정책을 결정
void doPolicy(Table& table, SimulatedAnnealing& sa, int step) {
    if (step % 50 == 0) { // 업데이트가 일정 스텝 없으면 수행하는 것이 좋을 듯
        // forcedRandomSwap(table);
        forcedRandomChange(table);
        forcedRandomChange(table);
    }
    else {
        // randomChange(table, sa);
        pickBestChange(table, sa);
    }
}

void startEmulator(Table& table, SimulatedAnnealing& sa, int epoch) {
    int nScore;
    int cScore;
    bool bMaxScoreUpdated;

    for (int step = 1; step <= epoch; step++) {
        doPolicy(table, sa ,step);

        nScore = table.getNormalScore();
        cScore = table.getCountScore();

        bMaxScoreUpdated = false;
        if (nScore > maxNormalScore) {
            maxNormalScore = nScore;
            maxNormalScoreTable = table.getTableAsString();
            maxNormalScoreAt = step;
            bMaxScoreUpdated = true;
        }
        if (cScore > maxCountScore) {
            maxCountScore = cScore;
            maxCountScoreTable = table.getTableAsString();
            maxCountScoreAt = step;
            bMaxScoreUpdated = true;
        }

        if (bMaxScoreUpdated) {
            cout << "-----[New Max Score]-----\n";
            cout << "Normal score: " << nScore << '\n';
            cout << "Count score: " << cScore << '\n';
            cout << table.getTableAsString();
        } else if (step % 100 == 0) {
            cout << "-----[STEP " << step << "]-----\n";
            cout << "Normal score: " << nScore << '\n';
            cout << "Count score: " << cScore << '\n';
            cout << table.getTableAsString();
        }

        if (maxCountScore == 9000)
            break;
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));

    string path = "input/8898.in";
    int epoch = BASE_EPOCH; 
    if (argc >= 2) path = string(argv[1]);
    if (argc >= 3) epoch = atoi(argv[2]);

    string input = readInput(path);
    

    Table table = Table(input);
    // maxNormalScore = table.getNormalScore();
    // maxCountScore = table.getCountScore();

    cout << "Initial normal score: " << maxNormalScore << '\n';
    cout << "Initial count score: " << maxCountScore << '\n';
    table.getTableAsString();

    SimulatedAnnealing sa = SimulatedAnnealing();

    startEmulator(table, sa, epoch);

    cout << "\n\nTotal accecption count: " << sa.accCount << '\n';
    cout << "Best Normal Score: " << maxNormalScore << " at " << maxNormalScoreAt << '\n';
    cout << maxNormalScoreTable;
    cout << "Best Count Score: " << maxCountScore <<  " at " << maxCountScoreAt << '\n';
    cout << maxCountScoreTable;

    return 0;
}