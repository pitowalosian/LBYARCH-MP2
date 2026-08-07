# LBYARCH-MP2

## Performance Analysis

### Average Execution Time 
 Y | ASM Average Execution Time (ns) | C Average Execution Time (ns) | Difference | Min | Max | C Min | C Max
--- | --- | --- | --- | --- | --- | --- | ---
 10 |  24.67 | 26.00 | 1.33 | 10 | 50 | 0 | 60
 100 | 19.17 | 23.57 | 4.4 | 16 | 21 | 18 | 31
 1000 | 17.73 | 21.90 | 4.17 | 13 | 51 | 18 | 31 
 9000 | 17.37 | 21.30 | 3.93 | 13 | 33 | 19 | 30

The table above shows the average execution time in nanoseconds for Assembly and C implementations across varying input sizes. The data implies a negative relationship between the input size and average execution time. I assume that this is due to the program's code wherein the execution time for each `calc_accel` call is averaged, then the average of that is also averaged for each test. Larger input sizes could lead to higher variability or deviations (as seen in the table) in execution time, which could pull the average execution time lower.

For comparison purposes, I created a `calc_accel_c` C function that is programmed to also calculate the acceleration, just like the `calc_accel` block in ASM. In a `y = 10` input size, the average execution time for the C function is `26 ns`, while the ASM code's average execution time is `24.67 ns` only, leading to a `1.33 ns` difference for this input size.

Overall, the data supports the conclusion that ASM is more efficient than C, since all input sizes result to ASM having a quicker average execution time than C.

## Take a screenshot of the program output with the correctness check.
For this part, I compared the output of the ASM function `calc_accel` with the output of the C function `calc_accel_c`. I also used an external website [see References] to cross-check these answers to get the accuracy of my program. 

![Screenshot_with_correctness_1)](/screenshots/car1.png)
![Screenshot_with_correctness_1)](/screenshots/car2.png)
![Screenshot_with_correctness_1)](/screenshots/car3.png)
![Screenshot_with_correctness_1)](/screenshots/car4.png)
![Screenshot_with_correctness_1)](/screenshots/car5.png)

**Note:** The program uses round to nearest rounding method, so it is implied that we also use the same rounding method when cross-checking with the acceleration calculator.

## Short Videos (5-10mins) showing your source code, compilation, and execution of the C and x86-64 program
![Demo_video](/video/LBYARCH-MP2_Demo_Video.mp4)

## References
https://www.omnicalculator.com/physics/acceleration
