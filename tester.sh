#!/bin/bash
./ex2 <test1.in> result1.out
./ex2 <test2.in> result2.out
diff result1.out expected1.out
diff result2.out expected2.out

