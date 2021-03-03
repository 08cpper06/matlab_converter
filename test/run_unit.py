import subprocess
import os

def run(pth):
    in_file = pth + '.in'
    ok_file = pth + '.ok'
    print(pth + ' -> ', end='')

    proc = subprocess.Popen(['.\\build\\matlab_converter.exe', in_file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    log = proc.stdout.read()
    log = log.decode('utf-8')
    log = log.replace('\r', '')

    ok_log = "".join([item for item in open(ok_file, 'r')])

#    print(ok_log.encode('utf-8'))
#    print(log.encode('utf-8'))

    if ok_log == log and not proc.returncode:
        print('OK')
        return 0
    else:
        print('NG')
        return 1

