
#line 1 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
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


#line 239 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"


/** Data **/

#line 92 "ext/gherkin_lexer_ro_ro/gherkin_lexer_ro_ro.c"
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
	0, 0, 18, 19, 20, 21, 22, 24, 
	41, 42, 43, 47, 52, 57, 62, 67, 
	72, 76, 80, 82, 83, 84, 85, 86, 
	87, 88, 89, 90, 91, 92, 93, 94, 
	95, 96, 97, 102, 109, 114, 115, 116, 
	117, 118, 120, 121, 122, 123, 124, 125, 
	126, 127, 128, 129, 130, 131, 132, 133, 
	147, 149, 151, 153, 170, 171, 173, 174, 
	175, 176, 177, 178, 179, 180, 181, 182, 
	183, 184, 185, 186, 193, 195, 197, 199, 
	201, 203, 205, 207, 209, 211, 213, 215, 
	217, 219, 221, 223, 225, 226, 227, 228, 
	229, 230, 231, 232, 233, 234, 235, 236, 
	237, 238, 239, 240, 241, 242, 243, 254, 
	256, 258, 260, 262, 264, 266, 268, 270, 
	272, 274, 276, 278, 280, 282, 284, 286, 
	288, 290, 292, 294, 296, 298, 300, 302, 
	304, 306, 308, 310, 312, 314, 316, 318, 
	320, 322, 324, 326, 328, 330, 332, 334, 
	336, 338, 340, 342, 344, 346, 348, 350, 
	352, 354, 356, 358, 361, 363, 365, 367, 
	369, 371, 373, 375, 377, 379, 381, 383, 
	384, 385, 386, 387, 388, 389, 390, 392, 
	393, 394, 408, 410, 412, 414, 416, 418, 
	420, 422, 424, 426, 428, 430, 432, 434, 
	436, 438, 440, 442, 444, 446, 448, 450, 
	453, 455, 457, 459, 461, 463, 465, 467, 
	469, 471, 473, 475, 477, 480, 482, 484, 
	486, 488, 490, 492, 494, 496, 498, 500, 
	502, 504, 506, 508, 510, 512, 514, 516, 
	518, 520, 522, 524, 526, 528, 531, 533, 
	535, 537, 539, 541, 543, 545, 547, 549, 
	551, 553, 554, 555, 556, 557, 558, 559, 
	560, 561, 562, 563, 564, 565, 566, 567, 
	581, 583, 585, 587, 589, 591, 593, 595, 
	597, 599, 601, 603, 605, 607, 609, 611, 
	613, 615, 617, 619, 621, 623, 625, 627, 
	629, 631, 633, 636, 638, 640, 642, 644, 
	646, 648, 650, 652, 654, 656, 658, 660, 
	662, 664, 666, 668, 670, 672, 674, 676, 
	678, 680, 682, 684, 686, 690, 696, 699, 
	701, 707, 724, 726, 728, 730, 732, 734, 
	736, 738, 740, 742, 744, 746, 748, 750, 
	752, 754, 756, 758, 760, 762, 764, 766, 
	768, 770, 773, 775, 777, 779, 781, 783, 
	785, 787, 789, 791, 793, 795, 797, 799, 
	801, 803, 805, 807, 809, 811, 813, 815, 
	817, 819, 821, 823, 826, 828, 830, 832, 
	834, 836, 838, 840, 842, 844, 846, 848, 
	849, 850
};

static const char _lexer_trans_keys[] = {
	-56, -17, 10, 32, 34, 35, 37, 42, 
	64, 65, 67, 68, 69, 70, 83, 124, 
	9, 13, -104, 105, 32, 10, 10, 13, 
	-56, 10, 32, 34, 35, 37, 42, 64, 
	65, 67, 68, 69, 70, 83, 124, 9, 
	13, 34, 34, 10, 32, 9, 13, 10, 
	32, 34, 9, 13, 10, 32, 34, 9, 
	13, 10, 32, 34, 9, 13, 10, 32, 
	34, 9, 13, 10, 32, 34, 9, 13, 
	10, 32, 9, 13, 10, 32, 9, 13, 
	10, 13, 10, 95, 70, 69, 65, 84, 
	85, 82, 69, 95, 69, 78, 68, 95, 
	37, 13, 32, 64, 9, 10, 9, 10, 
	13, 32, 64, 11, 12, 10, 32, 64, 
	9, 13, 116, 117, 110, 99, -61, 111, 
	-94, 110, 100, 110, 100, 105, -59, -93, 
	105, 105, 58, 10, 10, -56, 10, 32, 
	35, 37, 42, 64, 65, 67, 68, 70, 
	83, 9, 13, -104, 10, 10, 105, 10, 
	32, -56, 10, 32, 34, 35, 37, 42, 
	64, 65, 67, 68, 69, 70, 83, 124, 
	9, 13, 97, 99, 114, -60, -125, 120, 
	101, 109, 112, 108, 101, 108, 101, 58, 
	10, 10, 10, 32, 35, 70, 124, 9, 
	13, 10, 117, 10, 110, 10, 99, -56, 
	10, -101, 10, 10, 105, 10, 111, 10, 
	110, 10, 97, 10, 108, 10, 105, 10, 
	116, 10, 97, 10, 116, 10, 101, 10, 
	58, 117, 110, 99, -56, -101, 105, 111, 
	110, 97, 108, 105, 116, 97, 116, 101, 
	58, 10, 10, 10, 32, 35, 37, 64, 
	67, 69, 70, 83, 9, 13, 10, 95, 
	10, 70, 10, 69, 10, 65, 10, 84, 
	10, 85, 10, 82, 10, 69, 10, 95, 
	10, 69, 10, 78, 10, 68, 10, 95, 
	10, 37, 10, 111, 10, 110, 10, 100, 
	10, 105, -59, 10, -93, 10, 10, 105, 
	10, 105, 10, 58, 10, 120, 10, 101, 
	10, 109, 10, 112, 10, 108, 10, 101, 
	10, 108, 10, 101, 10, 117, 10, 110, 
	10, 99, -56, 10, -101, 10, 10, 105, 
	10, 111, 10, 110, 10, 97, 10, 108, 
	10, 105, 10, 116, 10, 97, 10, 116, 
	10, 99, 10, 101, 10, 110, 10, 97, 
	10, 114, 10, 105, 10, 117, 10, 58, 
	108, 10, 32, 10, 100, 10, 101, 10, 
	32, -59, 10, -97, 10, 10, 97, 10, 
	98, 10, 108, 10, 111, 10, 110, 99, 
	101, 110, 97, 114, 105, 117, 58, 108, 
	10, 10, -56, 10, 32, 35, 37, 42, 
	64, 65, 67, 68, 70, 83, 9, 13, 
	-104, 10, 10, 105, 10, 32, 10, 95, 
	10, 70, 10, 69, 10, 65, 10, 84, 
	10, 85, 10, 82, 10, 69, 10, 95, 
	10, 69, 10, 78, 10, 68, 10, 95, 
	10, 37, 10, 116, 10, 117, 10, 110, 
	10, 99, -61, 10, 111, -94, 10, 10, 
	110, 10, 100, 10, 110, 10, 100, 10, 
	105, -59, 10, -93, 10, 10, 105, 10, 
	105, 10, 58, 10, 97, 10, 99, 114, 
	-60, 10, -125, 10, 10, 117, 10, 110, 
	10, 99, -56, 10, -101, 10, 10, 105, 
	10, 111, 10, 110, 10, 97, 10, 108, 
	10, 105, 10, 116, 10, 97, 10, 116, 
	10, 101, 10, 99, 10, 101, 10, 110, 
	10, 97, 10, 114, 10, 105, 10, 117, 
	10, 58, 108, 10, 32, 10, 100, 10, 
	101, 10, 32, -59, 10, -97, 10, 10, 
	97, 10, 98, 10, 108, 10, 111, 10, 
	110, 32, 100, 101, 32, -59, -97, 97, 
	98, 108, 111, 110, 58, 10, 10, -56, 
	10, 32, 35, 37, 42, 64, 65, 67, 
	68, 70, 83, 9, 13, -104, 10, 10, 
	105, 10, 32, 10, 95, 10, 70, 10, 
	69, 10, 65, 10, 84, 10, 85, 10, 
	82, 10, 69, 10, 95, 10, 69, 10, 
	78, 10, 68, 10, 95, 10, 37, 10, 
	116, 10, 117, 10, 110, 10, 99, -61, 
	10, -94, 10, 10, 110, 10, 100, 10, 
	97, 10, 99, 114, -60, 10, -125, 10, 
	10, 117, 10, 110, 10, 99, -56, 10, 
	-101, 10, 10, 105, 10, 111, 10, 110, 
	10, 97, 10, 108, 10, 105, 10, 116, 
	10, 97, 10, 116, 10, 101, 10, 58, 
	10, 99, 10, 101, 10, 110, 10, 97, 
	10, 114, 10, 105, 10, 117, 32, 124, 
	9, 13, 10, 32, 92, 124, 9, 13, 
	10, 92, 124, 10, 92, 10, 32, 92, 
	124, 9, 13, -56, 10, 32, 34, 35, 
	37, 42, 64, 65, 67, 68, 69, 70, 
	83, 124, 9, 13, 10, 95, 10, 70, 
	10, 69, 10, 65, 10, 84, 10, 85, 
	10, 82, 10, 69, 10, 95, 10, 69, 
	10, 78, 10, 68, 10, 95, 10, 37, 
	10, 116, 10, 117, 10, 110, 10, 99, 
	-61, 10, -94, 10, 10, 110, 10, 100, 
	10, 97, 10, 99, 114, -60, 10, -125, 
	10, 10, 117, 10, 110, 10, 99, -56, 
	10, -101, 10, 10, 105, 10, 111, 10, 
	110, 10, 97, 10, 108, 10, 105, 10, 
	116, 10, 97, 10, 116, 10, 101, 10, 
	58, 10, 99, 10, 101, 10, 110, 10, 
	97, 10, 114, 10, 105, 10, 117, 10, 
	58, 108, 10, 32, 10, 100, 10, 101, 
	10, 32, -59, 10, -97, 10, 10, 97, 
	10, 98, 10, 108, 10, 111, 10, 110, 
	-69, -65, 0
};

static const char _lexer_single_lengths[] = {
	0, 16, 1, 1, 1, 1, 2, 15, 
	1, 1, 2, 3, 3, 3, 3, 3, 
	2, 2, 2, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 3, 5, 3, 1, 1, 1, 
	1, 2, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 12, 
	2, 2, 2, 15, 1, 2, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 5, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 9, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 3, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 1, 
	1, 1, 1, 1, 1, 1, 2, 1, 
	1, 12, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 3, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 12, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 3, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 4, 3, 2, 
	4, 15, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 3, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 1, 
	1, 0
};

static const char _lexer_range_lengths[] = {
	0, 1, 0, 0, 0, 0, 0, 1, 
	0, 0, 1, 1, 1, 1, 1, 1, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 1, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 1, 0, 0, 0, 0, 
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
	0, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 1, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 1, 1, 0, 0, 
	1, 1, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0
};

static const short _lexer_index_offsets[] = {
	0, 0, 18, 20, 22, 24, 26, 29, 
	46, 48, 50, 54, 59, 64, 69, 74, 
	79, 83, 87, 90, 92, 94, 96, 98, 
	100, 102, 104, 106, 108, 110, 112, 114, 
	116, 118, 120, 125, 132, 137, 139, 141, 
	143, 145, 148, 150, 152, 154, 156, 158, 
	160, 162, 164, 166, 168, 170, 172, 174, 
	188, 191, 194, 197, 214, 216, 219, 221, 
	223, 225, 227, 229, 231, 233, 235, 237, 
	239, 241, 243, 245, 252, 255, 258, 261, 
	264, 267, 270, 273, 276, 279, 282, 285, 
	288, 291, 294, 297, 300, 302, 304, 306, 
	308, 310, 312, 314, 316, 318, 320, 322, 
	324, 326, 328, 330, 332, 334, 336, 347, 
	350, 353, 356, 359, 362, 365, 368, 371, 
	374, 377, 380, 383, 386, 389, 392, 395, 
	398, 401, 404, 407, 410, 413, 416, 419, 
	422, 425, 428, 431, 434, 437, 440, 443, 
	446, 449, 452, 455, 458, 461, 464, 467, 
	470, 473, 476, 479, 482, 485, 488, 491, 
	494, 497, 500, 503, 507, 510, 513, 516, 
	519, 522, 525, 528, 531, 534, 537, 540, 
	542, 544, 546, 548, 550, 552, 554, 557, 
	559, 561, 575, 578, 581, 584, 587, 590, 
	593, 596, 599, 602, 605, 608, 611, 614, 
	617, 620, 623, 626, 629, 632, 635, 638, 
	642, 645, 648, 651, 654, 657, 660, 663, 
	666, 669, 672, 675, 678, 682, 685, 688, 
	691, 694, 697, 700, 703, 706, 709, 712, 
	715, 718, 721, 724, 727, 730, 733, 736, 
	739, 742, 745, 748, 751, 754, 758, 761, 
	764, 767, 770, 773, 776, 779, 782, 785, 
	788, 791, 793, 795, 797, 799, 801, 803, 
	805, 807, 809, 811, 813, 815, 817, 819, 
	833, 836, 839, 842, 845, 848, 851, 854, 
	857, 860, 863, 866, 869, 872, 875, 878, 
	881, 884, 887, 890, 893, 896, 899, 902, 
	905, 908, 911, 915, 918, 921, 924, 927, 
	930, 933, 936, 939, 942, 945, 948, 951, 
	954, 957, 960, 963, 966, 969, 972, 975, 
	978, 981, 984, 987, 990, 994, 1000, 1004, 
	1007, 1013, 1030, 1033, 1036, 1039, 1042, 1045, 
	1048, 1051, 1054, 1057, 1060, 1063, 1066, 1069, 
	1072, 1075, 1078, 1081, 1084, 1087, 1090, 1093, 
	1096, 1099, 1103, 1106, 1109, 1112, 1115, 1118, 
	1121, 1124, 1127, 1130, 1133, 1136, 1139, 1142, 
	1145, 1148, 1151, 1154, 1157, 1160, 1163, 1166, 
	1169, 1172, 1175, 1178, 1182, 1185, 1188, 1191, 
	1194, 1197, 1200, 1203, 1206, 1209, 1212, 1215, 
	1217, 1219
};

static const short _lexer_trans_targs[] = {
	2, 391, 7, 7, 8, 18, 20, 4, 
	34, 37, 41, 60, 64, 92, 175, 324, 
	7, 0, 3, 0, 4, 0, 5, 0, 
	0, 6, 7, 19, 6, 2, 7, 7, 
	8, 18, 20, 4, 34, 37, 41, 60, 
	64, 92, 175, 324, 7, 0, 9, 0, 
	10, 0, 11, 10, 10, 0, 12, 12, 
	13, 12, 12, 12, 12, 13, 12, 12, 
	12, 12, 14, 12, 12, 12, 12, 15, 
	12, 12, 7, 16, 17, 16, 0, 7, 
	16, 16, 0, 7, 16, 16, 0, 7, 
	19, 18, 7, 0, 21, 0, 22, 0, 
	23, 0, 24, 0, 25, 0, 26, 0, 
	27, 0, 28, 0, 29, 0, 30, 0, 
	31, 0, 32, 0, 33, 0, 393, 0, 
	0, 0, 0, 0, 35, 36, 7, 36, 
	36, 34, 35, 35, 7, 36, 34, 36, 
	0, 38, 0, 39, 0, 40, 0, 3, 
	0, 42, 45, 0, 43, 0, 44, 0, 
	4, 0, 46, 0, 47, 0, 48, 0, 
	49, 0, 50, 0, 51, 0, 52, 0, 
	53, 0, 55, 54, 55, 54, 56, 55, 
	55, 7, 330, 58, 7, 344, 348, 352, 
	356, 372, 55, 54, 57, 55, 54, 55, 
	58, 54, 55, 59, 54, 2, 7, 7, 
	8, 18, 20, 4, 34, 37, 41, 60, 
	64, 92, 175, 324, 7, 0, 61, 0, 
	62, 4, 0, 63, 0, 4, 0, 65, 
	0, 66, 0, 67, 0, 68, 0, 69, 
	0, 70, 0, 71, 0, 72, 0, 73, 
	0, 75, 74, 75, 74, 75, 75, 7, 
	76, 7, 75, 74, 75, 77, 74, 75, 
	78, 74, 75, 79, 74, 80, 75, 74, 
	81, 75, 74, 75, 82, 74, 75, 83, 
	74, 75, 84, 74, 75, 85, 74, 75, 
	86, 74, 75, 87, 74, 75, 88, 74, 
	75, 89, 74, 75, 90, 74, 75, 91, 
	74, 75, 59, 74, 93, 0, 94, 0, 
	95, 0, 96, 0, 97, 0, 98, 0, 
	99, 0, 100, 0, 101, 0, 102, 0, 
	103, 0, 104, 0, 105, 0, 106, 0, 
	107, 0, 108, 0, 110, 109, 110, 109, 
	110, 110, 7, 111, 7, 125, 134, 142, 
	156, 110, 109, 110, 112, 109, 110, 113, 
	109, 110, 114, 109, 110, 115, 109, 110, 
	116, 109, 110, 117, 109, 110, 118, 109, 
	110, 119, 109, 110, 120, 109, 110, 121, 
	109, 110, 122, 109, 110, 123, 109, 110, 
	124, 109, 110, 7, 109, 110, 126, 109, 
	110, 127, 109, 110, 128, 109, 110, 129, 
	109, 130, 110, 109, 131, 110, 109, 110, 
	132, 109, 110, 133, 109, 110, 59, 109, 
	110, 135, 109, 110, 136, 109, 110, 137, 
	109, 110, 138, 109, 110, 139, 109, 110, 
	140, 109, 110, 141, 109, 110, 133, 109, 
	110, 143, 109, 110, 144, 109, 110, 145, 
	109, 146, 110, 109, 147, 110, 109, 110, 
	148, 109, 110, 149, 109, 110, 150, 109, 
	110, 151, 109, 110, 152, 109, 110, 153, 
	109, 110, 154, 109, 110, 155, 109, 110, 
	141, 109, 110, 157, 109, 110, 158, 109, 
	110, 159, 109, 110, 160, 109, 110, 161, 
	109, 110, 162, 109, 110, 163, 109, 110, 
	59, 164, 109, 110, 165, 109, 110, 166, 
	109, 110, 167, 109, 110, 168, 109, 169, 
	110, 109, 170, 110, 109, 110, 171, 109, 
	110, 172, 109, 110, 173, 109, 110, 174, 
	109, 110, 133, 109, 176, 0, 177, 0, 
	178, 0, 179, 0, 180, 0, 181, 0, 
	182, 0, 183, 257, 0, 185, 184, 185, 
	184, 186, 185, 185, 7, 189, 188, 7, 
	203, 207, 219, 223, 238, 185, 184, 187, 
	185, 184, 185, 188, 184, 185, 59, 184, 
	185, 190, 184, 185, 191, 184, 185, 192, 
	184, 185, 193, 184, 185, 194, 184, 185, 
	195, 184, 185, 196, 184, 185, 197, 184, 
	185, 198, 184, 185, 199, 184, 185, 200, 
	184, 185, 201, 184, 185, 202, 184, 185, 
	7, 184, 185, 204, 184, 185, 205, 184, 
	185, 206, 184, 185, 187, 184, 208, 185, 
	211, 184, 209, 185, 184, 185, 210, 184, 
	185, 188, 184, 185, 212, 184, 185, 213, 
	184, 185, 214, 184, 215, 185, 184, 216, 
	185, 184, 185, 217, 184, 185, 218, 184, 
	185, 59, 184, 185, 220, 184, 185, 221, 
	188, 184, 222, 185, 184, 188, 185, 184, 
	185, 224, 184, 185, 225, 184, 185, 226, 
	184, 227, 185, 184, 228, 185, 184, 185, 
	229, 184, 185, 230, 184, 185, 231, 184, 
	185, 232, 184, 185, 233, 184, 185, 234, 
	184, 185, 235, 184, 185, 236, 184, 185, 
	237, 184, 185, 218, 184, 185, 239, 184, 
	185, 240, 184, 185, 241, 184, 185, 242, 
	184, 185, 243, 184, 185, 244, 184, 185, 
	245, 184, 185, 59, 246, 184, 185, 247, 
	184, 185, 248, 184, 185, 249, 184, 185, 
	250, 184, 251, 185, 184, 252, 185, 184, 
	185, 253, 184, 185, 254, 184, 185, 255, 
	184, 185, 256, 184, 185, 218, 184, 258, 
	0, 259, 0, 260, 0, 261, 0, 262, 
	0, 263, 0, 264, 0, 265, 0, 266, 
	0, 267, 0, 268, 0, 269, 0, 271, 
	270, 271, 270, 272, 271, 271, 7, 275, 
	274, 7, 289, 293, 297, 301, 317, 271, 
	270, 273, 271, 270, 271, 274, 270, 271, 
	59, 270, 271, 276, 270, 271, 277, 270, 
	271, 278, 270, 271, 279, 270, 271, 280, 
	270, 271, 281, 270, 271, 282, 270, 271, 
	283, 270, 271, 284, 270, 271, 285, 270, 
	271, 286, 270, 271, 287, 270, 271, 288, 
	270, 271, 7, 270, 271, 290, 270, 271, 
	291, 270, 271, 292, 270, 271, 273, 270, 
	294, 271, 270, 295, 271, 270, 271, 296, 
	270, 271, 274, 270, 271, 298, 270, 271, 
	299, 274, 270, 300, 271, 270, 274, 271, 
	270, 271, 302, 270, 271, 303, 270, 271, 
	304, 270, 305, 271, 270, 306, 271, 270, 
	271, 307, 270, 271, 308, 270, 271, 309, 
	270, 271, 310, 270, 271, 311, 270, 271, 
	312, 270, 271, 313, 270, 271, 314, 270, 
	271, 315, 270, 271, 316, 270, 271, 59, 
	270, 271, 318, 270, 271, 319, 270, 271, 
	320, 270, 271, 321, 270, 271, 322, 270, 
	271, 323, 270, 271, 316, 270, 324, 325, 
	324, 0, 329, 328, 327, 325, 328, 326, 
	0, 327, 325, 326, 0, 327, 326, 329, 
	328, 327, 325, 328, 326, 2, 329, 329, 
	8, 18, 20, 4, 34, 37, 41, 60, 
	64, 92, 175, 324, 329, 0, 55, 331, 
	54, 55, 332, 54, 55, 333, 54, 55, 
	334, 54, 55, 335, 54, 55, 336, 54, 
	55, 337, 54, 55, 338, 54, 55, 339, 
	54, 55, 340, 54, 55, 341, 54, 55, 
	342, 54, 55, 343, 54, 55, 7, 54, 
	55, 345, 54, 55, 346, 54, 55, 347, 
	54, 55, 57, 54, 349, 55, 54, 350, 
	55, 54, 55, 351, 54, 55, 58, 54, 
	55, 353, 54, 55, 354, 58, 54, 355, 
	55, 54, 58, 55, 54, 55, 357, 54, 
	55, 358, 54, 55, 359, 54, 360, 55, 
	54, 361, 55, 54, 55, 362, 54, 55, 
	363, 54, 55, 364, 54, 55, 365, 54, 
	55, 366, 54, 55, 367, 54, 55, 368, 
	54, 55, 369, 54, 55, 370, 54, 55, 
	371, 54, 55, 59, 54, 55, 373, 54, 
	55, 374, 54, 55, 375, 54, 55, 376, 
	54, 55, 377, 54, 55, 378, 54, 55, 
	379, 54, 55, 59, 380, 54, 55, 381, 
	54, 55, 382, 54, 55, 383, 54, 55, 
	384, 54, 385, 55, 54, 386, 55, 54, 
	55, 387, 54, 55, 388, 54, 55, 389, 
	54, 55, 390, 54, 55, 371, 54, 392, 
	0, 7, 0, 0, 0
};

static const char _lexer_trans_actions[] = {
	25, 0, 47, 0, 5, 1, 0, 25, 
	1, 25, 25, 25, 25, 25, 25, 31, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	39, 50, 99, 19, 0, 25, 47, 0, 
	5, 1, 0, 25, 1, 25, 25, 25, 
	25, 25, 25, 31, 0, 39, 0, 39, 
	0, 39, 47, 0, 0, 39, 119, 41, 
	41, 41, 3, 111, 29, 29, 29, 0, 
	111, 29, 29, 29, 0, 111, 29, 0, 
	29, 0, 95, 7, 0, 7, 39, 47, 
	0, 0, 39, 95, 7, 7, 39, 103, 
	21, 0, 47, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	39, 39, 39, 39, 0, 23, 107, 23, 
	23, 44, 23, 0, 47, 0, 1, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 124, 50, 47, 0, 77, 47, 
	0, 65, 29, 77, 65, 77, 77, 77, 
	77, 77, 0, 0, 0, 47, 0, 47, 
	0, 0, 47, 11, 0, 56, 115, 27, 
	53, 50, 27, 56, 50, 56, 56, 56, 
	56, 56, 56, 59, 27, 39, 0, 39, 
	0, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 124, 50, 47, 0, 47, 0, 74, 
	77, 74, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 47, 0, 
	0, 47, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 17, 0, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 124, 50, 47, 0, 
	47, 0, 62, 29, 62, 77, 77, 77, 
	77, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 9, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 0, 47, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 9, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 0, 47, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	9, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 0, 
	47, 0, 0, 47, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 0, 39, 124, 50, 47, 
	0, 77, 47, 0, 68, 29, 77, 68, 
	77, 77, 77, 77, 77, 0, 0, 0, 
	47, 0, 47, 0, 0, 47, 13, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	13, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 0, 47, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 47, 0, 0, 47, 0, 0, 
	47, 13, 0, 47, 0, 0, 47, 0, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 0, 47, 0, 0, 47, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 13, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 124, 
	50, 47, 0, 77, 47, 0, 71, 29, 
	77, 71, 77, 77, 77, 77, 77, 0, 
	0, 0, 47, 0, 47, 0, 0, 47, 
	15, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 15, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	0, 47, 0, 0, 47, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 0, 47, 0, 0, 47, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 15, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 0, 
	0, 39, 47, 33, 33, 80, 33, 33, 
	39, 0, 35, 0, 39, 0, 0, 47, 
	0, 0, 35, 0, 0, 89, 47, 0, 
	86, 83, 37, 89, 83, 89, 89, 89, 
	89, 89, 89, 92, 0, 39, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 11, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 0, 
	47, 0, 0, 47, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 11, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 11, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 0, 
	39, 0, 39, 0, 0
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
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39, 39, 39, 39, 39, 39, 39, 
	39, 39
};

static const int lexer_start = 1;
static const int lexer_first_final = 393;
static const int lexer_error = 0;

static const int lexer_en_main = 1;


#line 243 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"

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
    
    
#line 990 "ext/gherkin_lexer_ro_ro/gherkin_lexer_ro_ro.c"
	{
	cs = lexer_start;
	}

#line 425 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
    
#line 997 "ext/gherkin_lexer_ro_ro/gherkin_lexer_ro_ro.c"
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
#line 86 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
		MARK(content_start, p);
    lexer->current_line = lexer->line_number;
  }
	break;
	case 1:
#line 91 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    MARK(content_start, p);
  }
	break;
	case 2:
#line 95 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    lexer->current_line = lexer->line_number;
    lexer->start_col = p - data - lexer->last_newline;
  }
	break;
	case 3:
#line 100 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    int len = LEN(content_start, PTR_TO(final_newline));

    if (len < 0) len = 0;

    store_pystring_content(listener, lexer->start_col, PTR_TO(content_start), len, lexer->current_line);
  }
	break;
	case 4:
#line 108 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_KW_END_CON(feature);
  }
	break;
	case 5:
#line 112 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_KW_END_CON(background);
  }
	break;
	case 6:
#line 116 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_KW_END_CON(scenario);
  }
	break;
	case 7:
#line 120 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_KW_END_CON(scenario_outline);
  }
	break;
	case 8:
#line 124 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_KW_END_CON(examples);
  }
	break;
	case 9:
#line 128 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    store_kw_con(listener, "step",
      PTR_TO(keyword_start), LEN(keyword_start, PTR_TO(keyword_end)),
      PTR_TO(content_start), LEN(content_start, p), 
      lexer->current_line);
  }
	break;
	case 10:
#line 135 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_ATTR(comment);
    lexer->mark = 0;
  }
	break;
	case 11:
#line 140 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    STORE_ATTR(tag);
    lexer->mark = 0;
  }
	break;
	case 12:
#line 145 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    lexer->line_number += 1;
    MARK(final_newline, p);
  }
	break;
	case 13:
#line 150 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    MARK(last_newline, p + 1);
  }
	break;
	case 14:
#line 154 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    if (lexer->mark == 0) {
      MARK(mark, p);
    }
  }
	break;
	case 15:
#line 160 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    MARK(keyword_end, p);
    MARK(keyword_start, PTR_TO(mark));
    MARK(content_start, p + 1);
    lexer->mark = 0;
  }
	break;
	case 16:
#line 167 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    MARK(content_end, p);
  }
	break;
	case 17:
#line 171 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    p = p - 1;
    lexer->current_line = lexer->line_number;
    current_row = rb_ary_new();
  }
	break;
	case 18:
#line 177 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
		MARK(content_start, p);
  }
	break;
	case 19:
#line 181 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
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
#line 192 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
	{
    rb_funcall(listener, rb_intern("row"), 2, current_row, INT2FIX(lexer->current_line));
  }
	break;
	case 21:
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
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
#line 1265 "ext/gherkin_lexer_ro_ro/gherkin_lexer_ro_ro.c"
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
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"
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
#line 1324 "ext/gherkin_lexer_ro_ro/gherkin_lexer_ro_ro.c"
		}
	}
	}

	_out: {}
	}

#line 426 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro_ro.c.rl"

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

void Init_gherkin_lexer_ro_ro()
{
  mGherkin = rb_define_module("Gherkin");
  rb_eGherkinLexingError = rb_const_get(mGherkin, rb_intern("LexingError"));

  mCLexer = rb_define_module_under(mGherkin, "CLexer");
  cI18nLexer = rb_define_class_under(mCLexer, "Ro_ro", rb_cObject);
  rb_define_alloc_func(cI18nLexer, CLexer_alloc);
  rb_define_method(cI18nLexer, "initialize", CLexer_init, 1);
  rb_define_method(cI18nLexer, "scan", CLexer_scan, 1);
}

