//
// Created by wangrl on 19-4-14.
//

#include <vector>
#include <unordered_map>

using namespace std;



vector<int> twoSum(vector<int>& nums, int target) {
    // Key is the number and value is its index in the vector.
    unordered_map<int, int> hash;
    vector<int> result;
    for (int i = 0; i < nums.size(); i++) {
        int numberToFind = target - nums[i];

        // if numberToFind is found in map, return them.
        if (hash.find(numberToFind) != hash.end()) {
            result.push_back(hash[numberToFind]);
            result.push_back(i);
            return result;
        }

        // number was not dound. Put it in the map.
        hash[nums[i]] = i;
    }
    return result;
}

