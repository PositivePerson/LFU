//
// Created by Bartek on 03/01/2023.
//

#ifndef LFU_DISPLAYERS_H
#define LFU_DISPLAYERS_H

#include "iostream"
#include <bits/stdc++.h>

using namespace std;

void displayStorage(vector<int> storage) {
    cout << "Storage is: ";
    for(int i=0; i<storage.size() ; i++) {
        cout << storage[i] << ' ';
    }
    cout << '\n';
}

void displayFrequencies(vector<pair<int, int>> &frequencies) {
    cout << "Page\tFrequency\n";
    for(auto frequency: frequencies){
        cout << frequency.first << '\t' << frequency.second << '\n';
    }
}

#endif //LFU_DISPLAYERS_H
