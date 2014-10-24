/*
	util.c
		Utility functions
		this file is part of Divonne
		last modified 17 Jan 05 th
*/


#include "decl.h"

static count ndim_, ncomp_, selectedcomp_, nregions_;
static number neval_, neval_opt_, neval_cut_;
static int sign_, phase_;

static Bounds border_;

static Samples samples_[3];
static Rule rule7_, rule9_, rule11_, rule13_;
static real *xgiven_, *fgiven_, *xextra_, *fextra_;
static count ldxgiven_;
static number ngiven_, nextra_;

static Totals *totals_;


#define Allocate(p, n) \
  if( (p = malloc((n)*sizeof(*p))) == NULL ) { \
    fprintf(stderr, "Out of memory in " __FILE__ " line %d.\n", __LINE__); \
    exit(1); \
  }


#ifdef DEBUG
#include "debug.c"
#endif

