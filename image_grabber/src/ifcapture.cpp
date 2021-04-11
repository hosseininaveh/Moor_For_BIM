#include "ros/ros.h"
#include "std_msgs/String.h"
#include <iostream>
#include <termios.h>
#include <sys/select.h>     //Used for kbhit and getch_
#include <sys/ioctl.h>      //Used for kbhit and getch_
#include <stropts.h>        //Used for kbhit and getch_
int _kbhit() {
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

static struct termios old;
static struct termios NEW;

/* Initialize new terminal i/o settings */
void initTermios(int echo)
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  NEW = old; /* make new settings same as old settings */
  NEW.c_lflag &= ~ICANON; /* disable buffered i/o */
  NEW.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &NEW); /* use these new terminal i/o settings now */
}
/* Restore old terminal i/o settings */
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "ifcapture");
  ros::NodeHandle nh;

  ros::Publisher chatter_pub = nh.advertise<std_msgs::String>("IfCapture", 1);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    std_msgs::String msg;
    char command;
    if (_kbhit())
      command=getch_(0);
    else
      command=' '; ///a non used character
    msg.data = command;
    chatter_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
