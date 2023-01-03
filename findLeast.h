//
// Created by Bartek on 03/01/2023.
//

#ifndef LFU_FINDLEAST_H
#define LFU_FINDLEAST_H

#include "iostream"
#include <bits/stdc++.h>

using namespace std;

int findArrayMinimum(int arr[]) {
    int lowestValue = arr[0];
    for (int i = 1; i < sizeof(arr)/sizeof(arr[0]); ++i)
    {
        if (arr[i] < lowestValue) lowestValue = arr[i];
    }
    return lowestValue;
}

// Find which from "storage" number to replace
int findLeast(vector<pair<int, int>> &frequencies, vector<int> pages, vector<int> &storage, vector<pair<int, bool>> removedPages) {
    cout << "--------- findLeast ---------\n";
    int countLeasts = 1;

    int storageFreq[storage.size()];
    for(int j=0 ; j<storage.size() ; j++) {
        for (int i = 0; i < frequencies.size(); i++) {
            if (frequencies[i].first == storage[j]) {
                storageFreq[j] = frequencies[i].second;
                cout << "Filling in storageFreq[" << j << "] with value " << frequencies[i].second << '\n';
            }
        }
    }
    int min = findArrayMinimum(storageFreq);
    cout << "Minimum freq in storage is: " << min << '\n';
    for(int i=1 ; i<storage.size(); i++) { // Through storageFreq[]
        if(storageFreq[i] == min) {
            cout << "(inside findLeast:) storageFreq[i] == storageFreq[i-1] == " << storageFreq[i] << ")\n";
            countLeasts++;
        }
//        else {
//            break; // To avoid error in case (frequencies looks like): 1, 1, 2, 2, 2
//        }
    }

    if(countLeasts == 1) {
        cout << "Returning countLeasts == 1\n";
        cout << "------ end of findLeast ------\n";
        return frequencies[0].first;
    } else {
        // find which page (from storage) came first
        for(int k=0 ; k<pages.size() ; k++){
//            cout << "(inside findLeast:) Error: Moved out of for loop. Page " << pages[k] << " \n";
            for(int i=0 ; i<storage.size() ; i++) {
                if( storageFreq[i] == min && removedPages[k].first == storage[i] && removedPages[k].second == false) {
                    cout << "(inside findLeast:) Im returning page " << pages[k] << '\n';
                    cout << "------ end of findLeast ------\n";
                    return pages[k];
                }
            }
        }
    }
}

#endif //LFU_FINDLEAST_H
