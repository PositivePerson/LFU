#include <bits/stdc++.h>
#include <iterator>

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
        return frequencies[0].first;
    } else {
        // find which page (from storage) came first
        for(int k=0 ; k<pages.size() ; k++){
//            cout << "(inside findLeast:) Error: Moved out of for loop. Page " << pages[k] << " \n";
            for(int i=0 ; i<storage.size() ; i++) {
                if( storageFreq[i] == min && removedPages[k].first == storage[i] && removedPages[k].second == false) {
                    cout << "(inside findLeast:) Im returning page " << pages[k] << '\n';
                    return pages[k];
                }
            }
        }
    }
}

void sortFrequencies(vector<pair<int, int>> &frequencies) {
    std::sort( frequencies.begin(), frequencies.end(),
               [](const std::pair<int, int>& f, const std::pair<int, int>& s) {
                   return f.first < s.first;
               });
}

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

int main()
{
    int fault = 0;
    int pageHit = 0;

    int capacity = 3;
    vector<int> storage(capacity, -1);

    vector<int> pages = { 1, 2, 3, 4, 2, 1, 5 };
    vector<pair<int, bool>> removedPages = {
            {1, false},
            {2, false},
            {3, false},
            {4, false},
            {2, false},
            {1, false},
            {5, false}
    };

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

        std::sort( frequencies.begin(), frequencies.end(),
                   [](const std::pair<int, int>& f, const std::pair<int, int>& s) {
                       return f.second < s.second;
                   });

        // Fill Capacity blanks
        bool seated = false;
        for(int i=0 ; i<capacity ; i++) {
            if(storage[i] == -1) {
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

            int temp;
            if(alreadyInStorage) {
                std::vector<pair<int, int>>::iterator frequencyToIncrease;
                frequencyToIncrease = find_if(frequencies.begin(), frequencies.end(), [page](pair<int, int> i) {
                    return i.first == page;
                });
                cout << "Already in storage so frequencyToIncrease.first == " << frequencyToIncrease->first << '\n';
//                It is done before
//                frequencyToIncrease->second++;
                cout << "INCREASED frequencyToIncrease: { first: " << frequencyToIncrease->first << "  |  second: "
                     << frequencyToIncrease->second << " } " << '\n';
            } else {
                std::vector<pair<int, int>>::iterator frequencyToDecrease;
                temp = findLeast(frequencies,pages, storage, removedPages);
                cout << "For page -" << page << "- findLeast returned page " << temp << " from storage\n";

                frequencyToDecrease = find_if(frequencies.begin(), frequencies.end(), [temp](pair<int, int> i) {
                    return i.first == temp;
                });
                cout << "NOT in storage so frequencyToDecrease.first == " << frequencyToDecrease->first << '\n';
                frequencyToDecrease->second--;
                cout << "DECREASED frequencyToDecrease: { first: " << frequencyToDecrease->first << "  |  second: "
                << frequencyToDecrease->second << " } " << '\n';

                for(int j=0 ; j<removedPages.size() ; j++) {
                    if(removedPages[j].first == temp && removedPages[j].second == false) {
                        cout << "j = " << j << " | pages[j] = " << pages[j] << " | temp = " << temp << '\n';
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


        if(!existFrequency) fault++;
        else pageHit++;
    }

    cout << '\n';
    displayStorage(storage);
    cout << '\n';

    sortFrequencies(frequencies);
    displayFrequencies(frequencies);

    cout << '\n';
    cout << "Page Faults = " << fault << '\n';
    cout << "Page Hits = " << pageHit << '\n';
    return 0;
}
