import subprocess
import os

def run(pth):
    in_file = pth + '.in'
    ok_file = pth + '.ok'
    print(pth + ' -> ', end='')

    proc = subprocess.Popen(['.' + os.sep + 'build' + os.sep+ 'matlab_converter.exe', in_file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
#    proc = subprocess.run(['.' + os.sep + 'build' + os.sep+ 'matlab_converter.exe', in_file])
#    return
    log = proc.stdout.read()
    log = log.decode('utf-8')
    if os.name == 'nt':
        # CRLF -> LF
        log = log.replace('\r', '')

    err_log = proc.stderr.read()
    err_log = err_log.decode('utf-8')
    if os.name =='nt':
        # CRLF -> LF
        err_log = err_log.replace('\r', '')

    ok_log = "".join([item for item in open(ok_file, 'r')])

#    print(ok_log.encode('utf-8'))
#    print(log.encode('utf-8'))

    proc.kill()

    if ok_log == log and not proc.returncode:
        print('\033[33mOK\033[0m')
        return 0
    else:
        print('\033[31mNG')
        print('--- ok_file ---')
        print(ok_log.replace('\n', '↲\n'))
        print('--- actual ---')
        print(log.replace('\n', '↲\n'))
        print('--- error ---')
        print(err_log.replace('\n', '↲\n'))
        print('--------------\033[0m')
        return 1

