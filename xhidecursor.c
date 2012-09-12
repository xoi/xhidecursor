#include <stdlib.h>
#include <string.h>
#include <X11/extensions/Xfixes.h>
#include <X11/extensions/XInput2.h>

int main(int argc, char *argv[])
{
  int idle_time = 5;

  if (argc > 1)
    idle_time = atoi(argv[1]);

  Display *display = XOpenDisplay(NULL);
  Window root = DefaultRootWindow(display);

  // not check version

  XIEventMask eventmask;
  unsigned char mask[(XI_LASTEVENT + 7)/8];

  memset(mask, 0, sizeof(mask));

  eventmask.deviceid = XIAllMasterDevices;
  eventmask.mask_len = sizeof(mask);
  eventmask.mask = mask;
  XISetMask(mask, XI_RawMotion);

  XISelectEvents(display, root, &eventmask, 1);

  struct timeval timeout;
  fd_set readfds;
  int fd = ConnectionNumber(display);
  int nfds = fd + 1;

  XEvent event;
  int n;
  for (;;) {
    // loop until cursor idle
    do {
      // discard all events
      for (n = XPending(display); 0 < n; --n)
	XNextEvent(display, &event);

      FD_ZERO(&readfds);
      FD_SET(fd, &readfds);
      timeout.tv_sec = idle_time;
      timeout.tv_usec = 0;
    } while (select(nfds, &readfds, NULL, NULL, &timeout) != 0);

    XFixesHideCursor(display, root);

    // wait for motion event
    XNextEvent(display, &event);
    // discard all events in the queue
    for (n = XEventsQueued(display, QueuedAlready); 0 < n; --n)
      XNextEvent(display, &event);

    XFixesShowCursor(display, root);
  }
}
