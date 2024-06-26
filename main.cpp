#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class Table {

private:
    int digits[8][14];
    int nScore;
    int cScore;

    int numberCounts[10000]; // 각 수의 만들 수 있는 개수
    vector<int> madeNumbers; // 만들어진 수들. 각 수의 인덱스는 dfs로 찾은 순서에 해당
    vector<int> usedIndices[8][14][4]; // 그 칸의 수가 [3,2,1,0]번째 자리로 사용되어 만들어진 수의 인덱스들(dfs로 찾은 순서)\

    void fillTableRandomly() {

    }

    void dfs(int r, int c, int num, int depth, int route[4][2]) {
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

    void initScore() {
        int route[4][2];

        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 14; c++)
                dfs(r, c, 0, 0, route);
        
        updateScore();
    }

    // 속도 증가 위해 함수 없앨 수도 있음
    int base[4] = {1000, 100, 10, 1};
    int getNewNumber(int num, int depth, int newDigit) {
        return num + (newDigit - num / base[depth] % 10) * base[depth];
    }


public:

    Table(string input) {
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

    void updateTable(int r, int c, int newDigit) {
        int newNumber;

        for (int d = 3; d >= 0; d--) {
            for (auto idx: usedIndices[r][c][d]) {
                numberCounts[madeNumbers[idx]]--;
                newNumber = getNewNumber(madeNumbers[idx], d, newDigit);

                numberCounts[newNumber]++;
                madeNumbers[idx] = newNumber;
            }
        }
    }

    void updateScore() {
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

    int getNormalScore() {
        return nScore;
    }

    int getCountScore() {
        return cScore;
    }
};

int main() {
    string path = "input/1.in";
    ifstream file(path);
    stringstream buffer;
    buffer << file.rdbuf();
    string input = buffer.str();
    file.close();

    Table table = Table(input);

    // 이제 변경 정책만 만들면 된다!
    // 숫자 한번 변경할 때 최대 2048번의 count의 변화 생김 (updateTable)
    // 숫자 변경 후 updateScore 사용해야 점수 업데이트 함

    return 0;
}