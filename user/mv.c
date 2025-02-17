// Author - Will Rollitt

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

int mv(int, const char**);
int move(const char*, const char*);
int scan_args(int, const char**);
int usage(void);

BOOL MV_VERBOSE_F = FALSE;

int
main(int argc, char* argv[])
{
  if(argc != 3)
    return usage();

  return mv(argc, (const char**)argv);
}

int
mv(int argc, const char** argv)
{
  return scan_args(argc, argv);
}

int
move(const char* src, const char* dst)
{
  if(link(src, dst) < 0){
    fprintf(stderr, "mv : failed to move file %s\n", src);
    return -1;
  }

  switch(MV_VERBOSE_F){
    case TRUE:
      printf("%s -> %s\n", src, dst);
      break;
  }

  return unlink(src);
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
            MV_VERBOSE_F = TRUE;
            break;
          default:
            fprintf(stderr,
                "mv : unkown option - %c\n", argv[i][k]);
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

  return move(argv[include[0]], argv[include[1]]);

fail:
  return usage();
}

int
usage(void)
{
  fprintf(stderr,
      "usage : mv [-v] [source] [destination]\n");
  return -1;
}
