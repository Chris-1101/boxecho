#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "termwidth.h"

// Get Terminal Width
void get_term_width(Width *w)
{
  const char *term = ctermid(NULL);

  if (!term[0])
  {
    fprintf(stderr, "Failed to retrieve controlling terminal\n");
    exit(EXIT_FAILURE);
  }

  int stream = open(term, O_RDONLY);
  struct winsize ws;

  if (stream == -1)
  {
    fprintf(stderr, "Failed to open %s: %s\n", term, strerror(errno));
    exit(EXIT_FAILURE);
  }

  if (ioctl(stream, TIOCGWINSZ, &ws) == -1)
  {
    fprintf(stderr, "Failed to retrieve terminal width: %s\n", strerror(errno));
    exit(EXIT_FAILURE);
  }
  else
  {
    unsigned short width_term = ws.ws_col;
    unsigned short padding_frame = 4 * 2;
    unsigned short padding_content = padding_frame + (3 * 2);

    Width width = { width_term
                  , width_term - padding_frame
                  , width_term - padding_content };

    memcpy(w, &width, sizeof(*w));
  }
}
