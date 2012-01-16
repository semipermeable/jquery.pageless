
#line 1 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
#include <assert.h>
#include <ruby.h>

#if defined(_WIN32)
#include <stddef.h>
#endif

#ifdef HAVE_RUBY_RE_H
#include <ruby/re.h>
#else
#include <re.h>
#endif

#ifdef HAVE_RUBY_ENCODING_H
#include <ruby/encoding.h>
#define ENCODED_STR_NEW(ptr, len) \
    rb_enc_str_new(ptr, len, rb_utf8_encoding())
#else
#define ENCODED_STR_NEW(ptr, len) \
    rb_str_new(ptr, len)
#endif

#define LF_FLAG      0
#define CRLF_FLAG    1
#define LF           "\n"
#define CRLF         "\r\n"

#ifndef RSTRING_PTR
#define RSTRING_PTR(s) (RSTRING(s)->ptr)
#endif

#ifndef RSTRING_LEN
#define RSTRING_LEN(s) (RSTRING(s)->len)
#endif

#define DATA_GET(FROM, TYPE, NAME) \
  Data_Get_Struct(FROM, TYPE, NAME); \
  if (NAME == NULL) { \
    rb_raise(rb_eArgError, "NULL found for " # NAME " when it shouldn't be."); \
  }
 
typedef struct lexer_state {
  int content_len;
  int line_number;
  int current_line;
  int start_col;
  int eol;
  size_t mark;
  size_t keyword_start;
  size_t keyword_end;
  size_t next_keyword_start;
  size_t content_start;
  size_t content_end;
  size_t query_start;
  size_t last_newline;
  size_t final_newline;
} lexer_state;

static VALUE mGherkin;
static VALUE mCLexer;
static VALUE cI18nLexer;
static VALUE rb_eGherkinLexingError;

#define LEN(AT, P) (P - data - lexer->AT)
#define MARK(M, P) (lexer->M = (P) - data)
#define PTR_TO(P) (data + lexer->P)

#define STORE_KW_END_CON(EVENT) \
  store_multiline_kw_con(listener, # EVENT, \
    PTR_TO(keyword_start), LEN(keyword_start, PTR_TO(keyword_end - 1)), \
    PTR_TO(content_start), LEN(content_start, PTR_TO(content_end)), \
    lexer->current_line, lexer->eol); \
    if (lexer->content_end != 0) { \
      p = PTR_TO(content_end - 1); \
    } \
    lexer->content_end = 0

#define STORE_ATTR(ATTR) \
    store_attr(listener, # ATTR, \
      PTR_TO(content_start), LEN(content_start, p), \
      lexer->line_number)


#line 239 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"


/** Data **/

#line 92 "ext/gherkin_lexer_it/gherkin_lexer_it.c"
static const char _lexer_actions[] = {
	0, 1, 0, 1, 1, 1, 2, 1, 
	3, 1, 4, 1, 5, 1, 6, 1, 
	7, 1, 8, 1, 9, 1, 10, 1, 
	11, 1, 14, 1, 15, 1, 16, 1, 
	17, 1, 18, 1, 19, 1, 20, 1, 
	21, 2, 1, 16, 2, 11, 0, 2, 
	12, 13, 2, 15, 0, 2, 15, 2, 
	2, 15, 14, 2, 15, 17, 2, 16, 
	4, 2, 16, 5, 2, 16, 6, 2, 
	16, 7, 2, 16, 8, 2, 16, 14, 
	2, 18, 19, 2, 20, 0, 2, 20, 
	2, 2, 20, 14, 2, 20, 17, 3, 
	3, 12, 13, 3, 9, 12, 13, 3, 
	10, 12, 13, 3, 11, 12, 13, 3, 
	12, 13, 16, 3, 15, 12, 13, 4, 
	1, 12, 13, 16, 4, 15, 0, 12, 
	13
};

static const short _lexer_key_offsets[] = {
	0, 0, 19, 20, 21, 39, 40, 41, 
	45, 50, 55, 60, 65, 70, 74, 78, 
	80, 81, 82, 83, 84, 85, 86, 87, 
	88, 89, 90, 91, 92, 93, 94, 95, 
	96, 97, 99, 104, 111, 116, 117, 118, 
	119, 120, 121, 122, 123, 124, 125, 126, 
	127, 128, 129, 130, 131, 146, 148, 150, 
	152, 154, 156, 158, 160, 162, 164, 166, 
	168, 170, 172, 174, 176, 194, 195, 196, 
	197, 199, 200, 201, 202, 203, 204, 205, 
	206, 213, 215, 217, 219, 221, 223, 225, 
	227, 229, 231, 233, 235, 237, 239, 240, 
	241, 242, 243, 244, 245, 246, 247, 248, 
	249, 250, 251, 252, 253, 254, 265, 267, 
	269, 271, 273, 275, 277, 279, 281, 283, 
	285, 287, 289, 291, 293, 295, 297, 299, 
	301, 303, 305, 307, 309, 311, 313, 315, 
	317, 319, 321, 323, 325, 327, 329, 331, 
	333, 335, 337, 339, 341, 343, 345, 348, 
	350, 352, 354, 356, 358, 360, 362, 364, 
	366, 368, 370, 372, 374, 376, 378, 380, 
	382, 383, 384, 385, 386, 387, 389, 390, 
	391, 392, 393, 394, 395, 396, 397, 413, 
	415, 417, 419, 421, 423, 425, 427, 429, 
	431, 433, 435, 437, 439, 441, 443, 445, 
	447, 449, 451, 453, 455, 457, 459, 461, 
	463, 465, 467, 469, 471, 473, 475, 477, 
	479, 481, 483, 485, 487, 489, 491, 493, 
	495, 497, 499, 501, 503, 505, 507, 509, 
	512, 514, 516, 518, 520, 522, 524, 526, 
	528, 530, 532, 534, 536, 538, 540, 542, 
	544, 546, 547, 548, 549, 550, 551, 552, 
	553, 554, 555, 556, 557, 558, 559, 560, 
	561, 562, 563, 564, 565, 566, 567, 582, 
	584, 586, 588, 590, 592, 594, 596, 598, 
	600, 602, 604, 606, 608, 610, 612, 614, 
	616, 618, 620, 622, 624, 626, 628, 630, 
	632, 634, 636, 638, 640, 642, 644, 646, 
	648, 650, 652, 654, 656, 658, 660, 662, 
	664, 666, 668, 670, 672, 674, 676, 680, 
	686, 689, 691, 697, 715, 717, 719, 721, 
	723, 725, 727, 729, 731, 733, 735, 737, 
	739, 741, 743, 745, 747, 749, 751, 753, 
	755, 757, 759, 761, 763, 765, 767, 770, 
	772, 774, 776, 778, 780, 782, 784, 786, 
	788, 790, 792, 794, 796, 798, 800, 802, 
	804, 806
};

static const char _lexer_trans_keys[] = {
	-17, 10, 32, 34, 35, 37, 42, 64, 
	65, 67, 68, 69, 70, 77, 81, 83, 
	124, 9, 13, -69, -65, 10, 32, 34, 
	35, 37, 42, 64, 65, 67, 68, 69, 
	70, 77, 81, 83, 124, 9, 13, 34, 
	34, 10, 32, 9, 13, 10, 32, 34, 
	9, 13, 10, 32, 34, 9, 13, 10, 
	32, 34, 9, 13, 10, 32, 34, 9, 
	13, 10, 32, 34, 9, 13, 10, 32, 
	9, 13, 10, 32, 9, 13, 10, 13, 
	10, 95, 70, 69, 65, 84, 85, 82, 
	69, 95, 69, 78, 68, 95, 37, 32, 
	10, 10, 13, 13, 32, 64, 9, 10, 
	9, 10, 13, 32, 64, 11, 12, 10, 
	32, 64, 9, 13, 108, 108, 111, 114, 
	97, 111, 110, 116, 101, 115, 116, 111, 
	58, 10, 10, 10, 32, 35, 37, 42, 
	64, 65, 68, 69, 70, 77, 81, 83, 
	9, 13, 10, 95, 10, 70, 10, 69, 
	10, 65, 10, 84, 10, 85, 10, 82, 
	10, 69, 10, 95, 10, 69, 10, 78, 
	10, 68, 10, 95, 10, 37, 10, 32, 
	10, 32, 34, 35, 37, 42, 64, 65, 
	67, 68, 69, 70, 77, 81, 83, 124, 
	9, 13, 97, 116, 111, 32, 115, 101, 
	109, 112, 105, 58, 10, 10, 10, 32, 
	35, 70, 124, 9, 13, 10, 117, 10, 
	110, 10, 122, 10, 105, 10, 111, 10, 
	110, 10, 97, 10, 108, 10, 105, 10, 
	116, -61, 10, -96, 10, 10, 58, 117, 
	110, 122, 105, 111, 110, 97, 108, 105, 
	116, -61, -96, 58, 10, 10, 10, 32, 
	35, 37, 64, 67, 69, 70, 83, 9, 
	13, 10, 95, 10, 70, 10, 69, 10, 
	65, 10, 84, 10, 85, 10, 82, 10, 
	69, 10, 95, 10, 69, 10, 78, 10, 
	68, 10, 95, 10, 37, 10, 111, 10, 
	110, 10, 116, 10, 101, 10, 115, 10, 
	116, 10, 111, 10, 58, 10, 115, 10, 
	101, 10, 109, 10, 112, 10, 105, 10, 
	117, 10, 110, 10, 122, 10, 105, 10, 
	111, 10, 110, 10, 97, 10, 108, 10, 
	105, 10, 116, -61, 10, -96, 10, 10, 
	99, 10, 101, 104, 10, 110, 10, 97, 
	10, 114, 10, 105, 10, 101, 10, 109, 
	10, 97, 10, 32, 10, 100, 10, 101, 
	10, 108, 10, 108, 10, 111, 10, 32, 
	10, 115, 10, 99, 10, 101, 117, 97, 
	110, 100, 99, 101, 104, 110, 97, 114, 
	105, 111, 58, 10, 10, 10, 32, 35, 
	37, 42, 64, 65, 67, 68, 69, 70, 
	77, 81, 83, 9, 13, 10, 95, 10, 
	70, 10, 69, 10, 65, 10, 84, 10, 
	85, 10, 82, 10, 69, 10, 95, 10, 
	69, 10, 78, 10, 68, 10, 95, 10, 
	37, 10, 32, 10, 108, 10, 108, 10, 
	111, 10, 114, 10, 97, 10, 111, 10, 
	110, 10, 116, 10, 101, 10, 115, 10, 
	116, 10, 111, 10, 58, 10, 97, 10, 
	116, 10, 111, 10, 117, 10, 110, 10, 
	122, 10, 105, 10, 111, 10, 110, 10, 
	97, 10, 108, 10, 105, 10, 116, -61, 
	10, -96, 10, 10, 117, 10, 97, 10, 
	110, 10, 100, 10, 99, 10, 101, 104, 
	10, 110, 10, 97, 10, 114, 10, 105, 
	10, 101, 10, 109, 10, 97, 10, 32, 
	10, 100, 10, 101, 10, 108, 10, 108, 
	10, 111, 10, 32, 10, 115, 10, 99, 
	10, 101, 101, 109, 97, 32, 100, 101, 
	108, 108, 111, 32, 115, 99, 101, 110, 
	97, 114, 105, 111, 58, 10, 10, 10, 
	32, 35, 37, 42, 64, 65, 68, 69, 
	70, 77, 81, 83, 9, 13, 10, 95, 
	10, 70, 10, 69, 10, 65, 10, 84, 
	10, 85, 10, 82, 10, 69, 10, 95, 
	10, 69, 10, 78, 10, 68, 10, 95, 
	10, 37, 10, 32, 10, 108, 10, 108, 
	10, 111, 10, 114, 10, 97, 10, 97, 
	10, 116, 10, 111, 10, 117, 10, 110, 
	10, 122, 10, 105, 10, 111, 10, 110, 
	10, 97, 10, 108, 10, 105, 10, 116, 
	-61, 10, -96, 10, 10, 58, 10, 117, 
	10, 97, 10, 110, 10, 100, 10, 99, 
	10, 101, 10, 110, 10, 97, 10, 114, 
	10, 105, 10, 111, 32, 124, 9, 13, 
	10, 32, 92, 124, 9, 13, 10, 92, 
	124, 10, 92, 10, 32, 92, 124, 9, 
	13, 10, 32, 34, 35, 37, 42, 64, 
	65, 67, 68, 69, 70, 77, 81, 83, 
	124, 9, 13, 10, 108, 10, 108, 10, 
	111, 10, 114, 10, 97, 10, 97, 10, 
	116, 10, 111, 10, 117, 10, 110, 10, 
	122, 10, 105, 10, 111, 10, 110, 10, 
	97, 10, 108, 10, 105, 10, 116, -61, 
	10, -96, 10, 10, 58, 10, 117, 10, 
	97, 10, 110, 10, 100, 10, 99, 10, 
	101, 104, 10, 110, 10, 97, 10, 114, 
	10, 105, 10, 111, 10, 101, 10, 109, 
	10, 97, 10, 32, 10, 100, 10, 101, 
	10, 108, 10, 108, 10, 111, 10, 32, 
	10, 115, 10, 99, 10, 101, 0
};

static const char _lexer_single_lengths[] = {
	0, 17, 1, 1, 16, 1, 1, 2, 
	3, 3, 3, 3, 3, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 2, 3, 5, 3, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 13, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 16, 1, 1, 1, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	5, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 9, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	1, 1, 1, 1, 1, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 14, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 13, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 4, 
	3, 2, 4, 16, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 0
};

static const char _lexer_range_lengths[] = {
	0, 1, 0, 0, 1, 0, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 1, 
	0, 0, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0
};

static const short _lexer_index_offsets[] = {
	0, 0, 19, 21, 23, 41, 43, 45, 
	49, 54, 59, 64, 69, 74, 78, 82, 
	85, 87, 89, 91, 93, 95, 97, 99, 
	101, 103, 105, 107, 109, 111, 113, 115, 
	117, 119, 122, 127, 134, 139, 141, 143, 
	145, 147, 149, 151, 153, 155, 157, 159, 
	161, 163, 165, 167, 169, 184, 187, 190, 
	193, 196, 199, 202, 205, 208, 211, 214, 
	217, 220, 223, 226, 229, 247, 249, 251, 
	253, 256, 258, 260, 262, 264, 266, 268, 
	270, 277, 280, 283, 286, 289, 292, 295, 
	298, 301, 304, 307, 310, 313, 316, 318, 
	320, 322, 324, 326, 328, 330, 332, 334, 
	336, 338, 340, 342, 344, 346, 357, 360, 
	363, 366, 369, 372, 375, 378, 381, 384, 
	387, 390, 393, 396, 399, 402, 405, 408, 
	411, 414, 417, 420, 423, 426, 429, 432, 
	435, 438, 441, 444, 447, 450, 453, 456, 
	459, 462, 465, 468, 471, 474, 477, 481, 
	484, 487, 490, 493, 496, 499, 502, 505, 
	508, 511, 514, 517, 520, 523, 526, 529, 
	532, 534, 536, 538, 540, 542, 545, 547, 
	549, 551, 553, 555, 557, 559, 561, 577, 
	580, 583, 586, 589, 592, 595, 598, 601, 
	604, 607, 610, 613, 616, 619, 622, 625, 
	628, 631, 634, 637, 640, 643, 646, 649, 
	652, 655, 658, 661, 664, 667, 670, 673, 
	676, 679, 682, 685, 688, 691, 694, 697, 
	700, 703, 706, 709, 712, 715, 718, 721, 
	725, 728, 731, 734, 737, 740, 743, 746, 
	749, 752, 755, 758, 761, 764, 767, 770, 
	773, 776, 778, 780, 782, 784, 786, 788, 
	790, 792, 794, 796, 798, 800, 802, 804, 
	806, 808, 810, 812, 814, 816, 818, 833, 
	836, 839, 842, 845, 848, 851, 854, 857, 
	860, 863, 866, 869, 872, 875, 878, 881, 
	884, 887, 890, 893, 896, 899, 902, 905, 
	908, 911, 914, 917, 920, 923, 926, 929, 
	932, 935, 938, 941, 944, 947, 950, 953, 
	956, 959, 962, 965, 968, 971, 974, 978, 
	984, 988, 991, 997, 1015, 1018, 1021, 1024, 
	1027, 1030, 1033, 1036, 1039, 1042, 1045, 1048, 
	1051, 1054, 1057, 1060, 1063, 1066, 1069, 1072, 
	1075, 1078, 1081, 1084, 1087, 1090, 1093, 1097, 
	1100, 1103, 1106, 1109, 1112, 1115, 1118, 1121, 
	1124, 1127, 1130, 1133, 1136, 1139, 1142, 1145, 
	1148, 1151
};

static const short _lexer_trans_targs[] = {
	2, 4, 4, 5, 15, 17, 31, 34, 
	37, 42, 69, 72, 94, 41, 168, 172, 
	318, 4, 0, 3, 0, 4, 0, 4, 
	4, 5, 15, 17, 31, 34, 37, 42, 
	69, 72, 94, 41, 168, 172, 318, 4, 
	0, 6, 0, 7, 0, 8, 7, 7, 
	0, 9, 9, 10, 9, 9, 9, 9, 
	10, 9, 9, 9, 9, 11, 9, 9, 
	9, 9, 12, 9, 9, 4, 13, 14, 
	13, 0, 4, 13, 13, 0, 4, 13, 
	13, 0, 4, 16, 15, 4, 0, 18, 
	0, 19, 0, 20, 0, 21, 0, 22, 
	0, 23, 0, 24, 0, 25, 0, 26, 
	0, 27, 0, 28, 0, 29, 0, 30, 
	0, 369, 0, 32, 0, 0, 33, 4, 
	16, 33, 0, 0, 0, 0, 35, 36, 
	4, 36, 36, 34, 35, 35, 4, 36, 
	34, 36, 0, 38, 0, 39, 0, 40, 
	0, 41, 0, 31, 0, 43, 0, 44, 
	0, 45, 0, 46, 0, 47, 0, 48, 
	0, 49, 0, 50, 0, 52, 51, 52, 
	51, 52, 52, 4, 53, 67, 4, 324, 
	329, 67, 332, 328, 345, 349, 52, 51, 
	52, 54, 51, 52, 55, 51, 52, 56, 
	51, 52, 57, 51, 52, 58, 51, 52, 
	59, 51, 52, 60, 51, 52, 61, 51, 
	52, 62, 51, 52, 63, 51, 52, 64, 
	51, 52, 65, 51, 52, 66, 51, 52, 
	4, 51, 52, 68, 51, 4, 4, 5, 
	15, 17, 31, 34, 37, 42, 69, 72, 
	94, 41, 168, 172, 318, 4, 0, 70, 
	0, 71, 0, 31, 0, 32, 73, 0, 
	74, 0, 75, 0, 76, 0, 77, 0, 
	78, 0, 80, 79, 80, 79, 80, 80, 
	4, 81, 4, 80, 79, 80, 82, 79, 
	80, 83, 79, 80, 84, 79, 80, 85, 
	79, 80, 86, 79, 80, 87, 79, 80, 
	88, 79, 80, 89, 79, 80, 90, 79, 
	80, 91, 79, 92, 80, 79, 93, 80, 
	79, 80, 68, 79, 95, 0, 96, 0, 
	97, 0, 98, 0, 99, 0, 100, 0, 
	101, 0, 102, 0, 103, 0, 104, 0, 
	105, 0, 106, 0, 107, 0, 109, 108, 
	109, 108, 109, 109, 4, 110, 4, 124, 
	132, 137, 149, 109, 108, 109, 111, 108, 
	109, 112, 108, 109, 113, 108, 109, 114, 
	108, 109, 115, 108, 109, 116, 108, 109, 
	117, 108, 109, 118, 108, 109, 119, 108, 
	109, 120, 108, 109, 121, 108, 109, 122, 
	108, 109, 123, 108, 109, 4, 108, 109, 
	125, 108, 109, 126, 108, 109, 127, 108, 
	109, 128, 108, 109, 129, 108, 109, 130, 
	108, 109, 131, 108, 109, 68, 108, 109, 
	133, 108, 109, 134, 108, 109, 135, 108, 
	109, 136, 108, 109, 131, 108, 109, 138, 
	108, 109, 139, 108, 109, 140, 108, 109, 
	141, 108, 109, 142, 108, 109, 143, 108, 
	109, 144, 108, 109, 145, 108, 109, 146, 
	108, 109, 147, 108, 148, 109, 108, 131, 
	109, 108, 109, 150, 108, 109, 151, 155, 
	108, 109, 152, 108, 109, 153, 108, 109, 
	154, 108, 109, 130, 108, 109, 156, 108, 
	109, 157, 108, 109, 158, 108, 109, 159, 
	108, 109, 160, 108, 109, 161, 108, 109, 
	162, 108, 109, 163, 108, 109, 164, 108, 
	109, 165, 108, 109, 166, 108, 109, 167, 
	108, 109, 151, 108, 169, 0, 170, 0, 
	171, 0, 71, 0, 173, 0, 174, 249, 
	0, 175, 0, 176, 0, 177, 0, 178, 
	0, 179, 0, 180, 0, 182, 181, 182, 
	181, 182, 182, 4, 183, 197, 4, 198, 
	203, 211, 197, 214, 202, 226, 230, 182, 
	181, 182, 184, 181, 182, 185, 181, 182, 
	186, 181, 182, 187, 181, 182, 188, 181, 
	182, 189, 181, 182, 190, 181, 182, 191, 
	181, 182, 192, 181, 182, 193, 181, 182, 
	194, 181, 182, 195, 181, 182, 196, 181, 
	182, 4, 181, 182, 68, 181, 182, 199, 
	181, 182, 200, 181, 182, 201, 181, 182, 
	202, 181, 182, 197, 181, 182, 204, 181, 
	182, 205, 181, 182, 206, 181, 182, 207, 
	181, 182, 208, 181, 182, 209, 181, 182, 
	210, 181, 182, 68, 181, 182, 212, 181, 
	182, 213, 181, 182, 197, 181, 182, 215, 
	181, 182, 216, 181, 182, 217, 181, 182, 
	218, 181, 182, 219, 181, 182, 220, 181, 
	182, 221, 181, 182, 222, 181, 182, 223, 
	181, 182, 224, 181, 225, 182, 181, 210, 
	182, 181, 182, 227, 181, 182, 228, 181, 
	182, 229, 181, 182, 213, 181, 182, 231, 
	181, 182, 232, 236, 181, 182, 233, 181, 
	182, 234, 181, 182, 235, 181, 182, 209, 
	181, 182, 237, 181, 182, 238, 181, 182, 
	239, 181, 182, 240, 181, 182, 241, 181, 
	182, 242, 181, 182, 243, 181, 182, 244, 
	181, 182, 245, 181, 182, 246, 181, 182, 
	247, 181, 182, 248, 181, 182, 232, 181, 
	250, 0, 251, 0, 252, 0, 253, 0, 
	254, 0, 255, 0, 256, 0, 257, 0, 
	258, 0, 259, 0, 260, 0, 261, 0, 
	262, 0, 263, 0, 264, 0, 265, 0, 
	266, 0, 267, 0, 268, 0, 270, 269, 
	270, 269, 270, 270, 4, 271, 285, 4, 
	286, 291, 285, 294, 290, 307, 311, 270, 
	269, 270, 272, 269, 270, 273, 269, 270, 
	274, 269, 270, 275, 269, 270, 276, 269, 
	270, 277, 269, 270, 278, 269, 270, 279, 
	269, 270, 280, 269, 270, 281, 269, 270, 
	282, 269, 270, 283, 269, 270, 284, 269, 
	270, 4, 269, 270, 68, 269, 270, 287, 
	269, 270, 288, 269, 270, 289, 269, 270, 
	290, 269, 270, 285, 269, 270, 292, 269, 
	270, 293, 269, 270, 285, 269, 270, 295, 
	269, 270, 296, 269, 270, 297, 269, 270, 
	298, 269, 270, 299, 269, 270, 300, 269, 
	270, 301, 269, 270, 302, 269, 270, 303, 
	269, 270, 304, 269, 305, 270, 269, 306, 
	270, 269, 270, 68, 269, 270, 308, 269, 
	270, 309, 269, 270, 310, 269, 270, 293, 
	269, 270, 312, 269, 270, 313, 269, 270, 
	314, 269, 270, 315, 269, 270, 316, 269, 
	270, 317, 269, 270, 306, 269, 318, 319, 
	318, 0, 323, 322, 321, 319, 322, 320, 
	0, 321, 319, 320, 0, 321, 320, 323, 
	322, 321, 319, 322, 320, 323, 323, 5, 
	15, 17, 31, 34, 37, 42, 69, 72, 
	94, 41, 168, 172, 318, 323, 0, 52, 
	325, 51, 52, 326, 51, 52, 327, 51, 
	52, 328, 51, 52, 67, 51, 52, 330, 
	51, 52, 331, 51, 52, 67, 51, 52, 
	333, 51, 52, 334, 51, 52, 335, 51, 
	52, 336, 51, 52, 337, 51, 52, 338, 
	51, 52, 339, 51, 52, 340, 51, 52, 
	341, 51, 52, 342, 51, 343, 52, 51, 
	344, 52, 51, 52, 68, 51, 52, 346, 
	51, 52, 347, 51, 52, 348, 51, 52, 
	331, 51, 52, 350, 51, 52, 351, 356, 
	51, 52, 352, 51, 52, 353, 51, 52, 
	354, 51, 52, 355, 51, 52, 344, 51, 
	52, 357, 51, 52, 358, 51, 52, 359, 
	51, 52, 360, 51, 52, 361, 51, 52, 
	362, 51, 52, 363, 51, 52, 364, 51, 
	52, 365, 51, 52, 366, 51, 52, 367, 
	51, 52, 368, 51, 52, 351, 51, 0, 
	0
};

static const char _lexer_trans_actions[] = {
	0, 47, 0, 5, 1, 0, 25, 1, 
	25, 25, 25, 25, 25, 25, 25, 25, 
	31, 0, 39, 0, 39, 0, 39, 47, 
	0, 5, 1, 0, 25, 1, 25, 25, 
	25, 25, 25, 25, 25, 25, 31, 0, 
	39, 0, 39, 0, 39, 47, 0, 0, 
	39, 119, 41, 41, 41, 3, 111, 29, 
	29, 29, 0, 111, 29, 29, 29, 0, 
	111, 29, 0, 29, 0, 95, 7, 0, 
	7, 39, 47, 0, 0, 39, 95, 7, 
	7, 39, 103, 21, 0, 47, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 39, 50, 99, 
	19, 0, 39, 39, 39, 39, 0, 23, 
	107, 23, 23, 44, 23, 0, 47, 0, 
	1, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 124, 50, 47, 
	0, 47, 0, 65, 29, 77, 65, 77, 
	77, 77, 77, 77, 77, 77, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	11, 0, 47, 11, 0, 115, 27, 53, 
	50, 27, 56, 50, 56, 56, 56, 56, 
	56, 56, 56, 56, 59, 27, 39, 0, 
	39, 0, 39, 0, 39, 0, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 124, 50, 47, 0, 47, 0, 
	74, 77, 74, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 0, 47, 0, 0, 47, 
	0, 47, 17, 0, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 124, 50, 
	47, 0, 47, 0, 62, 29, 62, 77, 
	77, 77, 77, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 9, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 9, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 47, 0, 0, 47, 0, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 124, 50, 47, 
	0, 47, 0, 68, 29, 77, 68, 77, 
	77, 77, 77, 77, 77, 77, 77, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 13, 0, 47, 13, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 13, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 124, 50, 
	47, 0, 47, 0, 71, 29, 77, 71, 
	77, 77, 77, 77, 77, 77, 77, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 15, 0, 47, 15, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 47, 15, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 0, 
	0, 39, 47, 33, 33, 80, 33, 33, 
	39, 0, 35, 0, 39, 0, 0, 47, 
	0, 0, 35, 0, 0, 47, 0, 86, 
	83, 37, 89, 83, 89, 89, 89, 89, 
	89, 89, 89, 89, 92, 0, 39, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 47, 0, 
	0, 47, 0, 47, 11, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 0, 
	0
};

static const char _lexer_eof_actions[] = {
	0, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39
};

static const int lexer_start = 1;
static const int lexer_first_final = 369;
static const int lexer_error = 0;

static const int lexer_en_main = 1;


#line 243 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"

static VALUE 
strip_i(VALUE str, VALUE ary)
{
  rb_funcall(str, rb_intern("strip!"), 0);
  rb_ary_push(ary, str);
  
  return Qnil;
}

static VALUE 
multiline_strip(VALUE text)
{
  VALUE map = rb_ary_new();
  VALUE split = rb_str_split(text, "\n");
  
  rb_iterate(rb_each, split, strip_i, map);
  
  return split;
}

static void 
store_kw_con(VALUE listener, const char * event_name, 
             const char * keyword_at, size_t keyword_length, 
             const char * at,         size_t length, 
             int current_line)
{
  VALUE con = Qnil, kw = Qnil;
  kw = ENCODED_STR_NEW(keyword_at, keyword_length);
  con = ENCODED_STR_NEW(at, length);
  rb_funcall(con, rb_intern("strip!"), 0);
  rb_funcall(listener, rb_intern(event_name), 3, kw, con, INT2FIX(current_line)); 
}

static void
store_multiline_kw_con(VALUE listener, const char * event_name,
                      const char * keyword_at, size_t keyword_length,
                      const char * at,         size_t length,
                      int current_line, int eol)
{
  VALUE con = Qnil, kw = Qnil, name = Qnil, desc = Qnil;

  kw = ENCODED_STR_NEW(keyword_at, keyword_length);
  con = ENCODED_STR_NEW(at, length);

  VALUE split = multiline_strip(con);
  
  name = rb_funcall(split, rb_intern("shift"), 0);
  desc = rb_ary_join(split, rb_str_new2( \
          eol == CRLF_FLAG ? CRLF : LF ));

  if( name == Qnil ) 
  {
    name = rb_str_new2("");
  }
  if( rb_funcall(desc, rb_intern("size"), 0) == 0) 
  {
    desc = rb_str_new2("");
  }
  rb_funcall(name, rb_intern("strip!"), 0);
  rb_funcall(desc, rb_intern("strip!"), 0);
  rb_funcall(listener, rb_intern(event_name), 4, kw, name, desc, INT2FIX(current_line)); 
}

static void 
store_attr(VALUE listener, const char * attr_type,
           const char * at, size_t length, 
           int line)
{
  VALUE val = ENCODED_STR_NEW(at, length);
  rb_funcall(listener, rb_intern(attr_type), 2, val, INT2FIX(line));
}

static void 
store_pystring_content(VALUE listener, 
          int start_col, 
          const char *at, size_t length, 
          int current_line)
{
  VALUE con = ENCODED_STR_NEW(at, length);
  // Gherkin will crash gracefully if the string representation of start_col pushes the pattern past 32 characters
  char pat[32]; 
  snprintf(pat, 32, "^[\t ]{0,%d}", start_col); 
  VALUE re = rb_reg_regcomp(rb_str_new2(pat));
  VALUE re2 = rb_reg_regcomp(rb_str_new2("\r\\Z"));
  VALUE unescape_escaped_quotes = rb_reg_regcomp(rb_str_new2("\\\\\"\\\\\"\\\\\""));
  rb_funcall(con, rb_intern("gsub!"), 2, re, rb_str_new2(""));
  rb_funcall(con, rb_intern("sub!"), 2, re2, rb_str_new2(""));
  rb_funcall(con, rb_intern("gsub!"), 2, unescape_escaped_quotes, rb_str_new2("\"\"\""));
  rb_funcall(listener, rb_intern("py_string"), 2, con, INT2FIX(current_line));
}

static void 
raise_lexer_error(const char * at, int line)
{ 
  rb_raise(rb_eGherkinLexingError, "Lexing error on line %d: '%s'. See http://wiki.github.com/aslakhellesoy/gherkin/lexingerror for more information.", line, at);
}

static int 
count_char(char char_to_count, char *str) {

  int count = 0;
  int i = 0;
  while(str[i] != '\0') {
    if(str[i] == char_to_count) {
      count++;
    }
    i++;
  }
  return count;
}

static void lexer_init(lexer_state *lexer) {
  lexer->content_start = 0;
  lexer->content_end = 0;
  lexer->content_len = 0;
  lexer->mark = 0;
  lexer->keyword_start = 0;
  lexer->keyword_end = 0;
  lexer->next_keyword_start = 0;
  lexer->line_number = 1;
  lexer->last_newline = 0;
  lexer->final_newline = 0;
  lexer->start_col = 0;
  lexer->eol = LF_FLAG;
}

static VALUE CLexer_alloc(VALUE klass)
{
  VALUE obj;
  lexer_state *lxr = ALLOC(lexer_state);
  lexer_init(lxr);

  obj = Data_Wrap_Struct(klass, NULL, -1, lxr);

  return obj;
}

static VALUE CLexer_init(VALUE self, VALUE listener)
{
  rb_iv_set(self, "@listener", listener);
  
  lexer_state *lxr = NULL;
  DATA_GET(self, lexer_state, lxr);
  lexer_init(lxr);
  
  return self;
}

static VALUE CLexer_scan(VALUE self, VALUE input)
{
  VALUE listener = rb_iv_get(self, "@listener");

  lexer_state *lexer = NULL;
  DATA_GET(self, lexer_state, lexer);

  VALUE input_copy = rb_str_dup(input);

  rb_str_append(input_copy, rb_str_new2("\n%_FEATURE_END_%"));
  char *data = RSTRING_PTR(input_copy);
  size_t len = RSTRING_LEN(input_copy);
  
  if (count_char('\r', data) > (count_char('\n', data) / 2)) {
    lexer->eol = CRLF_FLAG;
  }
  
  if (len == 0) { 
    rb_raise(rb_eGherkinLexingError, "No content to lex.");
  } else {

    const char *p, *pe, *eof;
    int cs = 0;
    
    VALUE current_row = Qnil;

    p = data;
    pe = data + len;
    eof = pe;
    
    assert(*pe == '\0' && "pointer does not end on NULL");
    
    
#line 953 "ext/gherkin_lexer_it/gherkin_lexer_it.c"
	{
	cs = lexer_start;
	}

#line 425 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
    
#line 960 "ext/gherkin_lexer_it/gherkin_lexer_it.c"
	{
	int _klen;
	unsigned int _trans;
	const char *_acts;
	unsigned int _nacts;
	const char *_keys;

	if ( p == pe )
		goto _test_eof;
	if ( cs == 0 )
		goto _out;
_resume:
	_keys = _lexer_trans_keys + _lexer_key_offsets[cs];
	_trans = _lexer_index_offsets[cs];

	_klen = _lexer_single_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + _klen - 1;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + ((_upper-_lower) >> 1);
			if ( (*p) < *_mid )
				_upper = _mid - 1;
			else if ( (*p) > *_mid )
				_lower = _mid + 1;
			else {
				_trans += (_mid - _keys);
				goto _match;
			}
		}
		_keys += _klen;
		_trans += _klen;
	}

	_klen = _lexer_range_lengths[cs];
	if ( _klen > 0 ) {
		const char *_lower = _keys;
		const char *_mid;
		const char *_upper = _keys + (_klen<<1) - 2;
		while (1) {
			if ( _upper < _lower )
				break;

			_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( (*p) < _mid[0] )
				_upper = _mid - 2;
			else if ( (*p) > _mid[1] )
				_lower = _mid + 2;
			else {
				_trans += ((_mid - _keys)>>1);
				goto _match;
			}
		}
		_trans += _klen;
	}

_match:
	cs = _lexer_trans_targs[_trans];

	if ( _lexer_trans_actions[_trans] == 0 )
		goto _again;

	_acts = _lexer_actions + _lexer_trans_actions[_trans];
	_nacts = (unsigned int) *_acts++;
	while ( _nacts-- > 0 )
	{
		switch ( *_acts++ )
		{
	case 0:
#line 86 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
		MARK(content_start, p);
    lexer->current_line = lexer->line_number;
  }
	break;
	case 1:
#line 91 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    MARK(content_start, p);
  }
	break;
	case 2:
#line 95 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    lexer->current_line = lexer->line_number;
    lexer->start_col = p - data - lexer->last_newline;
  }
	break;
	case 3:
#line 100 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    int len = LEN(content_start, PTR_TO(final_newline));

    if (len < 0) len = 0;

    store_pystring_content(listener, lexer->start_col, PTR_TO(content_start), len, lexer->current_line);
  }
	break;
	case 4:
#line 108 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_KW_END_CON(feature);
  }
	break;
	case 5:
#line 112 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_KW_END_CON(background);
  }
	break;
	case 6:
#line 116 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_KW_END_CON(scenario);
  }
	break;
	case 7:
#line 120 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_KW_END_CON(scenario_outline);
  }
	break;
	case 8:
#line 124 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_KW_END_CON(examples);
  }
	break;
	case 9:
#line 128 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    store_kw_con(listener, "step",
      PTR_TO(keyword_start), LEN(keyword_start, PTR_TO(keyword_end)),
      PTR_TO(content_start), LEN(content_start, p), 
      lexer->current_line);
  }
	break;
	case 10:
#line 135 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_ATTR(comment);
    lexer->mark = 0;
  }
	break;
	case 11:
#line 140 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    STORE_ATTR(tag);
    lexer->mark = 0;
  }
	break;
	case 12:
#line 145 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    lexer->line_number += 1;
    MARK(final_newline, p);
  }
	break;
	case 13:
#line 150 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    MARK(last_newline, p + 1);
  }
	break;
	case 14:
#line 154 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    if (lexer->mark == 0) {
      MARK(mark, p);
    }
  }
	break;
	case 15:
#line 160 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    MARK(keyword_end, p);
    MARK(keyword_start, PTR_TO(mark));
    MARK(content_start, p + 1);
    lexer->mark = 0;
  }
	break;
	case 16:
#line 167 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    MARK(content_end, p);
  }
	break;
	case 17:
#line 171 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    p = p - 1;
    lexer->current_line = lexer->line_number;
    current_row = rb_ary_new();
  }
	break;
	case 18:
#line 177 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
		MARK(content_start, p);
  }
	break;
	case 19:
#line 181 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    VALUE con = ENCODED_STR_NEW(PTR_TO(content_start), LEN(content_start, p));
    rb_funcall(con, rb_intern("strip!"), 0);
    VALUE re_pipe      = rb_reg_regcomp(rb_str_new2("\\\\\\|"));
    VALUE re_backslash = rb_reg_regcomp(rb_str_new2("\\\\\\\\"));
    rb_funcall(con, rb_intern("gsub!"), 2, re_pipe,      rb_str_new2("|"));
    rb_funcall(con, rb_intern("gsub!"), 2, re_backslash, rb_str_new2("\\"));

    rb_ary_push(current_row, con);
  }
	break;
	case 20:
#line 192 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    rb_funcall(listener, rb_intern("row"), 2, current_row, INT2FIX(lexer->current_line));
  }
	break;
	case 21:
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    if (cs < lexer_first_final) {
      if (raise_lexer_error != NULL) {
        size_t count = 0;
        int newstr_count = 0;
        size_t len;
        const char *buff;
        if (lexer->last_newline != 0) {
          len = LEN(last_newline, eof);
          buff = PTR_TO(last_newline);
        } else {
          len = strlen(data);
          buff = data;
        }

        char newstr[len]; 

        for (count = 0; count < len; count++) {
          if(buff[count] == 10) {
            newstr[newstr_count] = '\0'; // terminate new string at first newline found
            break;
          } else {
            if (buff[count] == '%') {
              newstr[newstr_count++] = buff[count];
              newstr[newstr_count] = buff[count];
            } else {
              newstr[newstr_count] = buff[count];
            }
          }
          newstr_count++;
        }

        int line = lexer->line_number;
        lexer_init(lexer); // Re-initialize so we can scan again with the same lexer
        raise_lexer_error(newstr, line);
      }
    } else {
      rb_funcall(listener, rb_intern("eof"), 0);
    }
  }
	break;
#line 1228 "ext/gherkin_lexer_it/gherkin_lexer_it.c"
		}
	}

_again:
	if ( cs == 0 )
		goto _out;
	if ( ++p != pe )
		goto _resume;
	_test_eof: {}
	if ( p == eof )
	{
	const char *__acts = _lexer_actions + _lexer_eof_actions[cs];
	unsigned int __nacts = (unsigned int) *__acts++;
	while ( __nacts-- > 0 ) {
		switch ( *__acts++ ) {
	case 21:
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"
	{
    if (cs < lexer_first_final) {
      if (raise_lexer_error != NULL) {
        size_t count = 0;
        int newstr_count = 0;
        size_t len;
        const char *buff;
        if (lexer->last_newline != 0) {
          len = LEN(last_newline, eof);
          buff = PTR_TO(last_newline);
        } else {
          len = strlen(data);
          buff = data;
        }

        char newstr[len]; 

        for (count = 0; count < len; count++) {
          if(buff[count] == 10) {
            newstr[newstr_count] = '\0'; // terminate new string at first newline found
            break;
          } else {
            if (buff[count] == '%') {
              newstr[newstr_count++] = buff[count];
              newstr[newstr_count] = buff[count];
            } else {
              newstr[newstr_count] = buff[count];
            }
          }
          newstr_count++;
        }

        int line = lexer->line_number;
        lexer_init(lexer); // Re-initialize so we can scan again with the same lexer
        raise_lexer_error(newstr, line);
      }
    } else {
      rb_funcall(listener, rb_intern("eof"), 0);
    }
  }
	break;
#line 1287 "ext/gherkin_lexer_it/gherkin_lexer_it.c"
		}
	}
	}

	_out: {}
	}

#line 426 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/it.c.rl"

    assert(p <= pe && "data overflow after parsing execute");
    assert(lexer->content_start <= len && "content starts after data end");
    assert(lexer->mark < len && "mark is after data end");
    
    // Reset lexer by re-initializing the whole thing
    lexer_init(lexer);

    if (cs == lexer_error) {
      rb_raise(rb_eGherkinLexingError, "Invalid format, lexing fails.");
    } else {
      return Qtrue;
    }
  }
}

void Init_gherkin_lexer_it()
{
  mGherkin = rb_define_module("Gherkin");
  rb_eGherkinLexingError = rb_const_get(mGherkin, rb_intern("LexingError"));

  mCLexer = rb_define_module_under(mGherkin, "CLexer");
  cI18nLexer = rb_define_class_under(mCLexer, "It", rb_cObject);
  rb_define_alloc_func(cI18nLexer, CLexer_alloc);
  rb_define_method(cI18nLexer, "initialize", CLexer_init, 1);
  rb_define_method(cI18nLexer, "scan", CLexer_scan, 1);
}

