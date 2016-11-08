Finding median from stream of number:
This projects calculates median every time when a new number comes in. It calculates the median in efficient manner.
It does this by keeping track of median each time in the sorted map and then move left and right 
depending if the new number is to the left or to the right of current median value.

I tried to this is somewhat more practical way. I have created stores. Each stores keep values sorted. Sharding of the number is done 
based on the new number that comes and accordingly each new number might go to different shard.
The Store and Store manager logic abstract the complexity of storing and sharding from the Median finding code and gives user 
a feel as if all the values are comming from some data-structure in sorted manner.
My itention here is to simulate the real life scenario of finding median in Big-Data where you might need to shard the number to different 
stores and at the same time calculate the median efficiently.
