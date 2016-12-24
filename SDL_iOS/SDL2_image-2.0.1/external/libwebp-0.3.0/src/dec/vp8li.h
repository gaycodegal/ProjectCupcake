// Copyright 2012 Google Inc. All Rights Reserved.
//
// This code is licensed under the same terms as WebM:
//  Software License Agreement:  http://www.webmproject.org/license/software/
//  Additional IP Rights Grant:  http://www.webmproject.org/license/additional/
// -----------------------------------------------------------------------------
//
// Lossless decoder: internal header.
//
// Author: Skal (pascal.massimino@gmail.com)
//         Vikas Arora(vikaas.arora@gmail.com)

#ifndef WEBP_DEC_VP8LI_H_
#define WEBP_DEC_VP8LI_H_

#include <string.h>     // for memcpy()
#include "./webpi.h"
#include "../utils/bit_reader.h"
#include "../utils/color_cache.h"
#include "../utils/huffman.h"
#include "../webp/format_constants.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef enum {
  READ_DATA = 0,
  READ_HDR = 1,
  READ_DIM = 2
} VP8LDecodeState;

typedef struct VP8LTransform VP8LTransform;
struct VP8LTransform {
  VP8LImageTransformType type_;   // transform type.
  int                    bits_;   // subsampling bits defining transform window.
  int                    xsize_;  // transform window X index.
  int                    ysize_;  // transform window Y index.
  uint32_t              *data_;   // transform data.
};

typedef struct {
  HuffmanTree htrees_[HUFFMAN_CODES_PER_META_CODE];
} HTreeGroup;

typedef struct {
  int             color_cache_size_;
  VP8LColorCache  color_cache_;

  int             huffman_mask_;
  int             huffman_subsample_bits_;
  int             huffman_xsize_;
  uint32_t       *huffman_image_;
  int             num_htree_groups_;
  HTreeGroup     *htree_groups_;
} VP8LMetadata;

typedef struct {
  VP8StatusCode    status_;
  VP8LDecodeState  action_;
  VP8LDecodeState  state_;
  VP8Io           *io_;

  const WebPDecBuffer *output_;    // shortcut to io->opaque->output

  uint32_t        *pixels_;        // Internal data: either uint8_t* for alpha
                                   // or uint32_t* for BGRA.
  uint32_t        *argb_cache_;    // Scratch buffer for temporary BGRA storage.

  VP8LBitReader    br_;

  int              width_;
  int              height_;
  int              last_row_;      // last input row decoded so far.
  int              last_out_row_;  // last row output so far.

  VP8LMetadata     hdr_;

  int              next_transform_;
  VP8LTransform    transforms_[NUM_TRANSFORMS];
  // or'd bitset storing the transforms types.
  uint32_t         transforms_seen_;

  uint8_t         *rescaler_memory;  // Working memory for rescaling work.
  WebPRescaler    *rescaler;         // Common rescaler for all channels.
} VP8LDecoder;

//------------------------------------------------------------------------------
// internal functions. Not public.

// in vp8l.c

// Decodes a raw image stream (without header) and store the alpha data
// into *output, which must be of size width x height. Returns false in case
// of error.
int VP8LDecodeAlphaImageStream(int width, int height, const uint8_t* const data,
                               size_t data_size, uint8_t* const output);

// Allocates and initialize a new lossless decoder instance.
VP8LDecoder* VP8LNew(void);

// Decodes the image header. Returns false in case of error.
int VP8LDecodeHeader(VP8LDecoder* const dec, VP8Io* const io);

// Decodes an image. It's required to decode the lossless header before calling
// this function. Returns false in case of error, with updated dec->status_.
int VP8LDecodeImage(VP8LDecoder* const dec);

// Resets the decoder in its initial state, reclaiming memory.
// Preserves the dec->status_ value.
void VP8LClear(VP8LDecoder* const dec);

// Clears and deallocate a lossless decoder instance.
void VP8LDelete(VP8LDecoder* const dec);

//------------------------------------------------------------------------------

#if defined(__cplusplus) || defined(c_plusplus)
}    // extern "C"
#endif

#endif  /* WEBP_DEC_VP8LI_H_ */
