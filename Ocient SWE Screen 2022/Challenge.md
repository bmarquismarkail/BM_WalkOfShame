2022 HackerRank Screen Problem Description

You are tasked with coding an expression evaluation engine. This engine enables the evaluation of functional expressions of the form:

```
a(b(c(d,e)))
```

where any function `f` is defined in terms of one or more input arguments, and exactly one return value. As you might expect, an input argument to a function may be either a literal value (e.g. a number) or the return value/output of a function.

Function arguments and return values all have a well-defined data type: either integer or string. This implies that literals also fall into one of these two categories as well.

Your program should accept a function expression via `STDIN`, and emit the result of the function expression via `STDOUT`. As an example:

```
add(1,2)
```

read via `STDIN`, should emit

```
3
```

to `STDOUT`.

Suggested Approach

You should generally consider the input expression left-to-right. Whatever your chosen language, a helper function `consumeNextToken()` has been provided that will parse the "next" portion of the input string read from `STDIN`. While it is not required that you use this function, if you do, some of the tedium of parsing text from the input can be avoided. If you choose to use this function, note that it may require some minor modifications for it to work as you expect.

The problem below is divided into 4 sections:

- A "base-case" that you should tackle first.
- Three separate "complications" that add complexity to the base-case for additional points. These complications are independent of each other and you can consider them separately. Each provides an opportunity to score additional points.

You do not need to score 100% on this test to pass to the next interview round. We expect that most folks will not achieve a full submission. With that said, it is possible to complete all problem parts in the time allotted with approximately 100 - 300 lines of code, depending on language and your abstractions.

You may want to review the complications before tackling the base problem, in order to guide your approach. You may also implement part of a complication and move onto another, as they are designed to be independent for the majority of test cases and you can receive partial credit for completing part of a complication.

NOTE: HackerRank will test your code after the time limit is reached. If your code does not compile at that time, you will receive a 0. As the time limit approaches, please revert/comment out any changes you have in progress so that your code runs and at least some test cases pass.

Base Problem

Accept an input expression as described above, that correctly handles the following functions:

| Function      | Description                          | Input Types    | Return Type |
|---------------|--------------------------------------|----------------|-------------|
| add(x,y)      | Adds two integers: x+y               | int, int       | int         |
| sub(x,y)      | Subtracts two integers: x-y           | int, int       | int         |
| len(x)        | Computes the length of a string       | string         | int         |
| concat(x,y)   | Concatenates two strings              | string, string | string      |
| parse(x)      | Parses a string into an integer       | string         | int         |

Data Types

As mentioned above, literals (i.e., constants) have exactly one of two data types, either integer or string. Text read from the input stream will be presented in the specified input representation, and your program's output of the outer-most function's result should be in the specified output representation.

| Type    | Input Representation                                        | Output Representation                                      | Limits            |
|---------|------------------------------------------------------------|------------------------------------------------------------|--------------------|
| Integer | base-10 digits: 12345                                      | base-10 digits: 12345                                      | Value ranges [0,2^31-1] |
| String  | string of characters enclosed in quotation marks: "abc 123" | string of characters, no quotation marks: abc 123 | Maximum length 256 |

Test Cases

For all test cases in all parts, no invalid input will be presented, either in terms of syntax passed to `STDIN`, or in terms of arguments to functions (e.g., no test case will pass a string to `ADD`).

| Input                     | Output | Points |
|---------------------------|--------|--------|
| add(1,1)                  | 2      | 1      |
| sub(1,1)                  | 0      | 1      |
| len("abc123")             | 6      | 1      |
| concat("abc","123")       | abc123 | 1      |
| parse("123")              | 123    | 1      |
| add(add(1,1),1)           | 3      | 2      |
| add(1,add(1,1))           | 3      | 2      |
| len(concat("today","tomorrow")) | 13     | 2      |
| add(parse("5"),sub(parse("20"),parse("10"))) | 15     | 3      |

Complication #1: Improved Parsing and Variadic Arguments

Modify your existing parser to allow for whitespace characters around function arguments, and add the ability to parse negative numbers. This second modification increases the range for integers to be [-2^31,2^31-1]. These improvements will require modifications to the tokenizer function.

Test Cases

| Input           | Output | Points |
|-----------------|--------|--------|
| add(1 , 1)      | 2      | 2      |
| sub(1, -1)      | 2      | 2      |
| parse("-500")   | -500   | 2      |
| len("x and y")  | 7      | 2      |

Now modify the `add` and `concat` functions to accept and correctly process at least one, but an arbitrary number of arguments:

| Function       | Description                                         | Input Types    | Return Type |
|----------------|-----------------------------------------------------|----------------|-------------|
| add(a0,a1,a2,...,aN-1) | Adds N integers together, N >= 1           | integers       | int         |
| concat(s0,s1,...,sN-1) | Concatenates N strings together, in order, N >= 1 | strings        | string      |

Test Cases

| Input                  | Output | Points |
|------------------------|--------|--------|
| add(1,2,3,4,5)         | 15     | 2      |
| concat("a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z") | abcdefghijklmnopqrstuvwxyz | 2      |
| add(parse("1"),parse("2"),parse("3"),parse("4"),sub(6,1)) | 15     | 2      |
| sub(parse(concat("1","0","0")),parse(concat("5","0"))) | 50     | 2      |

Complication #2: Vectorization

Vectorization refers to a single operation acting on

 vectors of inputs, instead of scalars. In many situations, underlying hardware can do these types of operations quite efficiently using special instructions.

Add functions to enable mathematical operations on vectors of input arguments. To do this, you will need to modify your evaluation engine to include a new data type `int[]` which is an array/vector of integers.

You will not be expected to parse an array constant (see the `vector()` function below) but you will need to output one. You will also make a function called `reduce_add()` which will sum the elements in the vector and return an integer.

Data Types

| Type   | Input Representation                                              | Output Representation                                            | Limits          |
|--------|------------------------------------------------------------------|------------------------------------------------------------------|-----------------|
| int[]  | n/a                                                              | base-10 digits, in braces, separated by commas: [1,2,3,4,5]       | Individual values range[0,2^31-1] |

Functions

| Function           | Description                                                     | Input Types                     | Return Type |
|--------------------|-----------------------------------------------------------------|---------------------------------|-------------|
| vector(a0,a1,...,aN-1) | Constructs a vector from its inputs                              | integers                        | int[]       |
| range(start,stop)  | Constructs a vector consisting of the integers in [start, stop) | Integers                        | int[]       |
| addv(x,y)          | Pair-wise adds elements by index, resulting in a vector of the sums | int[], int[]                  | int[]       |
| reduce_add(v)      | Sums the elements in the vector                                  | int[]                           | int         |

Test Cases

| Input                                         | Output | Points |
|-----------------------------------------------|--------|--------|
| vector(1,1)                                   | [1,1]  | 2      |
| vector(1,2,3)                                 | [1,2,3] | 2      |
| addv(vector(1,2),vector(3,4))                  | [4,6]  | 2      |
| addv(vector(100,50),vector(-50,-50))           | [50,0] | 2      |
| addv(vector(10,100,1000),addv((vector(1000,1000,1000),vector(-10,-100,-1000))) | [1000,1000,1000] | 2      |
| addv(range(1,5),vector(1,1,1,1))                | [2,3,4,5] | 2      |
| subv(range(2,7),range(1,6))                    | [1,1,1,1,1] | 2      |
| reduce_add(range(0,11))                        | 55     | 2      |

Complication #3: Simple Branching

Branching is a powerful feature of programming languages. We can implement something basic in our expression engine. We can define a simple function `if_ge(val, comp, left, right)` where `val` is the value to be compared against `comp`, and depending on whether or not `val` is greater or equal to `comp`, we return the `left` or `right` value. If you have completed complication #2, `val` may additionally be a vector, and `left`, `right`, and `comp` will also be vectors of equal length. `if_ge()` will then function as an element-wise function, constructing a new vector containing values for `left` and `right` depending on the comparison of `val` and `comp`.

| Function             | Description                                                                      | Input Types                     | Return Type |
|----------------------|----------------------------------------------------------------------------------|---------------------------------|-------------|
| if_ge(val,comp,left,right) | Returns the `left` or `right` value depending on if `val >= comp`               | Integers, or int[] for `val` and `comp`, any for `left` and `right` | int, string, int[] |

Test Cases

| Input                                         | Output | Points |
|-----------------------------------------------|--------|--------|
| if_ge(4,4,"a","b")                            | a      | 2      |
| if_ge(add(1,3),sub(6,1),add(1,1),add(5,5))     | 10     | 2      |
| if_ge(add(1,3),sub(6,1),add(1,1,1),add(5,5,5)) | 15     | 2      |
| if_ge(range(1,5),range(0,4),range(1,5),range(0,4)) | [1,2,3,4] | 2      |
| if_ge(vector(0,1,0,1),vector(1,1,1,1),vector(5,6,7,8),vector(1,2,3,4)) | [1,6,3,8] | 2      |
| if_ge(reduce_add(vector(1,1,1,1)),4,"a","b")   | a      | 2      |