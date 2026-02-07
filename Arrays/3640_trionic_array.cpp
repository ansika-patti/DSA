#include <climits>
#include <vector>
using namespace std;

class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n=nums.size();
        long long ans=LLONG_MIN;
        
        for(int i=1; i<n-2; ){
            // Step 1: increasing segment
            if(nums[i]<=nums[i-1]){
                i++;
                continue;
            }
            int l = i-1;
            while(i<n && nums[i]>nums[i-1]) i++;
            int p = i-1;

            // Step 2: decreasing segment
            if(i==n || nums[i]>=nums[i-1]){
                i++;
                continue;
            } 
            while(i<n && nums[i]<nums[i-1]) i++;
            int q = i-1;

            // Step 3: increasing segment again
            if(i==n || nums[i]<=nums[i-1]){
                i++;
                continue;
            } 
            while(i<n && nums[i]>nums[i-1]) i++;
            int r = i-1;

            // Best left boundary
            long long bestLeftSum = LLONG_MIN, curr = 0;
            int bestL = l;
            for (int i = p - 1; i >= l; i--) {
                curr += nums[i];
                if (curr > bestLeftSum) {
                    bestLeftSum = curr;
                    bestL = i;
                }
            }

            // Best right boundary
            long long bestRightSum = LLONG_MIN;
            curr = 0;
            int bestR = r;
            for (int i = q + 1; i <= r; i++) {
                curr += nums[i];
                if (curr > bestRightSum) {
                    bestRightSum = curr;
                    bestR = i;
                }
            }

            // Compute sum using prefix sums
            long long sum=0;
            for(int j=bestL; j<=bestR; j++){
               sum+=nums[j];
            }
            if(sum>ans) ans=sum;

            // Move forward
            i = q;
        }

        return ans;
    }
};