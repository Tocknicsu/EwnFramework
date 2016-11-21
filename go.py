#!/usr/bin/env python3
import subprocess as sp

alpha_start = 1e-3
alpha_end = 1e-4
step = 1000

for i in range(step):
    alpha = alpha_start - i * (alpha_start - alpha_end) / step
    sp.call('time ./ewn 50000 3 1 %s weight.table.0 3 1 %s weight.table.1' % (
        alpha, alpha
    ), shell=True)
