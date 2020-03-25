# Reversing-Challenge

So, we have this executable named glowwine. <br>
Running it without any argument returns the following : <br>
` usage: ./glowwine <key>` <br>
Running it with any random key, say 'aaaaa', returns: <br>
` wrong key, try again :/ ` <br>
Now, to investigate further, I opened it with gdb. Disassembling the main gives us : <br>
![Screen-shot](https://github.com/angad-k/crackmes/blob/master/glowwine/Screenshot%20from%202020-03-19%2021-39-08.png) <br>
So,from this disassembled code, I deduced the basic control flow as shown below.
(Note : The flowchart also contains elements which are results of deductions that I'll explain later.)<br>
![flow-chart](https://github.com/angad-k/crackmes/blob/master/glowwine/New%20Doc%202020-03-19%2021.21.41(2).jpg) <br>
A little about the flowchart : <br>
- Every jump statement is where I end that block and start a new one. <br>
- Blocks marked A0, A1, A2 and A3 are the blocks where the given key is checked for various conditions. <br>
- Other blocks which are not labelled basically print something to the screen. <br>
Now, lets start with **A0**. It has a JG jump at the end which is a jump that will take place if the sign flag and zero flag both are not set. The compare statement before it compares the value of whatever's stored at [rbp - 0x4] with 0x1. All of this and the fact that running the executable without any argument gave us the usage instructions point to the fact this check must be for whether an argument is given or not. Sure enough, if we set the breakpoint at the start of main by `break *main` and then run the program, it doesn't jump and goes into the next block thus printing the usage instructions. So, we are now pretty sure about A0's work.<br>
**A0 checks for whether we have given an argument or not.**<br>
Let's move on to **A1** now. A quick glance at it reveals to us that there's a call to some <strlen@plt> procedure. strlen must be returning us with length of some string. And which string are we focusing on in this program? No brownie points for guessing, THE KEY'S LENGTH!!! So, yeah. We might me checking the length of the string here. Also, the comparison with 0x5 in the next line points to the thought that key's length must be 5. And sure enough, running the code with the key "aaaaa" allows us to jump to the next block while using 'a' leads to us moving into a type of block that calls a procedure called "sorrybro". What does sorrybro do, you ask? A quick disassembly of the sorrybro function yields : <br> 
![Screen-shot](https://github.com/angad-k/crackmes/blob/master/glowwine/Screenshot%20from%202020-03-19%2022-52-05.png) <br>
It can be seen that it calls a puts procedure and then exits. So, the puts function basically prints some string to the screen and in this case, it prints "wrong key, try again :/". <br>
There are three such blocks in the program which call the sorry-bro procedure. We'll call these blocks "sorrybrocallers". So, our basic task will be avoiding passing into these blocks and passing all the conditions for the jump statements.<br>
Okay, so what did we learn from this A1 block? Length matters. And it's not like everyday life where the societal expectation is just a lower limit. Here, we require the length to be 5 and only 5.<br>
**A1 checks whether length of the given string is 5.**<br>
Okay, let's move to **A2** now. After all of those mov statements, what catches the eye is the compare where al register's contents are compared with 0x40. 0x40 is the ASCII code for **@**. Running the program with "@@@@@" helps us pass that jump. But there must be the restriction of being equal to @ on only one character of the string. To find out which is that, we run the program with "@aaaa" and "aaaa@" because intuitively that character might be at the start or the end. And you know what happens?<br>
*drumroll*<br>
*more drumroll*<br>
*aur thoda...*<br>
None of them works. Both of them send us to the *sorrybrocaller*<br>
**sed lyf** <br>
However, we can notice we add 0x1 to rax before comparison. This might mean it is the second character in the string.
Sure enough, "a@aaa" works and helps us pass into A3 and so does "b@bbb". <br>
**A2 checks whether the given key has '@' at the second place.**<br>
Now, **A3**. Here, now we can see that the most of the starting statements are same except for the fact that we are adding 0x2 to the rax register while previously adding 0x1 to it. This means here we are accesing the third character of the key. Using this logic for consecutive statements where we add 0x3 and 0x4, the flow of A2 block can be summarised as : <br>
- (74a) edx has ASCII value of key's 3rd character. <br>
- (75f) eax has ASCII value of key's 4th character. <br>
- (762) edx has sum of ASCII values of key's 3rd and 4th characters. <br>
- (776) eax has ASCII value of key's 5th character. <br>
- (779) eax has sum of ASCII values of key's 3rd, 4th and 5th characters. <br>
- (77b) eax is compared with 0x12c(300) <br>
Thus, the condition for the successful bypassing of the *sorrybrocaller* after A3 is that the sum of ASCII values of key's 3rd, 4th and 5th characters is 300. Let's keep all three of them as 'd(100)'. So, key can be "a@ddd". Running the program with that key gives : <br>
`nice one! Now, can you keygen me?` <br>
So, yeah. It works. 
Okay, so let's put together all the conditions on the key. <br>
1) A key should be given. No shit, Sherlock. <br>
2) Length of the key should be 5.<br>
3) Character in the second place must be '@'<br>
4) Sum of ASCII values of characters in 3rd, 4th and 5th places must be 300.<br>
5) No restrictions on the first character. He can be anything he wants. Doctor, Engineer, Standup comedian, Actor, Singer, Ventriloquist, kuch bhi matlab kuch bhi. The first character can take any ASCII value from 33 to 126.<br>
"a@cde" and "b@ddd" are two examples of the possible keys.
---
Using all these conditions, I coded a cpp program to print all the possible keys and also save them to a file called keys.txt. Both **keys.txt** and the cpp program **keygen.cpp** are available in this repository.



