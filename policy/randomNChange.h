#ifndef RANDOMNCHANGE_H
#define RANDOMNCHANGE_H

#include <cstdlib>
#include <vector>
#include "../table.h"
#include "../sa/sa.h"

#define N 1

using namespace std;


bool isInVector(vector<pair<int,int>>& positions, int r, int c, int maxIndex);
void getRandomPositions(vector<pair<int,int>>& positions); // 일반적으로 작은 N에 대해 사용하므로 O(N^2)으로 작성함
void randomChange(Table& table, SimulatedAnnealing& sa);

#endif // RANDOMNCHANGE_H