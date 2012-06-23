/* -*- c++ -*- */
/*
 * Copyright 2004,2010 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

/*
 * config.h is generated by configure.  It contains the results
 * of probing for features, options etc.  It should be the first
 * file included in your .cc file.
 */
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <howto_square_ff.h>
#include <gr_io_signature.h>
#include <dsd.h>

/*
 * Create a new instance of howto_square_ff and return
 * a boost shared_ptr.  This is effectively the public constructor.
 */
howto_square_ff_sptr
howto_make_square_ff ()
{
  return gnuradio::get_initial_sptr(new howto_square_ff ());
}

/*
 * Specify constraints on number of input and output streams.
 * This info is used to construct the input and output signatures
 * (2nd & 3rd args to gr_block's constructor).  The input and
 * output signatures are used by the runtime system to
 * check that a valid number and type of inputs and outputs
 * are connected to this block.  In this case, we accept
 * only 1 input and 1 output.
 */
static const int MIN_IN = 1;	// mininum number of input streams
static const int MAX_IN = 1;	// maximum number of input streams
static const int MIN_OUT = 1;	// minimum number of output streams
static const int MAX_OUT = 1;	// maximum number of output streams

/*
 * The private constructor
 */
howto_square_ff::howto_square_ff ()
  : gr_block ("square_ff",
	      gr_make_io_signature (MIN_IN, MAX_IN, sizeof (short)),
	      gr_make_io_signature (MIN_OUT, MAX_OUT, sizeof (short)))
{
  dsd_opts opts;
  dsd_state state;

  initOpts (&opts);
  initState (&state);

  opts.gnuradio = 1;

  // Hard-code Provoice options (-fp) for now.
  opts.frame_dstar = 0;
  opts.frame_x2tdma = 0;
  opts.frame_p25p1 = 0;
  opts.frame_nxdn48 = 0;
  opts.frame_nxdn96 = 0;
  opts.frame_dmr = 0;
  opts.frame_provoice = 1;
  state.samplesPerSymbol = 5;
  state.symbolCenter = 2;
  opts.mod_c4fm = 0;
  opts.mod_qpsk = 0;
  opts.mod_gfsk = 1;
  state.rf_mod = 2;
  printf ("Setting symbol rate to 9600 / second\n");
  printf ("Enabling only GFSK modulation optimizations.\n");
  printf ("Decoding only ProVoice frames.\n");

  // Hard-code unvoiced quality (-u 10) for now.
  opts.uvquality = 10;

  // Hard-code verbosity (-v 1) for now.
  opts.verbose = 1;

  // Hard-code GFSK optimizations (-mg) for now.
  opts.mod_c4fm = 0;
  opts.mod_qpsk = 0;
  opts.mod_gfsk = 1;
  state.rf_mod = 2;
  printf ("Enabling only GFSK modulation optimizations.\n");

  // Initialize the mutex
  if(pthread_mutex_init(&mutex, NULL))
  {
//    printf("Unable to initialize a mutex\n");
  }
  pthread_mutex_lock(&mutex);
  pthread_t dsd_thread;
//  if(pthread_create(&dsd_thread, NULL, &opponent, NULL))
//  {
//    printf("Unable to spawn thread\n");
//  }  
}

/*
 * Our virtual destructor.
 */
howto_square_ff::~howto_square_ff ()
{
  // nothing else required in this example
}

void
howto_square_ff::forecast (int noutput_items,
                           gr_vector_int &ninput_items_required)
{
  // Input rate is 48000, output rate is 8000.
  ninput_items_required[0] = noutput_items * 6;
}

int
howto_square_ff::general_work (int noutput_items,
			       gr_vector_int &ninput_items,
			       gr_vector_const_void_star &input_items,
			       gr_vector_void_star &output_items)
{
  const short *in = (const short *) input_items[0];
  short *out = (short *) output_items[0];

  for (int i = 0; i < noutput_items; i++){
    out[i] = in[i] * in[i];
  }

  // Tell runtime system how many input items we consumed on
  // each input stream.

  consume_each (noutput_items);

  // Tell runtime system how many output items we produced.
  return noutput_items;
}
