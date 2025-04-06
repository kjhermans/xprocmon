/**
* \file
* \brief This file is an autogenerated function prototypes header file.
*
* WARNING: This file is automatically generated. Any changes will be lost.
*/

#ifndef _XPROCMON_FUNCTIONS_H_
#define _XPROCMON_FUNCTIONS_H_

/* declared in src//XNextEventTimed.c */
extern
int XNextEventTimed
  (Display* dsp, XEvent* event_return, struct timeval* tv)
  __attribute__ ((warn_unused_result));

/* declared in src//absorb_file.c */
extern
int absorb_file
  (char* path, unsigned char** buf, unsigned* buflen)
  __attribute__ ((warn_unused_result));

/* declared in src//absorb_file.c */
extern
char* dup_file_string
  (char* path)
  __attribute__ ((warn_unused_result));

/* declared in src//main.c */
extern
int main
  (int argc, char* argv[])
  __attribute__ ((warn_unused_result));

/* declared in src//xprocmon_data.c */
extern
int xprocmon_data
  (pid_t pid, xprocmon_t* pm)
  __attribute__ ((warn_unused_result));

/* declared in src//xprocmon_data_examine.c */
extern
void xprocmon_data_examine
  (xprocmon_data_t* pmd);

/* declared in src//xprocmon_maps.c */
extern
int xprocmon_maps
  (pid_t pid, xprocmon_t* pm)
  __attribute__ ((warn_unused_result));

/* declared in src//xprocmon_stat.c */
extern
int xprocmon_stat
  (pid_t pid, xprocmon_t* pm)
  __attribute__ ((warn_unused_result));

/* declared in src//xprocmon_window.c */
extern
int xprocmon_window
  (pid_t pid)
  __attribute__ ((warn_unused_result));



#endif