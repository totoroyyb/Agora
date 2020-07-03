#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "local_phy_ldpc_encoder_5gnr_internal.h"
#include "phy_ldpc_encoder_5gnr.h"
#include <stdlib.h>

#define BITMASKU8(x) ((1U << (x)) - 1)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

namespace avx2enc {
static constexpr size_t kProcBytes = 32;
};

// kMaxProcBytes is 64 bytes in FlexRAN's LDPC encoder and 32 bytes in Millipede's
// derived LDPC encoder. Using the larger of the two works.
static constexpr size_t kMaxProcBytes = 64;

#endif
