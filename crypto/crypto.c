#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>

char buf[2048];

int main() {
  int fd;
  fd = open("/dev/switch_dev", O_RDWR);
  read(fd, buf, 1024);
  if ( !strcmp(buf, "button: 1") ) {
    system("redis-cli incr button && redis-cli expire button 5");
  }

  srand((unsigned int)time(NULL) * getpid());
  if ( (int)(rand() % 100) > 50 ) {
    sprintf(buf, "redis-cli incrby token_balance %d", (int)(rand() % 10000));
    system(buf);
  }
  return 0;
}
