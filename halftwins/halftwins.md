## Half-Twins Write-up

So, we have this executable half-twins. Executing it on its own without any parameter gives the output : <br>
`hmm... i'm not sure you know what the word "twins" mean :/`<br>
 `good luck next time`<br>
Decompiling it with ghidra gives us the following cpp code : <br>
![First SS](https://github.com/angad-k/crackmes/blob/master/halftwins/screenshots/Screenshot%20from%202020-03-25%2019-43-13.png) <br>
![First SS](https://github.com/angad-k/crackmes/blob/master/halftwins/screenshots/Screenshot%20from%202020-03-25%2019-43-32.png)<br>
After a little bit of trial and errors, I figured out the first if condition on param1 basically checks if two parameters are given.<br>
Now, "__s" is initialized with the first string and "__s_00" with the other.<br>
The next two checks see to it that both the strings are greater than 7 in length.<br>
After that, it checks whether length of both strings is **equal**.<br>
Then, it checks whether the <string-length>&1 is 0. When will this be 0? When the last byte or the least significant byte is 0. ie - when the string-length is **even**.<br>
Now, it iterates from the start of the string to the middle to the halfway point and checks whether the string is equal upto that.
If the string's **first half is same**, it moves forward.
Then, iterates over the later half of both strings and checks whether they are not equal.
If the **later half is not same**, we get :<br>`Abby & Gabby: yaayy!! nice job! :D`<br>
So, to sum up all of this, following are the constrainst on the the two parameters: <br>
- Two strings should be given.
- Their lengths should be equal, greater than 7 and even.
- The first half of the strings should be same.
- The second half should vary at each character.
