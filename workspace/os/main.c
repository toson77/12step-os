#include "defines.h"
#include "intr.h"
#include "interrupt.h"
#include "serial.h"
#include "lib.h"

static void intr(softvec_type_t type, unsigned long sp)
{
  int c;
  static char buf[32];
  static int len;
  c = getc();
  if (c != '\n') {
    buf[len++] = c;
  } else {
    buf[len++] = '\0';
    if(!strncmp(buf, "echo", 4)) {
      puts(buf+4);
      puts("\n");
    } else {
      puts("unknown.\n");
    }
    puts("> ");
    len = 0;
  }
}

static int start_threads(int argc, char *argv[])
{
  kz_run(test08_1_main, "command", 0x100, 0, NULL);
  return 0;
}

int main() {
  INTR_DISABLE;
  puts("kozos boot succeed!\n");
  kz_start(start_threads, "start", 0x100, 0, NULL);
 return 0;
}
