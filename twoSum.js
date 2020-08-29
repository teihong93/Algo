var twoSum = function(nums, target) {
    let numMap = {};
    for(elem in nums) {
        const current = nums[elem]
        const subNum = target - current;
        if( numMap[subNum] ) {
            return [elem, numMap[subNum] ]   
        } else {
            numMap[ current ] = elem;
        }
    }
};
