#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>

//程序:从一个文件的文件空洞中写入N个字节
//    从一个文件的文件空洞中读取N个字节
int main(int argc, char *argv[])
{
    int fd;
    char filname;
    //判断输入是否满足要求
    if (argc != 3 || strcmp(argv[1], "--help") == 0)
    {
        usageErr("%s file usage\n", argv[0]);
    }

    filname = argv[1];

    //打开文件
    fd = open(filname, O_RDWR | O_CREAT, 00644);
    if (-1 == fd)
    {
        perror("open file errno");
        goto _out1;
    }
    //循环执行程序
    for (ap = 2; ap < argc; ap++)
    {
        //条件选择
        switch (argv[ap][0])
        {
            //case 'r' 不使用 break,与case ‘R’使用一个执行语句
        case 'r':
            //read file N bytes and display it
        case 'R':
            len = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
            buf = malloc(len);
            if (NULL == buf)
            {
                perror("allot memory error");
                goto _out1;
            }

            numread = read(fd, buf, len);
            if (-1 == numread)
            {
                perror("read file error");
                goto _out1;
            }
            if (0 == numread)
            {
                printf("%s : end-of-file\n", argv[ap]);
            }
            else
            {
                printf("%s:", argv[ap]);
                for (j = 0; j < numread; j++)
                {
                    if (argv[ap][0] == 'r')
                        printf("%c", );
                    else
                    {
                        printf("%02x", );
                    }
                }
            }
            break;

            //write file N bytes and display it
        case 'w':
            numwrite = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
            if (-1 == numwrite)
            {
                perror("write file error");
                goto _out1;
            }
            printf("%s:wrote %ld bytes\n", argv[ap], (long)numwrite);
            break;

            //change file offset
        case 's':
            offset = getLong(&argv[ap][1], GN_ANY_BASE, argv[ap]);
            if (-1 == lseek(fd, offset, SEEK_SET))
            {
                perror("lseek file error");
                goto _out1;
            }
            printf("%s: seek successd\n", argv[ap]);
            break;

            //default output errno
        default:
            cmdlineerro("argument must start with [rRws]: %s\n", argv[ap]);
        }
    }

    exit(EXIT_SUCCESS);

_out:
    eixt(EXIT_FAILURE);
}