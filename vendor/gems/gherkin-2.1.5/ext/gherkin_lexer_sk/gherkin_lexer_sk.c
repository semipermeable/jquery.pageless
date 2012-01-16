
#line 1 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
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


#line 239 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"


/** Data **/

#line 92 "ext/gherkin_lexer_sk/gherkin_lexer_sk.c"
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
	0, 0, 17, 18, 19, 35, 36, 37, 
	41, 46, 51, 56, 61, 65, 69, 71, 
	72, 73, 74, 75, 76, 77, 78, 79, 
	80, 81, 82, 83, 84, 85, 86, 87, 
	88, 90, 95, 102, 107, 109, 110, 111, 
	112, 113, 114, 115, 116, 117, 118, 119, 
	120, 121, 122, 123, 124, 125, 126, 127, 
	128, 129, 130, 131, 144, 146, 148, 150, 
	152, 154, 156, 158, 160, 162, 164, 166, 
	168, 170, 172, 174, 190, 192, 195, 196, 
	197, 198, 199, 200, 201, 202, 203, 204, 
	205, 206, 216, 218, 220, 222, 224, 226, 
	228, 230, 232, 234, 236, 238, 240, 242, 
	244, 246, 248, 250, 252, 254, 256, 258, 
	260, 262, 264, 266, 268, 270, 272, 274, 
	276, 279, 282, 284, 286, 288, 290, 292, 
	294, 296, 298, 300, 302, 304, 306, 308, 
	310, 312, 314, 316, 318, 320, 322, 324, 
	326, 328, 330, 332, 333, 334, 335, 336, 
	337, 338, 339, 340, 341, 342, 343, 357, 
	359, 361, 363, 365, 367, 369, 371, 373, 
	375, 377, 379, 381, 383, 385, 387, 390, 
	392, 394, 396, 398, 400, 402, 404, 406, 
	408, 410, 412, 414, 416, 418, 420, 422, 
	424, 426, 428, 430, 432, 435, 437, 439, 
	441, 443, 445, 447, 449, 451, 453, 455, 
	457, 459, 461, 463, 465, 467, 469, 471, 
	473, 475, 476, 477, 478, 479, 480, 481, 
	482, 483, 484, 485, 492, 494, 496, 498, 
	500, 502, 504, 506, 508, 510, 512, 514, 
	515, 516, 517, 518, 519, 520, 521, 522, 
	523, 537, 539, 541, 543, 545, 547, 549, 
	551, 553, 555, 557, 559, 561, 563, 565, 
	567, 570, 572, 574, 576, 578, 580, 582, 
	584, 586, 588, 590, 592, 594, 596, 598, 
	600, 602, 604, 606, 608, 610, 612, 616, 
	618, 620, 622, 624, 626, 628, 630, 632, 
	634, 636, 638, 640, 642, 644, 646, 648, 
	650, 652, 654, 656, 658, 660, 662, 664, 
	665, 666, 670, 676, 679, 681, 687, 703, 
	706, 708, 710, 712, 714, 716, 719, 721, 
	723, 725, 727, 729, 731, 733, 735, 737, 
	739, 741, 743, 745, 747, 749, 751, 753, 
	755, 757, 759, 761
};

static const char _lexer_trans_keys[] = {
	-17, 10, 32, 34, 35, 37, 42, 64, 
	65, 75, 78, 80, 83, 84, 124, 9, 
	13, -69, -65, 10, 32, 34, 35, 37, 
	42, 64, 65, 75, 78, 80, 83, 84, 
	124, 9, 13, 34, 34, 10, 32, 9, 
	13, 10, 32, 34, 9, 13, 10, 32, 
	34, 9, 13, 10, 32, 34, 9, 13, 
	10, 32, 34, 9, 13, 10, 32, 9, 
	13, 10, 32, 9, 13, 10, 13, 10, 
	95, 70, 69, 65, 84, 85, 82, 69, 
	95, 69, 78, 68, 95, 37, 32, 10, 
	10, 13, 13, 32, 64, 9, 10, 9, 
	10, 13, 32, 64, 11, 12, 10, 32, 
	64, 9, 13, 32, 108, 101, 101, -60, 
	-113, -61, -95, -60, -115, 114, 116, 32, 
	83, 99, 101, 110, -61, -95, 114, 117, 
	58, 10, 10, 10, 32, 35, 37, 42, 
	64, 65, 75, 80, 83, 84, 9, 13, 
	10, 95, 10, 70, 10, 69, 10, 65, 
	10, 84, 10, 85, 10, 82, 10, 69, 
	10, 95, 10, 69, 10, 78, 10, 68, 
	10, 95, 10, 37, 10, 32, 10, 32, 
	34, 35, 37, 42, 64, 65, 75, 78, 
	80, 83, 84, 124, 9, 13, 111, 114, 
	-59, 107, 122, -66, 105, 97, 100, 97, 
	118, 107, 97, 58, 10, 10, 10, 32, 
	35, 37, 64, 78, 80, 83, 9, 13, 
	10, 95, 10, 70, 10, 69, 10, 65, 
	10, 84, 10, 85, 10, 82, 10, 69, 
	10, 95, 10, 69, 10, 78, 10, 68, 
	10, 95, 10, 37, -61, 10, -95, 10, 
	-60, 10, -115, 10, 10, 114, 10, 116, 
	10, 32, 10, 83, 10, 99, 10, 101, 
	10, 110, -61, 10, -95, 10, 10, 114, 
	10, 117, 10, 58, 10, 111, 114, -59, 
	10, 122, -66, 10, 10, 105, 10, 97, 
	10, 100, 10, 97, 10, 118, 10, 107, 
	10, 97, 10, 97, 10, 100, 10, 105, 
	10, 101, -61, 10, -83, 10, 10, 107, 
	10, 108, 10, 97, 10, 100, 10, 121, 
	10, 99, 10, 101, 10, 110, -61, 10, 
	-95, 10, 10, 114, 105, 97, -60, -66, 
	97, 100, 105, 101, 58, 10, 10, 10, 
	32, 35, 37, 42, 64, 65, 75, 78, 
	80, 83, 84, 9, 13, 10, 95, 10, 
	70, 10, 69, 10, 65, 10, 84, 10, 
	85, 10, 82, 10, 69, 10, 95, 10, 
	69, 10, 78, 10, 68, 10, 95, 10, 
	37, 10, 32, 10, 32, 108, 10, 101, 
	10, 101, -60, 10, -113, 10, -61, 10, 
	-95, 10, -60, 10, -115, 10, 10, 114, 
	10, 116, 10, 32, 10, 83, 10, 99, 
	10, 101, 10, 110, -61, 10, -95, 10, 
	10, 114, 10, 117, 10, 58, 10, 111, 
	-59, 10, 107, -66, 10, 10, 105, 10, 
	97, 10, 100, 10, 97, 10, 118, 10, 
	107, 10, 97, 10, 105, 10, 97, -60, 
	10, -66, 10, 10, 99, 10, 101, 10, 
	110, -61, 10, -95, 10, 10, 114, 10, 
	97, 10, 107, -61, -83, 107, 108, 97, 
	100, 121, 58, 10, 10, 10, 32, 35, 
	80, 124, 9, 13, 10, 111, -59, 10, 
	-66, 10, 10, 105, 10, 97, 10, 100, 
	10, 97, 10, 118, 10, 107, 10, 97, 
	10, 58, 99, 101, 110, -61, -95, 114, 
	58, 10, 10, 10, 32, 35, 37, 42, 
	64, 65, 75, 78, 80, 83, 84, 9, 
	13, 10, 95, 10, 70, 10, 69, 10, 
	65, 10, 84, 10, 85, 10, 82, 10, 
	69, 10, 95, 10, 69, 10, 78, 10, 
	68, 10, 95, 10, 37, 10, 32, 10, 
	32, 108, 10, 101, 10, 101, -60, 10, 
	-113, 10, -61, 10, -95, 10, -60, 10, 
	-115, 10, 10, 114, 10, 116, 10, 32, 
	10, 83, 10, 99, 10, 101, 10, 110, 
	-61, 10, -95, 10, 10, 114, 10, 117, 
	10, 58, 10, 111, -59, 10, 107, 122, 
	-66, 10, 10, 105, 10, 97, 10, 100, 
	10, 97, 10, 118, 10, 107, 10, 97, 
	10, 105, 10, 97, -60, 10, -66, 10, 
	10, 97, 10, 100, 10, 105, 10, 101, 
	10, 99, 10, 101, 10, 110, -61, 10, 
	-95, 10, 10, 114, 10, 97, 10, 107, 
	97, 107, 32, 124, 9, 13, 10, 32, 
	92, 124, 9, 13, 10, 92, 124, 10, 
	92, 10, 32, 92, 124, 9, 13, 10, 
	32, 34, 35, 37, 42, 64, 65, 75, 
	78, 80, 83, 84, 124, 9, 13, 10, 
	32, 108, 10, 101, 10, 101, -60, 10, 
	-113, 10, 10, 111, -59, 10, 107, -66, 
	10, 10, 105, 10, 97, 10, 100, 10, 
	97, 10, 118, 10, 107, 10, 97, 10, 
	58, 10, 105, 10, 97, -60, 10, -66, 
	10, 10, 99, 10, 101, 10, 110, -61, 
	10, -95, 10, 10, 114, 10, 97, 10, 
	107, 0
};

static const char _lexer_single_lengths[] = {
	0, 15, 1, 1, 14, 1, 1, 2, 
	3, 3, 3, 3, 2, 2, 2, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	2, 3, 5, 3, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 11, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 14, 2, 3, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 8, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	3, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 12, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 3, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 5, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	12, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	3, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 4, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 1, 
	1, 2, 4, 3, 2, 4, 14, 3, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 0
};

static const char _lexer_range_lengths[] = {
	0, 1, 0, 0, 1, 0, 0, 1, 
	1, 1, 1, 1, 1, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 0, 0, 0, 0, 
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
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 1, 0, 0, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0
};

static const short _lexer_index_offsets[] = {
	0, 0, 17, 19, 21, 37, 39, 41, 
	45, 50, 55, 60, 65, 69, 73, 76, 
	78, 80, 82, 84, 86, 88, 90, 92, 
	94, 96, 98, 100, 102, 104, 106, 108, 
	110, 113, 118, 125, 130, 133, 135, 137, 
	139, 141, 143, 145, 147, 149, 151, 153, 
	155, 157, 159, 161, 163, 165, 167, 169, 
	171, 173, 175, 177, 190, 193, 196, 199, 
	202, 205, 208, 211, 214, 217, 220, 223, 
	226, 229, 232, 235, 251, 254, 258, 260, 
	262, 264, 266, 268, 270, 272, 274, 276, 
	278, 280, 290, 293, 296, 299, 302, 305, 
	308, 311, 314, 317, 320, 323, 326, 329, 
	332, 335, 338, 341, 344, 347, 350, 353, 
	356, 359, 362, 365, 368, 371, 374, 377, 
	380, 384, 388, 391, 394, 397, 400, 403, 
	406, 409, 412, 415, 418, 421, 424, 427, 
	430, 433, 436, 439, 442, 445, 448, 451, 
	454, 457, 460, 463, 465, 467, 469, 471, 
	473, 475, 477, 479, 481, 483, 485, 499, 
	502, 505, 508, 511, 514, 517, 520, 523, 
	526, 529, 532, 535, 538, 541, 544, 548, 
	551, 554, 557, 560, 563, 566, 569, 572, 
	575, 578, 581, 584, 587, 590, 593, 596, 
	599, 602, 605, 608, 611, 615, 618, 621, 
	624, 627, 630, 633, 636, 639, 642, 645, 
	648, 651, 654, 657, 660, 663, 666, 669, 
	672, 675, 677, 679, 681, 683, 685, 687, 
	689, 691, 693, 695, 702, 705, 708, 711, 
	714, 717, 720, 723, 726, 729, 732, 735, 
	737, 739, 741, 743, 745, 747, 749, 751, 
	753, 767, 770, 773, 776, 779, 782, 785, 
	788, 791, 794, 797, 800, 803, 806, 809, 
	812, 816, 819, 822, 825, 828, 831, 834, 
	837, 840, 843, 846, 849, 852, 855, 858, 
	861, 864, 867, 870, 873, 876, 879, 884, 
	887, 890, 893, 896, 899, 902, 905, 908, 
	911, 914, 917, 920, 923, 926, 929, 932, 
	935, 938, 941, 944, 947, 950, 953, 956, 
	958, 960, 964, 970, 974, 977, 983, 999, 
	1003, 1006, 1009, 1012, 1015, 1018, 1022, 1025, 
	1028, 1031, 1034, 1037, 1040, 1043, 1046, 1049, 
	1052, 1055, 1058, 1061, 1064, 1067, 1070, 1073, 
	1076, 1079, 1082, 1085
};

static const short _lexer_trans_targs[] = {
	2, 4, 4, 5, 14, 16, 30, 33, 
	36, 38, 41, 76, 239, 311, 313, 4, 
	0, 3, 0, 4, 0, 4, 4, 5, 
	14, 16, 30, 33, 36, 38, 41, 76, 
	239, 311, 313, 4, 0, 6, 0, 7, 
	0, 8, 7, 7, 0, 9, 9, 10, 
	9, 9, 9, 9, 10, 9, 9, 9, 
	9, 11, 9, 9, 9, 9, 12, 9, 
	9, 4, 13, 13, 0, 4, 13, 13, 
	0, 4, 15, 14, 4, 0, 17, 0, 
	18, 0, 19, 0, 20, 0, 21, 0, 
	22, 0, 23, 0, 24, 0, 25, 0, 
	26, 0, 27, 0, 28, 0, 29, 0, 
	347, 0, 31, 0, 0, 32, 4, 15, 
	32, 0, 0, 0, 0, 34, 35, 4, 
	35, 35, 33, 34, 34, 4, 35, 33, 
	35, 0, 31, 37, 0, 30, 0, 39, 
	0, 40, 0, 30, 0, 42, 0, 43, 
	0, 44, 0, 45, 0, 46, 0, 47, 
	0, 48, 0, 49, 0, 50, 0, 51, 
	0, 52, 0, 53, 0, 54, 0, 55, 
	0, 56, 0, 57, 0, 59, 58, 59, 
	58, 59, 59, 4, 60, 74, 4, 319, 
	321, 324, 339, 345, 59, 58, 59, 61, 
	58, 59, 62, 58, 59, 63, 58, 59, 
	64, 58, 59, 65, 58, 59, 66, 58, 
	59, 67, 58, 59, 68, 58, 59, 69, 
	58, 59, 70, 58, 59, 71, 58, 59, 
	72, 58, 59, 73, 58, 59, 4, 58, 
	59, 75, 58, 4, 4, 5, 14, 16, 
	30, 33, 36, 38, 41, 76, 239, 311, 
	313, 4, 0, 77, 217, 0, 78, 147, 
	151, 0, 79, 0, 80, 0, 81, 0, 
	82, 0, 83, 0, 84, 0, 85, 0, 
	86, 0, 87, 0, 89, 88, 89, 88, 
	89, 89, 4, 90, 4, 104, 120, 141, 
	89, 88, 89, 91, 88, 89, 92, 88, 
	89, 93, 88, 89, 94, 88, 89, 95, 
	88, 89, 96, 88, 89, 97, 88, 89, 
	98, 88, 89, 99, 88, 89, 100, 88, 
	89, 101, 88, 89, 102, 88, 89, 103, 
	88, 89, 4, 88, 105, 89, 88, 106, 
	89, 88, 107, 89, 88, 108, 89, 88, 
	89, 109, 88, 89, 110, 88, 89, 111, 
	88, 89, 112, 88, 89, 113, 88, 89, 
	114, 88, 89, 115, 88, 116, 89, 88, 
	117, 89, 88, 89, 118, 88, 89, 119, 
	88, 89, 75, 88, 89, 121, 134, 88, 
	122, 89, 130, 88, 123, 89, 88, 89, 
	124, 88, 89, 125, 88, 89, 126, 88, 
	89, 127, 88, 89, 128, 88, 89, 129, 
	88, 89, 119, 88, 89, 131, 88, 89, 
	132, 88, 89, 133, 88, 89, 119, 88, 
	135, 89, 88, 136, 89, 88, 89, 137, 
	88, 89, 138, 88, 89, 139, 88, 89, 
	140, 88, 89, 119, 88, 89, 142, 88, 
	89, 143, 88, 89, 144, 88, 145, 89, 
	88, 146, 89, 88, 89, 119, 88, 148, 
	0, 149, 0, 150, 0, 30, 0, 152, 
	0, 153, 0, 154, 0, 155, 0, 156, 
	0, 158, 157, 158, 157, 158, 158, 4, 
	159, 173, 4, 174, 176, 179, 195, 209, 
	215, 158, 157, 158, 160, 157, 158, 161, 
	157, 158, 162, 157, 158, 163, 157, 158, 
	164, 157, 158, 165, 157, 158, 166, 157, 
	158, 167, 157, 158, 168, 157, 158, 169, 
	157, 158, 170, 157, 158, 171, 157, 158, 
	172, 157, 158, 4, 157, 158, 75, 157, 
	158, 75, 175, 157, 158, 173, 157, 158, 
	177, 157, 178, 158, 157, 173, 158, 157, 
	180, 158, 157, 181, 158, 157, 182, 158, 
	157, 183, 158, 157, 158, 184, 157, 158, 
	185, 157, 158, 186, 157, 158, 187, 157, 
	158, 188, 157, 158, 189, 157, 158, 190, 
	157, 191, 158, 157, 192, 158, 157, 158, 
	193, 157, 158, 194, 157, 158, 75, 157, 
	158, 196, 157, 197, 158, 205, 157, 198, 
	158, 157, 158, 199, 157, 158, 200, 157, 
	158, 201, 157, 158, 202, 157, 158, 203, 
	157, 158, 204, 157, 158, 194, 157, 158, 
	206, 157, 158, 207, 157, 208, 158, 157, 
	173, 158, 157, 158, 210, 157, 158, 211, 
	157, 158, 212, 157, 213, 158, 157, 214, 
	158, 157, 158, 194, 157, 158, 216, 157, 
	158, 173, 157, 218, 0, 219, 0, 220, 
	0, 221, 0, 222, 0, 223, 0, 224, 
	0, 225, 0, 227, 226, 227, 226, 227, 
	227, 4, 228, 4, 227, 226, 227, 229, 
	226, 230, 227, 226, 231, 227, 226, 227, 
	232, 226, 227, 233, 226, 227, 234, 226, 
	227, 235, 226, 227, 236, 226, 227, 237, 
	226, 227, 238, 226, 227, 75, 226, 240, 
	0, 241, 0, 242, 0, 243, 0, 244, 
	0, 245, 0, 246, 0, 248, 247, 248, 
	247, 248, 248, 4, 249, 263, 4, 264, 
	266, 269, 285, 303, 309, 248, 247, 248, 
	250, 247, 248, 251, 247, 248, 252, 247, 
	248, 253, 247, 248, 254, 247, 248, 255, 
	247, 248, 256, 247, 248, 257, 247, 248, 
	258, 247, 248, 259, 247, 248, 260, 247, 
	248, 261, 247, 248, 262, 247, 248, 4, 
	247, 248, 75, 247, 248, 75, 265, 247, 
	248, 263, 247, 248, 267, 247, 268, 248, 
	247, 263, 248, 247, 270, 248, 247, 271, 
	248, 247, 272, 248, 247, 273, 248, 247, 
	248, 274, 247, 248, 275, 247, 248, 276, 
	247, 248, 277, 247, 248, 278, 247, 248, 
	279, 247, 248, 280, 247, 281, 248, 247, 
	282, 248, 247, 248, 283, 247, 248, 284, 
	247, 248, 75, 247, 248, 286, 247, 287, 
	248, 295, 299, 247, 288, 248, 247, 248, 
	289, 247, 248, 290, 247, 248, 291, 247, 
	248, 292, 247, 248, 293, 247, 248, 294, 
	247, 248, 284, 247, 248, 296, 247, 248, 
	297, 247, 298, 248, 247, 263, 248, 247, 
	248, 300, 247, 248, 301, 247, 248, 302, 
	247, 248, 284, 247, 248, 304, 247, 248, 
	305, 247, 248, 306, 247, 307, 248, 247, 
	308, 248, 247, 248, 284, 247, 248, 310, 
	247, 248, 263, 247, 312, 0, 30, 0, 
	313, 314, 313, 0, 318, 317, 316, 314, 
	317, 315, 0, 316, 314, 315, 0, 316, 
	315, 318, 317, 316, 314, 317, 315, 318, 
	318, 5, 14, 16, 30, 33, 36, 38, 
	41, 76, 239, 311, 313, 318, 0, 59, 
	75, 320, 58, 59, 74, 58, 59, 322, 
	58, 323, 59, 58, 74, 59, 58, 59, 
	325, 58, 326, 59, 335, 58, 327, 59, 
	58, 59, 328, 58, 59, 329, 58, 59, 
	330, 58, 59, 331, 58, 59, 332, 58, 
	59, 333, 58, 59, 334, 58, 59, 75, 
	58, 59, 336, 58, 59, 337, 58, 338, 
	59, 58, 74, 59, 58, 59, 340, 58, 
	59, 341, 58, 59, 342, 58, 343, 59, 
	58, 344, 59, 58, 59, 334, 58, 59, 
	346, 58, 59, 74, 58, 0, 0
};

static const char _lexer_trans_actions[] = {
	0, 47, 0, 5, 1, 0, 25, 1, 
	25, 25, 25, 25, 25, 25, 31, 0, 
	39, 0, 39, 0, 39, 47, 0, 5, 
	1, 0, 25, 1, 25, 25, 25, 25, 
	25, 25, 31, 0, 39, 0, 39, 0, 
	39, 47, 0, 0, 39, 119, 41, 41, 
	41, 3, 111, 29, 29, 29, 0, 111, 
	29, 29, 29, 0, 111, 29, 0, 29, 
	0, 95, 7, 7, 39, 47, 0, 0, 
	39, 103, 21, 0, 47, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 39, 50, 99, 19, 
	0, 39, 39, 39, 39, 0, 23, 107, 
	23, 23, 44, 23, 0, 47, 0, 1, 
	0, 39, 0, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 124, 50, 47, 
	0, 47, 0, 71, 29, 77, 71, 77, 
	77, 77, 77, 77, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 15, 0, 
	47, 15, 0, 115, 27, 53, 50, 27, 
	56, 50, 56, 56, 56, 56, 56, 56, 
	59, 27, 39, 0, 0, 39, 0, 0, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 124, 50, 47, 0, 
	47, 0, 62, 29, 62, 77, 77, 77, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 9, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 47, 0, 
	0, 47, 0, 47, 0, 0, 47, 0, 
	0, 47, 9, 0, 47, 0, 0, 0, 
	0, 47, 0, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	0, 47, 0, 0, 47, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 47, 0, 0, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 124, 50, 47, 0, 47, 0, 65, 
	29, 77, 65, 77, 77, 77, 77, 77, 
	77, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 11, 0, 47, 11, 0, 
	47, 11, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 0, 47, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 11, 0, 
	47, 0, 0, 0, 47, 0, 0, 0, 
	47, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 47, 0, 
	0, 47, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 124, 50, 47, 0, 47, 
	0, 74, 77, 74, 0, 0, 47, 0, 
	0, 0, 47, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 17, 0, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 124, 50, 47, 
	0, 47, 0, 68, 29, 77, 68, 77, 
	77, 77, 77, 77, 77, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 13, 
	0, 47, 13, 0, 47, 13, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 47, 0, 
	0, 47, 0, 47, 0, 0, 47, 0, 
	0, 47, 13, 0, 47, 0, 0, 0, 
	47, 0, 0, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 47, 0, 
	0, 47, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 39, 0, 39, 
	0, 0, 0, 39, 47, 33, 33, 80, 
	33, 33, 39, 0, 35, 0, 39, 0, 
	0, 47, 0, 0, 35, 0, 0, 47, 
	0, 86, 83, 37, 89, 83, 89, 89, 
	89, 89, 89, 89, 92, 0, 39, 47, 
	15, 0, 0, 47, 0, 0, 47, 0, 
	0, 0, 47, 0, 0, 47, 0, 47, 
	0, 0, 0, 47, 0, 0, 0, 47, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 15, 
	0, 47, 0, 0, 47, 0, 0, 0, 
	47, 0, 0, 47, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 0
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
	39, 39, 39, 39
};

static const int lexer_start = 1;
static const int lexer_first_final = 347;
static const int lexer_error = 0;

static const int lexer_en_main = 1;


#line 243 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"

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
    
    
#line 915 "ext/gherkin_lexer_sk/gherkin_lexer_sk.c"
	{
	cs = lexer_start;
	}

#line 425 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
    
#line 922 "ext/gherkin_lexer_sk/gherkin_lexer_sk.c"
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
#line 86 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
		MARK(content_start, p);
    lexer->current_line = lexer->line_number;
  }
	break;
	case 1:
#line 91 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    MARK(content_start, p);
  }
	break;
	case 2:
#line 95 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    lexer->current_line = lexer->line_number;
    lexer->start_col = p - data - lexer->last_newline;
  }
	break;
	case 3:
#line 100 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    int len = LEN(content_start, PTR_TO(final_newline));

    if (len < 0) len = 0;

    store_pystring_content(listener, lexer->start_col, PTR_TO(content_start), len, lexer->current_line);
  }
	break;
	case 4:
#line 108 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_KW_END_CON(feature);
  }
	break;
	case 5:
#line 112 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_KW_END_CON(background);
  }
	break;
	case 6:
#line 116 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_KW_END_CON(scenario);
  }
	break;
	case 7:
#line 120 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_KW_END_CON(scenario_outline);
  }
	break;
	case 8:
#line 124 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_KW_END_CON(examples);
  }
	break;
	case 9:
#line 128 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    store_kw_con(listener, "step",
      PTR_TO(keyword_start), LEN(keyword_start, PTR_TO(keyword_end)),
      PTR_TO(content_start), LEN(content_start, p), 
      lexer->current_line);
  }
	break;
	case 10:
#line 135 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_ATTR(comment);
    lexer->mark = 0;
  }
	break;
	case 11:
#line 140 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    STORE_ATTR(tag);
    lexer->mark = 0;
  }
	break;
	case 12:
#line 145 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    lexer->line_number += 1;
    MARK(final_newline, p);
  }
	break;
	case 13:
#line 150 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    MARK(last_newline, p + 1);
  }
	break;
	case 14:
#line 154 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    if (lexer->mark == 0) {
      MARK(mark, p);
    }
  }
	break;
	case 15:
#line 160 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    MARK(keyword_end, p);
    MARK(keyword_start, PTR_TO(mark));
    MARK(content_start, p + 1);
    lexer->mark = 0;
  }
	break;
	case 16:
#line 167 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    MARK(content_end, p);
  }
	break;
	case 17:
#line 171 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    p = p - 1;
    lexer->current_line = lexer->line_number;
    current_row = rb_ary_new();
  }
	break;
	case 18:
#line 177 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
		MARK(content_start, p);
  }
	break;
	case 19:
#line 181 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
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
#line 192 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
	{
    rb_funcall(listener, rb_intern("row"), 2, current_row, INT2FIX(lexer->current_line));
  }
	break;
	case 21:
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
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
#line 1190 "ext/gherkin_lexer_sk/gherkin_lexer_sk.c"
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
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"
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
#line 1249 "ext/gherkin_lexer_sk/gherkin_lexer_sk.c"
		}
	}
	}

	_out: {}
	}

#line 426 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/sk.c.rl"

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

void Init_gherkin_lexer_sk()
{
  mGherkin = rb_define_module("Gherkin");
  rb_eGherkinLexingError = rb_const_get(mGherkin, rb_intern("LexingError"));

  mCLexer = rb_define_module_under(mGherkin, "CLexer");
  cI18nLexer = rb_define_class_under(mCLexer, "Sk", rb_cObject);
  rb_define_alloc_func(cI18nLexer, CLexer_alloc);
  rb_define_method(cI18nLexer, "initialize", CLexer_init, 1);
  rb_define_method(cI18nLexer, "scan", CLexer_scan, 1);
}

