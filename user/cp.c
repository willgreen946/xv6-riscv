// Author - Will Rollitt

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int cp(int, const char**);
int copy(const char*, const char*);
int scan_args(int, const char**);
int usage(void);

BOOL CP_VERBOSE_F = FALSE;
BOOL CP_DIRECTORY_F = FALSE;

int
main(int argc, char* argv[])
{
  return (argc >= 2) ?
    cp(argc, (const char**)argv) : usage();
}

int
usage(void)
{
  fprintf(stdout,
      "usage : cp [-v | -r] [source] [destination]\n");
  return -1;
}

int
cp(int argc, const char** argv)
{
  return scan_args(argc, argv);
}

int
copy(const char* src, const char* dst)
{
  if(link(src, dst) < 0) {
    fprintf(stderr, "cp : failed to copy file %s\n", src);
    return -1;
  }

  switch(CP_VERBOSE_F){
    case TRUE:
      printf("%s -> %s\n", src, dst);
      break;
  }

  return 0;
}

int
scan_args(int argc, const char** argv)
{
  int i, k, inc, include[2];

  for(i = 1, inc = 0; i < argc; i++){
    if(argv[i][0] == '-') {
      for(k = 1; k < strlen(argv[i]); k++){
        switch(argv[i][k]){
          case 'v':
            CP_VERBOSE_F = TRUE;
            break;
          case 'r':
            CP_DIRECTORY_F = TRUE;
            break;
          default:
            fprintf(stderr,
                "cp : unkown option - %c\n", argv[i][k]);
            goto fail;
        }
      }
    }else{
      if(inc <= 1){
        include[inc] = i;
        ++inc;
      }else if(inc > 1)
        goto fail;
    }
  }

  if(inc != 2)
    goto fail;

  return copy(argv[include[0]], argv[include[1]]);

fail:
  return usage();
}
