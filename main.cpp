#include <bits/stdc++.h>
#include <iterator>
#include "displayers.h"
#include "findLeast.h"
#include "generator.h"

using namespace std;

void sortFrequenciesByPage(vector<pair<int, int>> &frequencies) {
    std::sort( frequencies.begin(), frequencies.end(),
               [](const std::pair<int, int>& f, const std::pair<int, int>& s) {
                   return f.first < s.first;
               });
}

void sortFrequenciesByFreq(vector<pair<int, int>> &frequencies) {
    std::sort( frequencies.begin(), frequencies.end(),
               [](const std::pair<int, int>& f, const std::pair<int, int>& s) {
                   return f.second < s.second;
               });
}

int main()
{
    int fault = 0;
    int pageHit = 0;

    int capacity = 3;
    cout << "Storage capacity (number): ";
    cin >> capacity;
    vector<int> storage(capacity, -1);

//    vector<int> pages = { 1, 2, 3, 4, 2, 1, 5 };
//    vector<pair<int, bool>> removedPages = {
//            {1, false},
//            {2, false},
//            {3, false},
//            {4, false},
//            {2, false},
//            {1, false},
//            {5, false}
//    };
    int pagesAmount = 3;
    cout << "Pages amount (number): ";
    cin >> pagesAmount;
    cout << '\n';

    cout << "----- generators -----\n";
    vector<int> pages = generatePages(pagesAmount);
    vector<pair<int, bool>> removedPages = generateRemoved(pages);
    cout << "--- end of generators ---\n";


    vector <pair<int,int>> frequencies;

    for(auto page: pages){
        cout << '\n';
        displayStorage(storage);
        cout << '\n';

        cout  << "Page " << page << '\n';

        // Count/create Frequency
        bool existFrequency = false;
        for(int i=0 ; i<frequencies.size() ; i++){
            if(frequencies[i].first == page) {
                existFrequency = true;
                frequencies[i].second++;
                break;
            }
        }
        if(!existFrequency) {
            cout << "Making pair for page " << page << ": ";
            frequencies.push_back(make_pair(page, 1));
            cout << frequencies.back().first << ", " << frequencies.back().second << '\n';
        }

        sortFrequenciesByFreq(frequencies);

        // Fill Capacity blanks
        bool seated = false;
        for(int i=0 ; i<capacity ; i++) {
            if(storage[i] == -1) {
                fault++;

                storage.at(i) = page;
                seated = true;
                break;
            }
        }
        //Compare frequencies
        if(!seated) {
            bool alreadyInStorage = false;
            for(int i=0 ; i<storage.size() ; i++) {
                if(page == storage[i]) {
                    alreadyInStorage = true;
                }
            }

            int temp; // page from 'storage' to be changed
            if(alreadyInStorage) {
                pageHit++;

                std::vector<pair<int, int>>::iterator frequencyToIncrease;
                frequencyToIncrease = find_if(frequencies.begin(), frequencies.end(), [page](pair<int, int> i) {
                    return i.first == page;
                });
//                It is done before
//                frequencyToIncrease->second++;
                cout << "INCREASED frequencyToIncrease: { first: " << frequencyToIncrease->first << "  |  second: "
                     << frequencyToIncrease->second << " } " << '\n';
            } else {
                fault++;

                std::vector<pair<int, int>>::iterator frequencyToDecrease;
                temp = findLeast(frequencies,pages, storage, removedPages);
                cout << "For page -" << page << "- findLeast returned page " << temp << " from storage (to replace)\n";

                frequencyToDecrease = find_if(frequencies.begin(), frequencies.end(), [temp](pair<int, int> i) {
                    return i.first == temp;
                });
                frequencyToDecrease->second--;
                cout << "DECREASED frequencyToDecrease: { first: " << frequencyToDecrease->first << "  |  second: "
                << frequencyToDecrease->second << " } " << '\n';

                for(int j=0 ; j<removedPages.size() ; j++) {
                    if(removedPages[j].first == temp && removedPages[j].second == false) {
                        cout << "(removedPages[" << j << "].first is " << removedPages[j].first << ") Removing page\n";
                        removedPages[j].second = true;
                        break;
                    }
                }
            }

            for (int i = 0; i < storage.size(); ++i) {
                if(storage[i] == temp) {
                    cout << "Storage change: " << storage[i] << " to " << page << '\n';
                    storage[i] = page;
                }
            }
        }
    }

    cout << '\n';
    displayStorage(storage);
    cout << '\n';

    sortFrequenciesByPage(frequencies);
    displayFrequencies(frequencies);

    cout << '\n';
    cout << "Page Faults = " << fault << '\n';
    cout << "Page Hits = " << pageHit << '\n';
    return 0;
}
