// Reference : http://www.ibm.com/developerworks/cn/linux/l-serials/index.html

#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix标准函数定义*/
#include     <sys/types.h>  /**/
#include     <sys/stat.h>   /**/
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX终端控制定义*/
#include     <errno.h>      /*错误号定义*/


#define FALSE 0
#define TRUE 1

/***@brief  设置串口通信速率
 *@param  fd     类型 int  打开串口的文件句柄
 *@param  speed  类型 int  串口速度
 *@return  void*/

int speed_arr[] = { B38400, B19200, B9600, B4800, B2400, B1200, B300,
    B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = {38400,  19200,  9600,  4800,  2400,  1200,  300,
    38400,  19200,  9600, 4800, 2400, 1200,  300, };
void SetSpeed(int fd, int speed)
{
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);
    for ( i= 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
    {
        if  (speed == name_arr[i])
        {
            tcflush(fd, TCIOFLUSH);
            cfsetispeed(&Opt, speed_arr[i]);
            cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt);
            if  (status != 0)
                perror("tcsetattr fd1");
            return;
        }
        tcflush(fd,TCIOFLUSH);
    }
}
/**
 *@brief   设置串口数据位，停止位和效验位
 *@param  fd     类型  int  打开的串口文件句柄*
 *@param  databits 类型  int 数据位   取值 为 7 或者8*
 *@param  stopbits 类型  int 停止位   取值为 1 或者2*
 *@param  parity  类型  int  效验类型 取值为N,E,O,,S
 */
int SetParity(int fd,int databits,int stopbits,int parity)
{
    struct termios options;
    if  ( tcgetattr( fd,&options)  !=  0)
    {
        perror("SetupSerial 1");
        return(FALSE);
    }
    options.c_cflag &= ~CSIZE;
    switch (databits) /*设置数据位数*/
    {
        case 7:
            options.c_cflag |= CS7;
            break;
        case 8:
            options.c_cflag |= CS8;
            break;
        default:
            fprintf(stderr,"Unsupported data size\n");
            return (FALSE);
    }
    switch (parity)
    {
        case 'n':
        case 'N':
            options.c_cflag &= ~PARENB;   /* Clear parity enable */
            options.c_iflag &= ~INPCK;     /* Enable parity checking */
            break;
        case 'o':
        case 'O':
            options.c_cflag |= (PARODD | PARENB);  /* 设置为奇效验*/
            options.c_iflag |= INPCK;             /* Disnable parity checking */
            break;
        case 'e':
        case 'E':
            options.c_cflag |= PARENB;     /* Enable parity */
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/
            options.c_iflag |= INPCK;       /* Disnable parity checking */
            break;
        case 'S':
        case 's':  /*as no parity*/
            options.c_cflag &= ~PARENB;
            options.c_cflag &= ~CSTOPB;
            break;
        default:
            fprintf(stderr,"Unsupported parity\n");
            return (FALSE);
    }
    /* 设置停止位*/
    switch (stopbits)
    {
        case 1:
            options.c_cflag &= ~CSTOPB;
            break;
        case 2:
            options.c_cflag |= CSTOPB;
            break;
        default:
            fprintf(stderr,"Unsupported stop bits\n");
            return (FALSE);
    }
    /* Set input parity option */
    if (parity != 'n')
        options.c_iflag |= INPCK;
    options.c_cc[VTIME] = 150; // 15 seconds
    options.c_cc[VMIN] = 0;

    tcflush(fd,TCIFLUSH); /* Update the options and do it NOW */
    if (tcsetattr(fd,TCSANOW,&options) != 0)
    {
        perror("SetupSerial 3");
        return (FALSE);
    }
    return (TRUE);
}
/**
 *@breif 打开串口
 */
int OpenDev(char *Dev)
{
    int fd = open( Dev, O_RDWR);         //| O_NOCTTY | O_NDELAY
    if (-1 == fd)
    { /*设置数据位数*/
        perror("Can't Open Serial Port");
        return -1;
    }
    else
        return fd;

}
/**
 *@breif     main()
 */
int main(int argc, char **argv)
{
    int fd;
    int nread;
    char buff[512], readbuff[32];

    if (argc < 2) {
        printf("Usage: %s devicefile \n", *argv);
        exit(1);
    }

    char *dev = *(argv + 1);

    printf("Device: %s \n", dev);
    fd = OpenDev(dev);
    printf("Device opened\n");

    if (fd > 0) {
        printf("Begin set speed\n");
        SetSpeed(fd, 9600);
    } else {
        printf("Can't Open Serial Port!\n");
        exit(0);
    }

    printf("Begin set parity\n");
    if (SetParity(fd,8,1,'N') == FALSE) {
        printf("Set Parity Error\n");
        exit(1);
    }

    sleep(3); // wait for Arduino

    while(1) {
        char w[] = "hello$";
        int x = write(fd, w, 6);
        if (x == -1) {
            perror("Can't write to device");
        }

        int buffi=0;
        int tempi=0;

        while((nread = read(fd,readbuff, 32)) > 0) {
            for (tempi=0; tempi<nread; tempi++) {
                buff[buffi++] = readbuff[tempi];
            }
        }

        buff[buffi]='\0';
        printf("Reply:%s\n",buff);
    }
    //close(fd);
    //exit(0);
}
