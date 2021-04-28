import sys
import os
import subprocess
from importlib import import_module

sys.dont_write_bytecode = True


test_case = [
                '001_step',
                '002_tokenizer',
                '004_untokenizer'
            ]


def get_make_cmd():
    if os.name == 'nt':
        return 'mingw32-make'
    return 'make'


def run_test(test_dir):
    mod = import_module(test_dir + '.' + test_dir)
    return mod.run()


if __name__ == '__main__':
    subprocess.run([get_make_cmd(), 'clean'])
    subprocess.run([get_make_cmd()])
    test_dir = '.' + os.sep + 'test' + os.sep

    sys.path.insert(0, test_dir)
    for item in test_case:
        if not os.path.isdir(test_dir + item):
            print(item + ' is not directory')
            exit(1)
        else:
            print('--- ' + item + ' ---')
            if not run_test(item):
                print('\033[33mTEST SSUCCEED!!\033[0m')
            else:
                print('\033[31mTEST FAILED!!\033[0m')

    sys.path.remove(test_dir)
