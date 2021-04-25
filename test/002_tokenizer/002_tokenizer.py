import subprocess
import os
import sys

sys.path.insert(0, '..')
import run_unit
sys.path.remove('..')


def run():
    ret = 0
    ret += 1 if run_unit.run('./test/002_tokenizer/001') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/002') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/003') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/004') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/005') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/006') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/007') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/008') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/009') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/010') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/011') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/012') else 0
    ret += 1 if run_unit.run('./test/002_tokenizer/013') else 0

    return ret
