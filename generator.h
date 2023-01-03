//
// Created by Bartek on 03/01/2023.
//

#ifndef LFU_GENERATOR_H
#define LFU_GENERATOR_H

#include "iostream"
#include <bits/stdc++.h>

using namespace std;

vector<int> generatePages(int amount) {
    srand((unsigned) time(NULL));

    vector <int> pages;
    for (int i = 0; i < amount; i++) {
        int page = 1 + (rand() % 9); // 1-10

        pages.push_back(page);
    }

    cout << "Generated 'Pages'\n";
    return pages;
}

vector<pair<int, bool>> generateRemoved(vector<int> pages) {
    vector<pair<int, bool>> removedPages;
    for (int i = 0; i < pages.size(); i++) {
        removedPages.push_back(make_pair(pages[i], false));
    }

    cout << "Generated 'RemovedPages'\n";
    return removedPages;
}

#endif //LFU_GENERATOR_H
