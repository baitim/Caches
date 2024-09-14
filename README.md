<h1 align="center">Caches</h1>

## Description

 Implementation of the LFU(least frequently used), ARC(adaptive replacement) and Belady's cache and their comparison.

## How to run

1. Clone <br>
    write <code>git clone https://github.com/baitim/Caches.git</code> in terminal

2. Go to folder <br>
    write <code>cd Caches</code> in terminal

3. Build <br>
    write <code>cmake . -B build ; cmake --build build</code> in terminal

4. Run <br>
    for LFU:    write <code>./build/src/lfu</code> in terminal <br>
    for ARC:    write <code>./build/src/arc</code> in terminal <br>
    for Belady: write <code>./build/src/belady</code> in terminal

## How to test

1. Run testing <br>
    write <code>ctest --test-dir build</code> in terminal

2. The test result will be in the "tests/tests_dat/answer.out" file

<p align="center"><img src="https://github.com/baitim/Caches/blob/main/images/cat.gif" width="40%"></p>

## Support
**This project is created by [baitim](https://t.me/bai_tim)**
