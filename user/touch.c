#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int touch(const char *);

int
main(int argc, const char * argv[])
{
  int i;

  for(i = 1; i < argc; i++){
    if (touch(argv[i]) < 0)
      return -1;
  }

  return 0;
}

int
touch(const char * file)
{
  volatile signed int fd = -1;

  if((fd = open(file, O_WRONLY | O_CREATE)) < 0){
    printf("Failed to create file %s\n", file);
    return -1;
  }

  close(fd);

  return 0;
}
