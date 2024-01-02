#include "dsd.h"

void
processNXDNData (dsd_opts * opts, dsd_state * state, FILE *logfile)
{
  int i, dibit;

  if (opts->errorbars == 1)
    {
      printf ("DATA    ");
      fprintf (logfile, "DATA    ");
    }

  for (i = 0; i < 30; i++)
    {
      dibit = getDibit (opts, state);
#ifdef NXDN_DUMP
      printf ("%c", dibit + 48);
      fprintf (logfile, "%c", dibit + 48);
#endif
    }
#ifdef NXDN_DUMP
  printf (" ");
  fprintf (logfile, " ");
#endif

  for (i = 0; i < 144; i++)
    {
      dibit = getDibit (opts, state);
#ifdef NXDN_DUMP
      printf ("%c", dibit + 48);
      fprintf (logfile, "%c", dibit + 48);
#endif
    }

  if (opts->errorbars == 1)
    {
      printf ("\n");
      fprintf (logfile, "\n");
    }
}
