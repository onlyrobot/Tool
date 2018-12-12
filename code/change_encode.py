import os
import re
path = 'E:/Temp/temp'
def traverse(path):
    print('current folder {}'.format(path))
    files = os.listdir(path)
    for file in files:
        if os.path.isdir(path + '/' + file):
            traverse(path + '/' + file)
        elif re.search(r'(\.(c|cpp|h|py))$', file):
            f = open(path + '/' + file, 'rb+')
            content = f.read()
            f.seek(0)
            try:
                f.write(content.decode('gbk').encode('utf-8'))
            except:
                print('error occurred when convert {}'.format(file))
            else:
                print('{} was converted'.format(file))
            finally:
                f.close()
        else:
            print('{} ignored'.format(file))
traverse(path)
