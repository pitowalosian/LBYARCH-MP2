# LBYARCH-MP2

## Performance Analysis

### ASM Average Execution Time 
 Y | Average Execution Time (ns) | Min | Max
<<<<<<< Updated upstream
--- | --- | --- | --- 
 10 | 56.67 | 0 | 300 
=======
--- | --- | --- | --- | ---
 10 | 116.67 | 0 | 300 
>>>>>>> Stashed changes
 100 | 476.67 | 200 | 600 
 1000 | 3266.67 | 2200 | 15200
 9000 | 19116.67 | 14900 | 73700

<<<<<<< Updated upstream
As seen from the table above, there is a positive relationship between the number of inputs and the average execution time, since the average execution time also increases when the number of inputs increase. This is understandable and valid due to sheer increase in the size of inputs per row. For comparison purposes, I created a `calc_accel_c` C function that is programmed to also calculate the acceleration, just like the `calc_accel` block in ASM. In a `y = 10` input size, the average execution time for the C function is `96.67 ns`, while the ASM code's average execution time is `56.67 ns` only. There is only a `40 ns` difference for this input size, however, we can already hypothesize that a larger input size will result to a much wider gap in the execution times of the two functions. To prove this, I used the largest input size my machine could run, `y = 9000`. The recorded average execution time for ASM is `19116.67 ns`, while it is a whopping `40053.33 ns` for C. There is a drastic `20936.66 ns` contrast between the two. From this, we can conclude that the Assembly language is much more efficient than C.
=======
As seen from the table above, there is a positive relationship between the number of inputs and the average execution time, since the average execution time also increases when the number of inputs increase. This is understandable and valid due to sheer size of inputs per row. For comparison purposes, I created a `calc_accel_c` C function that is programmed to also calculate the acceleration, just like the `calc_accel` block in ASM. In a `y = 10` input size, the average execution time for the C function is `143.33 ns`, while the ASM code's average execution time is `116.67 ns` only. There is only a `26.66 ns` difference for this input size, however, we can already hypothesize that a larger input size will result to a much wider gap in the execution times of the two functions. To prove this, I used the largest input size my machine could run, `y = 9000`. The recorded average execution time for ASM is `19116.67 ns`, while it is a whopping `60233.33 ns` for C. There is a drastic `20936.66 ns` contrast between the two. From this, we can conclude that the Assembly language is much more efficient than C.
>>>>>>> Stashed changes

## Take a screenshot of the program output with the correctness check.
For this part, I compared the output of the ASM function `calc_accel` with the output of the C function `calc_accel_c`. I also used an external website [see References] to cross-check these answers to get the accuracy of my program. 

![Screenshot_with_correctness_1)](/screenshots/car1.png)
![Screenshot_with_correctness_1)](/screenshots/car2.png)
![Screenshot_with_correctness_1)](/screenshots/car3.png)
![Screenshot_with_correctness_1)](/screenshots/car4.png)
![Screenshot_with_correctness_1)](/screenshots/car5.png)

**Note:** The program uses round to nearest rounding method, so it is implied that we also use the same rounding method when cross-checking with the acceleration calculator.

## Short Videos (5-10mins) showing your source code, compilation, and execution of the C and x86-64 program

## References
https://www.omnicalculator.com/physics/acceleration
