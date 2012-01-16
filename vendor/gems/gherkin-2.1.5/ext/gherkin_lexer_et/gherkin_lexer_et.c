
#line 1 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
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


#line 239 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"


/** Data **/

#line 92 "ext/gherkin_lexer_et/gherkin_lexer_et.c"
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
	0, 0, 18, 19, 20, 37, 38, 39, 
	43, 48, 53, 58, 63, 68, 72, 76, 
	78, 79, 80, 81, 82, 83, 84, 85, 
	86, 87, 88, 89, 90, 91, 92, 93, 
	94, 95, 97, 102, 109, 114, 115, 116, 
	117, 118, 119, 120, 121, 123, 124, 125, 
	126, 127, 128, 129, 130, 131, 132, 139, 
	141, 143, 145, 147, 149, 151, 168, 169, 
	170, 172, 173, 174, 175, 176, 177, 178, 
	179, 180, 192, 194, 196, 198, 200, 202, 
	204, 206, 208, 210, 212, 214, 216, 218, 
	220, 222, 224, 226, 228, 230, 232, 234, 
	236, 238, 240, 242, 244, 246, 248, 250, 
	252, 254, 256, 258, 260, 262, 264, 266, 
	268, 270, 272, 274, 276, 278, 280, 282, 
	283, 284, 285, 286, 287, 288, 289, 290, 
	291, 292, 293, 294, 295, 296, 297, 298, 
	299, 312, 314, 316, 318, 320, 322, 324, 
	326, 328, 330, 332, 334, 336, 338, 340, 
	342, 344, 346, 348, 350, 352, 354, 356, 
	358, 360, 362, 365, 367, 369, 371, 373, 
	375, 377, 380, 382, 384, 386, 388, 390, 
	392, 394, 396, 398, 400, 402, 403, 404, 
	405, 406, 407, 408, 409, 410, 411, 412, 
	413, 414, 415, 430, 432, 434, 436, 438, 
	440, 442, 444, 446, 448, 450, 452, 454, 
	456, 458, 460, 462, 464, 466, 468, 470, 
	472, 474, 476, 478, 480, 483, 485, 487, 
	489, 491, 493, 495, 497, 499, 501, 503, 
	505, 507, 509, 511, 513, 515, 517, 519, 
	521, 523, 526, 528, 530, 532, 534, 536, 
	537, 538, 539, 540, 541, 542, 543, 557, 
	559, 561, 563, 565, 567, 569, 571, 573, 
	575, 577, 579, 581, 583, 585, 587, 589, 
	591, 593, 595, 597, 599, 601, 603, 605, 
	607, 610, 612, 614, 616, 618, 620, 622, 
	624, 626, 628, 630, 632, 634, 636, 638, 
	640, 642, 644, 646, 648, 650, 653, 655, 
	659, 665, 668, 670, 676, 693
};

static const char _lexer_trans_keys[] = {
	-17, 10, 32, 34, 35, 37, 42, 64, 
	69, 74, 75, 79, 82, 83, 84, 124, 
	9, 13, -69, -65, 10, 32, 34, 35, 
	37, 42, 64, 69, 74, 75, 79, 82, 
	83, 84, 124, 9, 13, 34, 34, 10, 
	32, 9, 13, 10, 32, 34, 9, 13, 
	10, 32, 34, 9, 13, 10, 32, 34, 
	9, 13, 10, 32, 34, 9, 13, 10, 
	32, 34, 9, 13, 10, 32, 9, 13, 
	10, 32, 9, 13, 10, 13, 10, 95, 
	70, 69, 65, 84, 85, 82, 69, 95, 
	69, 78, 68, 95, 37, 32, 10, 10, 
	13, 13, 32, 64, 9, 10, 9, 10, 
	13, 32, 64, 11, 12, 10, 32, 64, 
	9, 13, 101, 108, 100, 97, 100, 101, 
	115, 97, 117, 104, 116, 117, 109, 105, 
	100, 58, 10, 10, 10, 32, 35, 79, 
	124, 9, 13, 10, 109, 10, 97, 10, 
	100, 10, 117, 10, 115, 10, 58, 10, 
	32, 34, 35, 37, 42, 64, 69, 74, 
	75, 79, 82, 83, 84, 124, 9, 13, 
	117, 105, 32, 100, 109, 97, 100, 117, 
	115, 58, 10, 10, 10, 32, 35, 37, 
	64, 74, 79, 82, 83, 84, 9, 13, 
	10, 95, 10, 70, 10, 69, 10, 65, 
	10, 84, 10, 85, 10, 82, 10, 69, 
	10, 95, 10, 69, 10, 78, 10, 68, 
	10, 95, 10, 37, 10, 117, 10, 104, 
	10, 116, 10, 117, 10, 109, 10, 105, 
	10, 100, 10, 58, 10, 109, 10, 97, 
	10, 100, 10, 117, 10, 115, 10, 97, 
	10, 97, 10, 109, 10, 115, 10, 116, 
	10, 115, 10, 101, 10, 110, 10, 97, 
	10, 97, 10, 114, 10, 105, 10, 117, 
	10, 109, 10, 97, 10, 117, 10, 115, 
	10, 116, 97, 97, 109, 115, 116, 115, 
	101, 110, 97, 97, 114, 105, 117, 109, 
	58, 10, 10, 10, 32, 35, 37, 42, 
	64, 69, 74, 75, 79, 83, 9, 13, 
	10, 95, 10, 70, 10, 69, 10, 65, 
	10, 84, 10, 85, 10, 82, 10, 69, 
	10, 95, 10, 69, 10, 78, 10, 68, 
	10, 95, 10, 37, 10, 32, 10, 101, 
	10, 108, 10, 100, 10, 97, 10, 100, 
	10, 101, 10, 115, 10, 97, 10, 117, 
	10, 105, 10, 32, 100, 10, 109, 10, 
	97, 10, 100, 10, 117, 10, 115, 10, 
	58, 10, 105, 116, 10, 105, 10, 115, 
	10, 101, 10, 110, 10, 97, 10, 97, 
	10, 114, 10, 105, 10, 117, 10, 109, 
	105, 116, 105, 115, 101, 110, 97, 97, 
	114, 105, 117, 109, 58, 10, 10, 10, 
	32, 35, 37, 42, 64, 69, 74, 75, 
	79, 82, 83, 84, 9, 13, 10, 95, 
	10, 70, 10, 69, 10, 65, 10, 84, 
	10, 85, 10, 82, 10, 69, 10, 95, 
	10, 69, 10, 78, 10, 68, 10, 95, 
	10, 37, 10, 32, 10, 101, 10, 108, 
	10, 100, 10, 97, 10, 100, 10, 101, 
	10, 115, 10, 97, 10, 117, 10, 105, 
	10, 32, 100, 10, 109, 10, 97, 10, 
	100, 10, 117, 10, 115, 10, 58, 10, 
	97, 10, 97, 10, 109, 10, 115, 10, 
	116, 10, 115, 10, 101, 10, 110, 10, 
	97, 10, 97, 10, 114, 10, 105, 10, 
	117, 10, 109, 10, 105, 116, 10, 105, 
	10, 97, 10, 117, 10, 115, 10, 116, 
	97, 117, 115, 116, 58, 10, 10, 10, 
	32, 35, 37, 42, 64, 69, 74, 75, 
	79, 82, 83, 9, 13, 10, 95, 10, 
	70, 10, 69, 10, 65, 10, 84, 10, 
	85, 10, 82, 10, 69, 10, 95, 10, 
	69, 10, 78, 10, 68, 10, 95, 10, 
	37, 10, 32, 10, 101, 10, 108, 10, 
	100, 10, 97, 10, 100, 10, 101, 10, 
	115, 10, 97, 10, 117, 10, 105, 10, 
	32, 100, 10, 109, 10, 97, 10, 100, 
	10, 117, 10, 115, 10, 58, 10, 97, 
	10, 97, 10, 109, 10, 115, 10, 116, 
	10, 115, 10, 101, 10, 110, 10, 97, 
	10, 97, 10, 114, 10, 105, 10, 117, 
	10, 109, 10, 105, 116, 10, 105, 32, 
	124, 9, 13, 10, 32, 92, 124, 9, 
	13, 10, 92, 124, 10, 92, 10, 32, 
	92, 124, 9, 13, 10, 32, 34, 35, 
	37, 42, 64, 69, 74, 75, 79, 82, 
	83, 84, 124, 9, 13, 0
};

static const char _lexer_single_lengths[] = {
	0, 16, 1, 1, 15, 1, 1, 2, 
	3, 3, 3, 3, 3, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 2, 3, 5, 3, 1, 1, 1, 
	1, 1, 1, 1, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 5, 2, 
	2, 2, 2, 2, 2, 15, 1, 1, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 10, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	11, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 3, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 13, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 3, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 1, 
	1, 1, 1, 1, 1, 1, 12, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	3, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	4, 3, 2, 4, 15, 0
};

static const char _lexer_range_lengths[] = {
	0, 1, 0, 0, 1, 0, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 1, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	1, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 0, 0, 0, 0, 0, 
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
	0, 0, 0, 0, 0, 0, 0, 1, 
	1, 0, 0, 1, 1, 0
};

static const short _lexer_index_offsets[] = {
	0, 0, 18, 20, 22, 39, 41, 43, 
	47, 52, 57, 62, 67, 72, 76, 80, 
	83, 85, 87, 89, 91, 93, 95, 97, 
	99, 101, 103, 105, 107, 109, 111, 113, 
	115, 117, 120, 125, 132, 137, 139, 141, 
	143, 145, 147, 149, 151, 154, 156, 158, 
	160, 162, 164, 166, 168, 170, 172, 179, 
	182, 185, 188, 191, 194, 197, 214, 216, 
	218, 221, 223, 225, 227, 229, 231, 233, 
	235, 237, 249, 252, 255, 258, 261, 264, 
	267, 270, 273, 276, 279, 282, 285, 288, 
	291, 294, 297, 300, 303, 306, 309, 312, 
	315, 318, 321, 324, 327, 330, 333, 336, 
	339, 342, 345, 348, 351, 354, 357, 360, 
	363, 366, 369, 372, 375, 378, 381, 384, 
	386, 388, 390, 392, 394, 396, 398, 400, 
	402, 404, 406, 408, 410, 412, 414, 416, 
	418, 431, 434, 437, 440, 443, 446, 449, 
	452, 455, 458, 461, 464, 467, 470, 473, 
	476, 479, 482, 485, 488, 491, 494, 497, 
	500, 503, 506, 510, 513, 516, 519, 522, 
	525, 528, 532, 535, 538, 541, 544, 547, 
	550, 553, 556, 559, 562, 565, 567, 569, 
	571, 573, 575, 577, 579, 581, 583, 585, 
	587, 589, 591, 606, 609, 612, 615, 618, 
	621, 624, 627, 630, 633, 636, 639, 642, 
	645, 648, 651, 654, 657, 660, 663, 666, 
	669, 672, 675, 678, 681, 685, 688, 691, 
	694, 697, 700, 703, 706, 709, 712, 715, 
	718, 721, 724, 727, 730, 733, 736, 739, 
	742, 745, 749, 752, 755, 758, 761, 764, 
	766, 768, 770, 772, 774, 776, 778, 792, 
	795, 798, 801, 804, 807, 810, 813, 816, 
	819, 822, 825, 828, 831, 834, 837, 840, 
	843, 846, 849, 852, 855, 858, 861, 864, 
	867, 871, 874, 877, 880, 883, 886, 889, 
	892, 895, 898, 901, 904, 907, 910, 913, 
	916, 919, 922, 925, 928, 931, 935, 938, 
	942, 948, 952, 955, 961, 978
};

static const short _lexer_trans_targs[] = {
	2, 4, 4, 5, 15, 17, 31, 34, 
	37, 44, 62, 65, 119, 180, 247, 303, 
	4, 0, 3, 0, 4, 0, 4, 4, 
	5, 15, 17, 31, 34, 37, 44, 62, 
	65, 119, 180, 247, 303, 4, 0, 6, 
	0, 7, 0, 8, 7, 7, 0, 9, 
	9, 10, 9, 9, 9, 9, 10, 9, 
	9, 9, 9, 11, 9, 9, 9, 9, 
	12, 9, 9, 4, 13, 14, 13, 0, 
	4, 13, 13, 0, 4, 13, 13, 0, 
	4, 16, 15, 4, 0, 18, 0, 19, 
	0, 20, 0, 21, 0, 22, 0, 23, 
	0, 24, 0, 25, 0, 26, 0, 27, 
	0, 28, 0, 29, 0, 30, 0, 309, 
	0, 32, 0, 0, 33, 4, 16, 33, 
	0, 0, 0, 0, 35, 36, 4, 36, 
	36, 34, 35, 35, 4, 36, 34, 36, 
	0, 38, 0, 39, 0, 40, 0, 41, 
	0, 42, 0, 43, 0, 31, 0, 31, 
	45, 0, 46, 0, 47, 0, 48, 0, 
	49, 0, 50, 0, 51, 0, 52, 0, 
	54, 53, 54, 53, 54, 54, 4, 55, 
	4, 54, 53, 54, 56, 53, 54, 57, 
	53, 54, 58, 53, 54, 59, 53, 54, 
	60, 53, 54, 61, 53, 4, 4, 5, 
	15, 17, 31, 34, 37, 44, 62, 65, 
	119, 180, 247, 303, 4, 0, 63, 0, 
	64, 0, 32, 31, 0, 66, 0, 67, 
	0, 68, 0, 69, 0, 70, 0, 71, 
	0, 73, 72, 73, 72, 73, 73, 4, 
	74, 4, 88, 96, 101, 105, 115, 73, 
	72, 73, 75, 72, 73, 76, 72, 73, 
	77, 72, 73, 78, 72, 73, 79, 72, 
	73, 80, 72, 73, 81, 72, 73, 82, 
	72, 73, 83, 72, 73, 84, 72, 73, 
	85, 72, 73, 86, 72, 73, 87, 72, 
	73, 4, 72, 73, 89, 72, 73, 90, 
	72, 73, 91, 72, 73, 92, 72, 73, 
	93, 72, 73, 94, 72, 73, 95, 72, 
	73, 61, 72, 73, 97, 72, 73, 98, 
	72, 73, 99, 72, 73, 100, 72, 73, 
	95, 72, 73, 102, 72, 73, 103, 72, 
	73, 104, 72, 73, 105, 72, 73, 106, 
	72, 73, 107, 72, 73, 108, 72, 73, 
	109, 72, 73, 110, 72, 73, 111, 72, 
	73, 112, 72, 73, 113, 72, 73, 114, 
	72, 73, 95, 72, 73, 116, 72, 73, 
	117, 72, 73, 118, 72, 73, 95, 72, 
	120, 0, 121, 0, 122, 0, 123, 0, 
	124, 0, 125, 0, 126, 0, 127, 0, 
	128, 0, 129, 0, 130, 0, 131, 0, 
	132, 0, 133, 0, 134, 0, 136, 135, 
	136, 135, 136, 136, 4, 137, 151, 4, 
	152, 159, 160, 163, 169, 136, 135, 136, 
	138, 135, 136, 139, 135, 136, 140, 135, 
	136, 141, 135, 136, 142, 135, 136, 143, 
	135, 136, 144, 135, 136, 145, 135, 136, 
	146, 135, 136, 147, 135, 136, 148, 135, 
	136, 149, 135, 136, 150, 135, 136, 4, 
	135, 136, 61, 135, 136, 153, 135, 136, 
	154, 135, 136, 155, 135, 136, 156, 135, 
	136, 157, 135, 136, 158, 135, 136, 151, 
	135, 136, 151, 135, 136, 161, 135, 136, 
	162, 135, 136, 61, 151, 135, 136, 164, 
	135, 136, 165, 135, 136, 166, 135, 136, 
	167, 135, 136, 168, 135, 136, 61, 135, 
	136, 170, 171, 135, 136, 158, 135, 136, 
	172, 135, 136, 173, 135, 136, 174, 135, 
	136, 175, 135, 136, 176, 135, 136, 177, 
	135, 136, 178, 135, 136, 179, 135, 136, 
	168, 135, 181, 182, 0, 43, 0, 183, 
	0, 184, 0, 185, 0, 186, 0, 187, 
	0, 188, 0, 189, 0, 190, 0, 191, 
	0, 192, 0, 194, 193, 194, 193, 194, 
	194, 4, 195, 209, 4, 210, 217, 218, 
	221, 227, 241, 243, 194, 193, 194, 196, 
	193, 194, 197, 193, 194, 198, 193, 194, 
	199, 193, 194, 200, 193, 194, 201, 193, 
	194, 202, 193, 194, 203, 193, 194, 204, 
	193, 194, 205, 193, 194, 206, 193, 194, 
	207, 193, 194, 208, 193, 194, 4, 193, 
	194, 61, 193, 194, 211, 193, 194, 212, 
	193, 194, 213, 193, 194, 214, 193, 194, 
	215, 193, 194, 216, 193, 194, 209, 193, 
	194, 209, 193, 194, 219, 193, 194, 220, 
	193, 194, 61, 209, 193, 194, 222, 193, 
	194, 223, 193, 194, 224, 193, 194, 225, 
	193, 194, 226, 193, 194, 61, 193, 194, 
	228, 193, 194, 229, 193, 194, 230, 193, 
	194, 231, 193, 194, 232, 193, 194, 233, 
	193, 194, 234, 193, 194, 235, 193, 194, 
	236, 193, 194, 237, 193, 194, 238, 193, 
	194, 239, 193, 194, 240, 193, 194, 226, 
	193, 194, 242, 232, 193, 194, 216, 193, 
	194, 244, 193, 194, 245, 193, 194, 246, 
	193, 194, 226, 193, 248, 0, 249, 0, 
	250, 0, 251, 0, 252, 0, 254, 253, 
	254, 253, 254, 254, 4, 255, 269, 4, 
	270, 277, 278, 281, 287, 301, 254, 253, 
	254, 256, 253, 254, 257, 253, 254, 258, 
	253, 254, 259, 253, 254, 260, 253, 254, 
	261, 253, 254, 262, 253, 254, 263, 253, 
	254, 264, 253, 254, 265, 253, 254, 266, 
	253, 254, 267, 253, 254, 268, 253, 254, 
	4, 253, 254, 61, 253, 254, 271, 253, 
	254, 272, 253, 254, 273, 253, 254, 274, 
	253, 254, 275, 253, 254, 276, 253, 254, 
	269, 253, 254, 269, 253, 254, 279, 253, 
	254, 280, 253, 254, 61, 269, 253, 254, 
	282, 253, 254, 283, 253, 254, 284, 253, 
	254, 285, 253, 254, 286, 253, 254, 61, 
	253, 254, 288, 253, 254, 289, 253, 254, 
	290, 253, 254, 291, 253, 254, 292, 253, 
	254, 293, 253, 254, 294, 253, 254, 295, 
	253, 254, 296, 253, 254, 297, 253, 254, 
	298, 253, 254, 299, 253, 254, 300, 253, 
	254, 286, 253, 254, 302, 292, 253, 254, 
	276, 253, 303, 304, 303, 0, 308, 307, 
	306, 304, 307, 305, 0, 306, 304, 305, 
	0, 306, 305, 308, 307, 306, 304, 307, 
	305, 308, 308, 5, 15, 17, 31, 34, 
	37, 44, 62, 65, 119, 180, 247, 303, 
	308, 0, 0, 0
};

static const char _lexer_trans_actions[] = {
	0, 47, 0, 5, 1, 0, 25, 1, 
	25, 25, 25, 25, 25, 25, 25, 31, 
	0, 39, 0, 39, 0, 39, 47, 0, 
	5, 1, 0, 25, 1, 25, 25, 25, 
	25, 25, 25, 25, 31, 0, 39, 0, 
	39, 0, 39, 47, 0, 0, 39, 119, 
	41, 41, 41, 3, 111, 29, 29, 29, 
	0, 111, 29, 29, 29, 0, 111, 29, 
	0, 29, 0, 95, 7, 0, 7, 39, 
	47, 0, 0, 39, 95, 7, 7, 39, 
	103, 21, 0, 47, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 39, 50, 99, 19, 0, 
	39, 39, 39, 39, 0, 23, 107, 23, 
	23, 44, 23, 0, 47, 0, 1, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	124, 50, 47, 0, 47, 0, 74, 77, 
	74, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 17, 0, 115, 27, 53, 
	50, 27, 56, 50, 56, 56, 56, 56, 
	56, 56, 56, 59, 27, 39, 0, 39, 
	0, 39, 0, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 124, 50, 47, 0, 47, 0, 62, 
	29, 62, 77, 77, 77, 77, 77, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 9, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 9, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 124, 50, 
	47, 0, 47, 0, 71, 29, 77, 71, 
	77, 77, 77, 77, 77, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 15, 
	0, 47, 15, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 15, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 15, 0, 
	47, 0, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 124, 50, 47, 0, 47, 
	0, 68, 29, 77, 68, 77, 77, 77, 
	77, 77, 77, 77, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 13, 0, 
	47, 13, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 13, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 13, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 124, 50, 
	47, 0, 47, 0, 65, 29, 77, 65, 
	77, 77, 77, 77, 77, 77, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	11, 0, 47, 11, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 11, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 11, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 0, 0, 0, 39, 47, 33, 
	33, 80, 33, 33, 39, 0, 35, 0, 
	39, 0, 0, 47, 0, 0, 35, 0, 
	0, 47, 0, 86, 83, 37, 89, 83, 
	89, 89, 89, 89, 89, 89, 89, 92, 
	0, 39, 0, 0
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
	39, 39, 39, 39, 39, 39
};

static const int lexer_start = 1;
static const int lexer_first_final = 309;
static const int lexer_error = 0;

static const int lexer_en_main = 1;


#line 243 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"

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
    
    
#line 855 "ext/gherkin_lexer_et/gherkin_lexer_et.c"
	{
	cs = lexer_start;
	}

#line 425 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
    
#line 862 "ext/gherkin_lexer_et/gherkin_lexer_et.c"
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
#line 86 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
		MARK(content_start, p);
    lexer->current_line = lexer->line_number;
  }
	break;
	case 1:
#line 91 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    MARK(content_start, p);
  }
	break;
	case 2:
#line 95 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    lexer->current_line = lexer->line_number;
    lexer->start_col = p - data - lexer->last_newline;
  }
	break;
	case 3:
#line 100 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    int len = LEN(content_start, PTR_TO(final_newline));

    if (len < 0) len = 0;

    store_pystring_content(listener, lexer->start_col, PTR_TO(content_start), len, lexer->current_line);
  }
	break;
	case 4:
#line 108 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_KW_END_CON(feature);
  }
	break;
	case 5:
#line 112 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_KW_END_CON(background);
  }
	break;
	case 6:
#line 116 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_KW_END_CON(scenario);
  }
	break;
	case 7:
#line 120 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_KW_END_CON(scenario_outline);
  }
	break;
	case 8:
#line 124 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_KW_END_CON(examples);
  }
	break;
	case 9:
#line 128 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    store_kw_con(listener, "step",
      PTR_TO(keyword_start), LEN(keyword_start, PTR_TO(keyword_end)),
      PTR_TO(content_start), LEN(content_start, p), 
      lexer->current_line);
  }
	break;
	case 10:
#line 135 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_ATTR(comment);
    lexer->mark = 0;
  }
	break;
	case 11:
#line 140 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    STORE_ATTR(tag);
    lexer->mark = 0;
  }
	break;
	case 12:
#line 145 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    lexer->line_number += 1;
    MARK(final_newline, p);
  }
	break;
	case 13:
#line 150 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    MARK(last_newline, p + 1);
  }
	break;
	case 14:
#line 154 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    if (lexer->mark == 0) {
      MARK(mark, p);
    }
  }
	break;
	case 15:
#line 160 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    MARK(keyword_end, p);
    MARK(keyword_start, PTR_TO(mark));
    MARK(content_start, p + 1);
    lexer->mark = 0;
  }
	break;
	case 16:
#line 167 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    MARK(content_end, p);
  }
	break;
	case 17:
#line 171 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    p = p - 1;
    lexer->current_line = lexer->line_number;
    current_row = rb_ary_new();
  }
	break;
	case 18:
#line 177 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
		MARK(content_start, p);
  }
	break;
	case 19:
#line 181 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
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
#line 192 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
	{
    rb_funcall(listener, rb_intern("row"), 2, current_row, INT2FIX(lexer->current_line));
  }
	break;
	case 21:
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
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
#line 1130 "ext/gherkin_lexer_et/gherkin_lexer_et.c"
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
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"
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
#line 1189 "ext/gherkin_lexer_et/gherkin_lexer_et.c"
		}
	}
	}

	_out: {}
	}

#line 426 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/et.c.rl"

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

void Init_gherkin_lexer_et()
{
  mGherkin = rb_define_module("Gherkin");
  rb_eGherkinLexingError = rb_const_get(mGherkin, rb_intern("LexingError"));

  mCLexer = rb_define_module_under(mGherkin, "CLexer");
  cI18nLexer = rb_define_class_under(mCLexer, "Et", rb_cObject);
  rb_define_alloc_func(cI18nLexer, CLexer_alloc);
  rb_define_method(cI18nLexer, "initialize", CLexer_init, 1);
  rb_define_method(cI18nLexer, "scan", CLexer_scan, 1);
}

