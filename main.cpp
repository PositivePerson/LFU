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
int findLeast(vector<pair<int, int>> &frequencies, vector<int> pages, const int capacity, vector<int> storage) {
    int countLeasts = 1;
//    for(int i=1 ; i<frequencies.size() ; i++) {
//        // frequencies[0].second <- least value because sorted ascending
//        if(frequencies[i].second == frequencies[0].second) {
//            cout << "(inside findLeast:) frequencies[i].second == frequencies[0].second  ("
//            << frequencies[0].second << ")\n";
//            countLeasts++;
//        }
//    }

    int storageFreq[storage.size()];

    for(int j=0 ; j<storage.size() ; j++) {
        for (int i = 0; i < frequencies.size(); i++) {
            if (frequencies[i].first == storage[j]) {
                storageFreq[j] = frequencies[i].second;
                cout << "Filling in storageFreq [" << j << "] with value " << frequencies[i].second << '\n';
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
        for(auto page:pages){
            for(int i=0 ; i<storage.size() ; i++) {
                if(page == storage[i] && storageFreq[i] == min) {
                    cout << "(inside findLeast:) Im returning page " << page << '\n';
                    return page;
                }
            }
//            for(int j=0 ; j<countLeasts ; j++) {
//                if(page == frequencies[j].first) {
//                    cout << "(inside findLeast:) Im returning page " << page << '\n';
//                    return page;
//                }
//            }
        }
    }
}

bool IsEqual (pair<int, int> i) {
    return i.second == 1;
}

int main()
{
    int fault = 0;
    int pageHit = 0;

    int capacity = 3;
    vector<int> storage(capacity, -1);

    vector<int> pages = { 1, 2, 3, 4, 2, 1, 5 };
    int n = pages.size();

    vector <pair<int,int>> frequencies={
//            {1,0},{2,0},{3,4}
//            {0, 0}
    };

//    for(int i=0 ; i<pages.size() ; i++){
//        if(frequencies[i].first == pages[i]) continue;
//    }

    for(auto page: pages){
        cout << "\nStorage is: ";
        for(int i=0; i<storage.size() ; i++) {
                cout << storage[i] << ' ';
        }
        cout << '\n';

        cout  << "\nPage " << page << '\n';

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
            cout << "Making pair for page " << page << '\n';
            frequencies.push_back(make_pair(page, 1));
            cout << "frequencies.end(): " << frequencies.back().first << " " << frequencies.back().second << '\n';
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
            // Ensure its not in storage
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
//          its done before      frequencyToIncrease->second++;
                cout << "INCREASED frequencyToIncrease: { first: " << frequencyToIncrease->first << "  |  second: "
                     << frequencyToIncrease->second << " } " << '\n';
            } else {
                std::vector<pair<int, int>>::iterator frequencyToDecrease;
                temp = findLeast(frequencies,pages, capacity, storage);
                cout << "For page -" << page << "- findLeast returned page " << temp << " from storage\n";

                frequencyToDecrease = find_if(frequencies.begin(), frequencies.end(), [temp](pair<int, int> i) {
                    return i.first == temp;
                });
                cout << "NOT in storage so frequencyToDecrease.first == " << frequencyToDecrease->first << '\n';
                frequencyToDecrease->second--;
                cout << "DECREASED frequencyToDecrease: { first: " << frequencyToDecrease->first << "  |  second: "
                << frequencyToDecrease->second << " } " << '\n';
            }


            for (int i = 0; i < storage.size(); ++i) {
                if(storage[i] == temp) {
                    cout << "Storage change: " << storage[i] << " to " << page << '\n';
                    storage[i] = page;
                }
            }
//            cout << "storage.at(find(storage.begin(), storage.end(), temp) != storage.end()): "
//            << storage.at(find(storage.begin(), storage.end(), temp) != storage.end()) << '\n';
//
//            storage.at(
//                    //find element with value returned by 'findLeast()'
//                    std::find(storage.begin(), storage.end(), temp) != storage.end()
//            ) = page;



//                     std::vector<pair<int, int>>::iterator it = find_if(frequencies.begin(), frequencies.end(), IsEqual);
        }


        if(!existFrequency) fault++;
        else pageHit++;
    }

    cout << "\nStorage is: ";
    for(int i=0; i<storage.size() ; i++) {
        cout << storage[i] << ' ';
    }
    cout << '\n';

    for(auto frequency: frequencies){
        cout << "Frequency " << frequency.first << " " << frequency.second << '\n';
    }

    cout << '\n';
    cout << "Page Faults = " << fault << '\n';
    cout << "Page Hits = " << pageHit << '\n';
    return 0;
}
