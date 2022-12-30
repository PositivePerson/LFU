// C++ program to illustrate
// page faults in LFU

#include <bits/stdc++.h>
#include<cstdlib>
using namespace std;

/* Counts no. of page faults */
int pageFaults(int n, int c, int pages[])
{
    // Initialise count to 0
    int count = 0;

    // To store elements in memory of size c
    vector<int> v;
    // To store frequency of pages
    unordered_map<int, int> mp;

    int i;
    for (i = 0; i <= n - 1; i++) {

        // Find if element is present in memory or not
        auto it = find(v.begin(), v.end(), pages[i]);

        // If element is not present
        if (it == v.end()) {

            // If memory is full
            if (v.size() == c) {

                // Decrease the frequency
                mp[v[0]]--;

                // Remove the first element as
                // It is least frequently used
                v.erase(v.begin());
            }

            // Add the element at the end of memory
            v.push_back(pages[i]);
            // Increase its frequency
            mp[pages[i]]++;

            // Increment the count
            count++;
        }
        else {

            // If element is present
            // Remove the element
            // And add it at the end
            // Increase its frequency
            mp[pages[i]]++;
            v.erase(it);
            v.push_back(pages[i]);
        }

        // Compare frequency with other pages
        // starting from the 2nd last page
        int k = v.size() - 2;

        // Sort the pages based on their frequency
        // And time at which they arrive
        // if frequency is same
        // then, the page arriving first must be placed first
        while (mp[v[k]] > mp[v[k + 1]] && k > -1) {
            swap(v[k + 1], v[k]);
            k--;
        }
    }

    // Return total page faults
    return count;
}

/* Driver program to test pageFaults function*/
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
        if(storage[0] == -1) cout << "storage[0] empty\n";

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
            for(int i=0 ; i<capacity ; i++) {
                int pageNumber = storage[i];

                std::sort( frequencies.begin(), frequencies.end(),
                [](const std::pair<int, int>& f, const std::pair<int, int>& s) {
                    return f.first < s.first;
                });
                cout << "frequencies[0]: " << frequencies[0].first
                << ": " << frequencies[0].second << '\n';
            }
        }

            // (if equal frequencies) Compare order of arrival

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

    for(auto strg: storage){
        cout << "strg: " << strg <<'\n';
    }
//    cout << "Page Faults = " << pageFaults(n, c, pages)
//         << endl;
//    cout << "Page Hits = " << n - pageFaults(n, c, pages);
    return 0;
}

// This code is contributed by rajsanghavi9.
