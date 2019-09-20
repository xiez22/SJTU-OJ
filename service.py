import os
import shutil

add_src = 'E:/Project/C++/Project'
add_dest = 'E:/Project/SJTU-OJ/Code/'

for i in range(1000, 5000):
    try:
        if (os.path.exists(add_src + str(i))):
            if (os.path.exists(add_src + str(i) + '/源.cpp')):
                shutil.copyfile(add_src + str(i) +
                                '/源.cpp', add_dest + str(i) + '.cpp')
            else:
                shutil.copyfile(add_src + str(i) + '/Project'+str(i) +
                                '/源.cpp', add_dest + str(i) + '.cpp')
    except Exception as err:
        print(err)
