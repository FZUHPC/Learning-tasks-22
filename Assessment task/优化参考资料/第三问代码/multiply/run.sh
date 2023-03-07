#!/bin/bash
gcc multiply.c -fopenmp -mavx2 -o muliply
gcc check.c -o check
