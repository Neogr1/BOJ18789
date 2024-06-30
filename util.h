#ifndef UTIL_H
#define UTIL_H

#include "table.h"

void forcedRandomSwap(Table& table);
void forcedRandomChange(Table& table);

// 점수 계산 방식의 다양한 고려 필요
int calculateMergedScore(int nScore, int cScore);

#endif