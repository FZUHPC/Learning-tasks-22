#!/bin/bash

gcc medianFilter.c  -fopenmp -o medianFilter

gcc check.c -o check
