#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); i++){
            for (int x = i + 1; x < nums.size(); x++){
                if (nums[i] + nums[x] == target){
                    return {i, x};
                }
            }
        }
        throw;
    }
};

int main(){
    std::vector <int> a = {1 , 23 , 5 , 11 , 12};
    Solution  myObject;
    std::vector<int> x = myObject.twoSum(a, 9);
}