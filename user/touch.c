// Author - Will Rollitt

#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int usage(void);
int touch(const char*);

int
main(int argc, char* argv[])
{
  int i;

  if (argc < 2)
    return usage();

  for(i = 1; i < argc; i++){
    if (touch((const char*)argv[i]) < 0)
      return -1;
  }

  return 0;
}

int
usage(void)
{
  fprintf(stderr,
      "usage : touch [file]\n");
  return -1;
}

int
touch(const char* file)
{
  int fd = -1;

  if((fd = open(file, O_WRONLY | O_CREATE)) < 0){
    fprintf(stderr,
        "touch : failed to create file %s\n", file);
    return -1;
  }

  close(fd);

  return 0;
}
