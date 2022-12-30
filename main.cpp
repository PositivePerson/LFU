#include <bits/stdc++.h>

using namespace std;

int findLeast(vector<pair<int, int>> &frequencies, vector<int> pages, const int capacity) {
    int countLeasts = 1;
    for(int i=0 ; i<capacity ; i++) {
        // frequencies[0].second <- least value because sorted ascending
        if(frequencies[i].second == frequencies[0].second) {
            countLeasts++;
        }
    }
    if(countLeasts == 1) {
        return frequencies[0].first;
    } else {
        // find which page came the first
        for(auto page:pages){
            for(int j=0 ; j<countLeasts ; j++) {
                if(page == frequencies[j].first) {
                    return page;
                }
            }
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
            {1,0},{2,0},{3,4}
    };

    for(int i=0 ; i<pages.size() ; i++){
        if(frequencies[i].first == pages[i]) continue;
    }

    for(auto page: pages){
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
            // Equal frequencies so Compare order of arrival
            int temp = findLeast(frequencies,pages, capacity);
            cout << "For page: " << page << " findLeast returned: " << temp << '\n';

            // Frequencies that .second === 'temp' --
            // temp = storage.at(
            //find element with value returned by 'findLeast()'
            std::vector<pair<int, int>>::iterator frequencyToDecrease = find_if(frequencies.begin(), frequencies.end(), [temp](pair<int, int> i) {
                return i.first == temp;
            });
            frequencyToDecrease->second--;
            cout << "frequencyToDecrease.first: " << frequencyToDecrease->first << "   |   ";
            cout << "frequencyToDecrease.second: " << frequencyToDecrease->second << '\n';

            cout << "storage.at(find(storage.begin(), storage.end(), temp) != storage.end()): "
            << storage.at(find(storage.begin(), storage.end(), temp) != storage.end()) << '\n';

            storage.at(
                    //find element with value returned by 'findLeast()'
                    std::find(storage.begin(), storage.end(), temp) != storage.end()
            ) = page;



//                     std::vector<pair<int, int>>::iterator it = find_if(frequencies.begin(), frequencies.end(), IsEqual);
        }


        // Count/create Frequency
        bool existFrequency = false;
        for(int i=0 ; i<frequencies.size() ; i++){
            if(frequencies[i].first == page) {
                existFrequency = true;
                frequencies[i].second++;
                break;
            }
        }
        if(!existFrequency) frequencies.push_back(make_pair(page, 0));

        if(!existFrequency) fault++;
        else pageHit++;
    }

    for(auto frequency: frequencies){
        cout << "Frequency " << frequency.first << " " << frequency.second << '\n';
    }

    cout << '\n';
    cout << "Page Faults = " << fault << '\n';
    cout << "Page Hits = " << pageHit << '\n';
    return 0;
}
