
#line 1 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
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


#line 239 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"


/** Data **/

#line 92 "ext/gherkin_lexer_ro/gherkin_lexer_ro.c"
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
	41, 46, 51, 56, 61, 66, 70, 74, 
	76, 77, 78, 79, 80, 81, 82, 83, 
	84, 85, 86, 87, 88, 89, 90, 91, 
	92, 93, 95, 100, 107, 112, 113, 114, 
	115, 116, 117, 119, 120, 121, 122, 123, 
	124, 125, 126, 127, 128, 129, 130, 143, 
	145, 147, 149, 151, 153, 155, 157, 159, 
	161, 163, 165, 167, 169, 171, 173, 189, 
	190, 192, 193, 194, 195, 196, 197, 198, 
	199, 200, 201, 202, 203, 204, 211, 213, 
	215, 217, 219, 221, 223, 225, 227, 229, 
	231, 233, 235, 237, 239, 241, 242, 243, 
	244, 245, 246, 247, 248, 249, 250, 251, 
	252, 253, 254, 255, 256, 257, 258, 269, 
	271, 273, 275, 277, 279, 281, 283, 285, 
	287, 289, 291, 293, 295, 297, 299, 301, 
	303, 305, 307, 309, 311, 313, 315, 317, 
	319, 321, 323, 325, 327, 329, 331, 333, 
	335, 337, 339, 341, 343, 345, 347, 349, 
	351, 353, 355, 357, 359, 361, 363, 365, 
	367, 369, 372, 374, 376, 378, 380, 382, 
	384, 386, 388, 390, 392, 394, 395, 396, 
	397, 398, 399, 400, 402, 403, 404, 417, 
	419, 421, 423, 425, 427, 429, 431, 433, 
	435, 437, 439, 441, 443, 445, 447, 449, 
	451, 453, 455, 457, 460, 462, 464, 466, 
	468, 470, 472, 474, 476, 478, 480, 483, 
	485, 487, 489, 491, 493, 495, 497, 499, 
	501, 503, 505, 507, 509, 511, 513, 516, 
	518, 520, 522, 524, 526, 528, 531, 533, 
	535, 537, 539, 541, 543, 545, 547, 549, 
	551, 552, 553, 554, 555, 556, 557, 558, 
	559, 560, 561, 562, 563, 564, 577, 579, 
	581, 583, 585, 587, 589, 591, 593, 595, 
	597, 599, 601, 603, 605, 607, 609, 611, 
	613, 615, 617, 619, 621, 623, 625, 628, 
	630, 632, 634, 636, 638, 640, 642, 644, 
	646, 648, 650, 652, 654, 656, 658, 660, 
	663, 665, 667, 669, 671, 673, 675, 679, 
	685, 688, 690, 696, 712, 714, 716, 718, 
	720, 722, 724, 726, 728, 730, 733, 735, 
	737, 739, 741, 743, 745, 747, 749, 751, 
	753, 755, 757, 759, 761, 763, 765, 768, 
	770, 772, 774, 776, 778, 780, 783, 785, 
	787, 789, 791, 793, 795, 797, 799, 801, 
	803
};

static const char _lexer_trans_keys[] = {
	-17, 10, 32, 34, 35, 37, 42, 64, 
	65, 67, 68, 69, 70, 83, 124, 9, 
	13, -69, -65, 10, 32, 34, 35, 37, 
	42, 64, 65, 67, 68, 69, 70, 83, 
	124, 9, 13, 34, 34, 10, 32, 9, 
	13, 10, 32, 34, 9, 13, 10, 32, 
	34, 9, 13, 10, 32, 34, 9, 13, 
	10, 32, 34, 9, 13, 10, 32, 34, 
	9, 13, 10, 32, 9, 13, 10, 32, 
	9, 13, 10, 13, 10, 95, 70, 69, 
	65, 84, 85, 82, 69, 95, 69, 78, 
	68, 95, 37, 32, 10, 10, 13, 13, 
	32, 64, 9, 10, 9, 10, 13, 32, 
	64, 11, 12, 10, 32, 64, 9, 13, 
	116, 117, 110, 99, 105, 97, 111, 110, 
	100, 110, 100, 105, 116, 105, 105, 58, 
	10, 10, 10, 32, 35, 37, 42, 64, 
	65, 67, 68, 70, 83, 9, 13, 10, 
	95, 10, 70, 10, 69, 10, 65, 10, 
	84, 10, 85, 10, 82, 10, 69, 10, 
	95, 10, 69, 10, 78, 10, 68, 10, 
	95, 10, 37, 10, 32, 10, 32, 34, 
	35, 37, 42, 64, 65, 67, 68, 69, 
	70, 83, 124, 9, 13, 97, 99, 114, 
	97, 120, 101, 109, 112, 108, 101, 108, 
	101, 58, 10, 10, 10, 32, 35, 70, 
	124, 9, 13, 10, 117, 10, 110, 10, 
	99, 10, 116, 10, 105, 10, 111, 10, 
	110, 10, 97, 10, 108, 10, 105, 10, 
	116, 10, 97, 10, 116, 10, 101, 10, 
	58, 117, 110, 99, 116, 105, 111, 110, 
	97, 108, 105, 116, 97, 116, 101, 58, 
	10, 10, 10, 32, 35, 37, 64, 67, 
	69, 70, 83, 9, 13, 10, 95, 10, 
	70, 10, 69, 10, 65, 10, 84, 10, 
	85, 10, 82, 10, 69, 10, 95, 10, 
	69, 10, 78, 10, 68, 10, 95, 10, 
	37, 10, 111, 10, 110, 10, 100, 10, 
	105, 10, 116, 10, 105, 10, 105, 10, 
	58, 10, 120, 10, 101, 10, 109, 10, 
	112, 10, 108, 10, 101, 10, 108, 10, 
	101, 10, 117, 10, 110, 10, 99, 10, 
	116, 10, 105, 10, 111, 10, 110, 10, 
	97, 10, 108, 10, 105, 10, 116, 10, 
	97, 10, 116, 10, 99, 10, 101, 10, 
	110, 10, 97, 10, 114, 10, 105, 10, 
	117, 10, 58, 108, 10, 32, 10, 100, 
	10, 101, 10, 32, 10, 115, 10, 97, 
	10, 98, 10, 108, 10, 111, 10, 110, 
	99, 105, 101, 110, 97, 114, 105, 117, 
	58, 108, 10, 10, 10, 32, 35, 37, 
	42, 64, 65, 67, 68, 70, 83, 9, 
	13, 10, 95, 10, 70, 10, 69, 10, 
	65, 10, 84, 10, 85, 10, 82, 10, 
	69, 10, 95, 10, 69, 10, 78, 10, 
	68, 10, 95, 10, 37, 10, 32, 10, 
	116, 10, 117, 10, 110, 10, 99, 10, 
	105, 10, 97, 111, 10, 110, 10, 100, 
	10, 110, 10, 100, 10, 105, 10, 116, 
	10, 105, 10, 105, 10, 58, 10, 97, 
	10, 99, 114, 10, 97, 10, 117, 10, 
	110, 10, 99, 10, 116, 10, 105, 10, 
	111, 10, 110, 10, 97, 10, 108, 10, 
	105, 10, 116, 10, 97, 10, 116, 10, 
	101, 10, 99, 105, 10, 101, 10, 110, 
	10, 97, 10, 114, 10, 105, 10, 117, 
	10, 58, 108, 10, 32, 10, 100, 10, 
	101, 10, 32, 10, 115, 10, 97, 10, 
	98, 10, 108, 10, 111, 10, 110, 32, 
	100, 101, 32, 115, 97, 98, 108, 111, 
	110, 58, 10, 10, 10, 32, 35, 37, 
	42, 64, 65, 67, 68, 70, 83, 9, 
	13, 10, 95, 10, 70, 10, 69, 10, 
	65, 10, 84, 10, 85, 10, 82, 10, 
	69, 10, 95, 10, 69, 10, 78, 10, 
	68, 10, 95, 10, 37, 10, 32, 10, 
	116, 10, 117, 10, 110, 10, 99, 10, 
	105, 10, 97, 10, 110, 10, 100, 10, 
	97, 10, 99, 114, 10, 97, 10, 117, 
	10, 110, 10, 99, 10, 116, 10, 105, 
	10, 111, 10, 110, 10, 97, 10, 108, 
	10, 105, 10, 116, 10, 97, 10, 116, 
	10, 101, 10, 58, 10, 99, 105, 10, 
	101, 10, 110, 10, 97, 10, 114, 10, 
	105, 10, 117, 32, 124, 9, 13, 10, 
	32, 92, 124, 9, 13, 10, 92, 124, 
	10, 92, 10, 32, 92, 124, 9, 13, 
	10, 32, 34, 35, 37, 42, 64, 65, 
	67, 68, 69, 70, 83, 124, 9, 13, 
	10, 116, 10, 117, 10, 110, 10, 99, 
	10, 105, 10, 97, 10, 110, 10, 100, 
	10, 97, 10, 99, 114, 10, 97, 10, 
	117, 10, 110, 10, 99, 10, 116, 10, 
	105, 10, 111, 10, 110, 10, 97, 10, 
	108, 10, 105, 10, 116, 10, 97, 10, 
	116, 10, 101, 10, 58, 10, 99, 105, 
	10, 101, 10, 110, 10, 97, 10, 114, 
	10, 105, 10, 117, 10, 58, 108, 10, 
	32, 10, 100, 10, 101, 10, 32, 10, 
	115, 10, 97, 10, 98, 10, 108, 10, 
	111, 10, 110, 0
};

static const char _lexer_single_lengths[] = {
	0, 15, 1, 1, 14, 1, 1, 2, 
	3, 3, 3, 3, 3, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 2, 3, 5, 3, 1, 1, 1, 
	1, 1, 2, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 11, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 14, 1, 
	2, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 5, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 1, 9, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 3, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 1, 1, 1, 
	1, 1, 1, 2, 1, 1, 11, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 3, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	1, 1, 1, 1, 1, 1, 1, 1, 
	1, 1, 1, 1, 1, 11, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 3, 
	2, 2, 2, 2, 2, 2, 2, 4, 
	3, 2, 4, 14, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	2, 2, 2, 2, 2, 2, 3, 2, 
	2, 2, 2, 2, 2, 3, 2, 2, 
	2, 2, 2, 2, 2, 2, 2, 2, 
	0
};

static const char _lexer_range_lengths[] = {
	0, 1, 0, 0, 1, 0, 0, 1, 
	1, 1, 1, 1, 1, 1, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 1, 1, 1, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 0, 1, 0, 
	0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0, 0, 0, 0, 1, 0, 0, 
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
	0, 0, 0, 0, 0, 1, 0, 0, 
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
	0
};

static const short _lexer_index_offsets[] = {
	0, 0, 17, 19, 21, 37, 39, 41, 
	45, 50, 55, 60, 65, 70, 74, 78, 
	81, 83, 85, 87, 89, 91, 93, 95, 
	97, 99, 101, 103, 105, 107, 109, 111, 
	113, 115, 118, 123, 130, 135, 137, 139, 
	141, 143, 145, 148, 150, 152, 154, 156, 
	158, 160, 162, 164, 166, 168, 170, 183, 
	186, 189, 192, 195, 198, 201, 204, 207, 
	210, 213, 216, 219, 222, 225, 228, 244, 
	246, 249, 251, 253, 255, 257, 259, 261, 
	263, 265, 267, 269, 271, 273, 280, 283, 
	286, 289, 292, 295, 298, 301, 304, 307, 
	310, 313, 316, 319, 322, 325, 327, 329, 
	331, 333, 335, 337, 339, 341, 343, 345, 
	347, 349, 351, 353, 355, 357, 359, 370, 
	373, 376, 379, 382, 385, 388, 391, 394, 
	397, 400, 403, 406, 409, 412, 415, 418, 
	421, 424, 427, 430, 433, 436, 439, 442, 
	445, 448, 451, 454, 457, 460, 463, 466, 
	469, 472, 475, 478, 481, 484, 487, 490, 
	493, 496, 499, 502, 505, 508, 511, 514, 
	517, 520, 524, 527, 530, 533, 536, 539, 
	542, 545, 548, 551, 554, 557, 559, 561, 
	563, 565, 567, 569, 572, 574, 576, 589, 
	592, 595, 598, 601, 604, 607, 610, 613, 
	616, 619, 622, 625, 628, 631, 634, 637, 
	640, 643, 646, 649, 653, 656, 659, 662, 
	665, 668, 671, 674, 677, 680, 683, 687, 
	690, 693, 696, 699, 702, 705, 708, 711, 
	714, 717, 720, 723, 726, 729, 732, 736, 
	739, 742, 745, 748, 751, 754, 758, 761, 
	764, 767, 770, 773, 776, 779, 782, 785, 
	788, 790, 792, 794, 796, 798, 800, 802, 
	804, 806, 808, 810, 812, 814, 827, 830, 
	833, 836, 839, 842, 845, 848, 851, 854, 
	857, 860, 863, 866, 869, 872, 875, 878, 
	881, 884, 887, 890, 893, 896, 899, 903, 
	906, 909, 912, 915, 918, 921, 924, 927, 
	930, 933, 936, 939, 942, 945, 948, 951, 
	955, 958, 961, 964, 967, 970, 973, 977, 
	983, 987, 990, 996, 1012, 1015, 1018, 1021, 
	1024, 1027, 1030, 1033, 1036, 1039, 1043, 1046, 
	1049, 1052, 1055, 1058, 1061, 1064, 1067, 1070, 
	1073, 1076, 1079, 1082, 1085, 1088, 1091, 1095, 
	1098, 1101, 1104, 1107, 1110, 1113, 1117, 1120, 
	1123, 1126, 1129, 1132, 1135, 1138, 1141, 1144, 
	1147
};

static const short _lexer_trans_targs[] = {
	2, 4, 4, 5, 15, 17, 31, 34, 
	37, 42, 71, 74, 101, 180, 318, 4, 
	0, 3, 0, 4, 0, 4, 4, 5, 
	15, 17, 31, 34, 37, 42, 71, 74, 
	101, 180, 318, 4, 0, 6, 0, 7, 
	0, 8, 7, 7, 0, 9, 9, 10, 
	9, 9, 9, 9, 10, 9, 9, 9, 
	9, 11, 9, 9, 9, 9, 12, 9, 
	9, 4, 13, 14, 13, 0, 4, 13, 
	13, 0, 4, 13, 13, 0, 4, 16, 
	15, 4, 0, 18, 0, 19, 0, 20, 
	0, 21, 0, 22, 0, 23, 0, 24, 
	0, 25, 0, 26, 0, 27, 0, 28, 
	0, 29, 0, 30, 0, 368, 0, 32, 
	0, 0, 33, 4, 16, 33, 0, 0, 
	0, 0, 35, 36, 4, 36, 36, 34, 
	35, 35, 4, 36, 34, 36, 0, 38, 
	0, 39, 0, 40, 0, 41, 0, 31, 
	0, 43, 45, 0, 44, 0, 31, 0, 
	46, 0, 47, 0, 48, 0, 49, 0, 
	50, 0, 51, 0, 52, 0, 54, 53, 
	54, 53, 54, 54, 4, 55, 69, 4, 
	324, 329, 332, 335, 350, 54, 53, 54, 
	56, 53, 54, 57, 53, 54, 58, 53, 
	54, 59, 53, 54, 60, 53, 54, 61, 
	53, 54, 62, 53, 54, 63, 53, 54, 
	64, 53, 54, 65, 53, 54, 66, 53, 
	54, 67, 53, 54, 68, 53, 54, 4, 
	53, 54, 70, 53, 4, 4, 5, 15, 
	17, 31, 34, 37, 42, 71, 74, 101, 
	180, 318, 4, 0, 72, 0, 73, 31, 
	0, 31, 0, 75, 0, 76, 0, 77, 
	0, 78, 0, 79, 0, 80, 0, 81, 
	0, 82, 0, 83, 0, 85, 84, 85, 
	84, 85, 85, 4, 86, 4, 85, 84, 
	85, 87, 84, 85, 88, 84, 85, 89, 
	84, 85, 90, 84, 85, 91, 84, 85, 
	92, 84, 85, 93, 84, 85, 94, 84, 
	85, 95, 84, 85, 96, 84, 85, 97, 
	84, 85, 98, 84, 85, 99, 84, 85, 
	100, 84, 85, 70, 84, 102, 0, 103, 
	0, 104, 0, 105, 0, 106, 0, 107, 
	0, 108, 0, 109, 0, 110, 0, 111, 
	0, 112, 0, 113, 0, 114, 0, 115, 
	0, 116, 0, 118, 117, 118, 117, 118, 
	118, 4, 119, 4, 133, 141, 149, 162, 
	118, 117, 118, 120, 117, 118, 121, 117, 
	118, 122, 117, 118, 123, 117, 118, 124, 
	117, 118, 125, 117, 118, 126, 117, 118, 
	127, 117, 118, 128, 117, 118, 129, 117, 
	118, 130, 117, 118, 131, 117, 118, 132, 
	117, 118, 4, 117, 118, 134, 117, 118, 
	135, 117, 118, 136, 117, 118, 137, 117, 
	118, 138, 117, 118, 139, 117, 118, 140, 
	117, 118, 70, 117, 118, 142, 117, 118, 
	143, 117, 118, 144, 117, 118, 145, 117, 
	118, 146, 117, 118, 147, 117, 118, 148, 
	117, 118, 140, 117, 118, 150, 117, 118, 
	151, 117, 118, 152, 117, 118, 153, 117, 
	118, 154, 117, 118, 155, 117, 118, 156, 
	117, 118, 157, 117, 118, 158, 117, 118, 
	159, 117, 118, 160, 117, 118, 161, 117, 
	118, 148, 117, 118, 163, 117, 118, 164, 
	117, 118, 165, 117, 118, 166, 117, 118, 
	167, 117, 118, 168, 117, 118, 169, 117, 
	118, 70, 170, 117, 118, 171, 117, 118, 
	172, 117, 118, 173, 117, 118, 174, 117, 
	118, 175, 117, 118, 176, 117, 118, 177, 
	117, 118, 178, 117, 118, 179, 117, 118, 
	140, 117, 181, 31, 0, 182, 0, 183, 
	0, 184, 0, 185, 0, 186, 0, 187, 
	0, 188, 256, 0, 190, 189, 190, 189, 
	190, 190, 4, 191, 205, 4, 206, 211, 
	221, 224, 238, 190, 189, 190, 192, 189, 
	190, 193, 189, 190, 194, 189, 190, 195, 
	189, 190, 196, 189, 190, 197, 189, 190, 
	198, 189, 190, 199, 189, 190, 200, 189, 
	190, 201, 189, 190, 202, 189, 190, 203, 
	189, 190, 204, 189, 190, 4, 189, 190, 
	70, 189, 190, 207, 189, 190, 208, 189, 
	190, 209, 189, 190, 210, 189, 190, 205, 
	189, 190, 212, 214, 189, 190, 213, 189, 
	190, 205, 189, 190, 215, 189, 190, 216, 
	189, 190, 217, 189, 190, 218, 189, 190, 
	219, 189, 190, 220, 189, 190, 70, 189, 
	190, 222, 189, 190, 223, 205, 189, 190, 
	205, 189, 190, 225, 189, 190, 226, 189, 
	190, 227, 189, 190, 228, 189, 190, 229, 
	189, 190, 230, 189, 190, 231, 189, 190, 
	232, 189, 190, 233, 189, 190, 234, 189, 
	190, 235, 189, 190, 236, 189, 190, 237, 
	189, 190, 220, 189, 190, 239, 205, 189, 
	190, 240, 189, 190, 241, 189, 190, 242, 
	189, 190, 243, 189, 190, 244, 189, 190, 
	245, 189, 190, 70, 246, 189, 190, 247, 
	189, 190, 248, 189, 190, 249, 189, 190, 
	250, 189, 190, 251, 189, 190, 252, 189, 
	190, 253, 189, 190, 254, 189, 190, 255, 
	189, 190, 220, 189, 257, 0, 258, 0, 
	259, 0, 260, 0, 261, 0, 262, 0, 
	263, 0, 264, 0, 265, 0, 266, 0, 
	267, 0, 269, 268, 269, 268, 269, 269, 
	4, 270, 284, 4, 285, 290, 293, 296, 
	311, 269, 268, 269, 271, 268, 269, 272, 
	268, 269, 273, 268, 269, 274, 268, 269, 
	275, 268, 269, 276, 268, 269, 277, 268, 
	269, 278, 268, 269, 279, 268, 269, 280, 
	268, 269, 281, 268, 269, 282, 268, 269, 
	283, 268, 269, 4, 268, 269, 70, 268, 
	269, 286, 268, 269, 287, 268, 269, 288, 
	268, 269, 289, 268, 269, 284, 268, 269, 
	291, 268, 269, 292, 268, 269, 284, 268, 
	269, 294, 268, 269, 295, 284, 268, 269, 
	284, 268, 269, 297, 268, 269, 298, 268, 
	269, 299, 268, 269, 300, 268, 269, 301, 
	268, 269, 302, 268, 269, 303, 268, 269, 
	304, 268, 269, 305, 268, 269, 306, 268, 
	269, 307, 268, 269, 308, 268, 269, 309, 
	268, 269, 310, 268, 269, 70, 268, 269, 
	312, 284, 268, 269, 313, 268, 269, 314, 
	268, 269, 315, 268, 269, 316, 268, 269, 
	317, 268, 269, 310, 268, 318, 319, 318, 
	0, 323, 322, 321, 319, 322, 320, 0, 
	321, 319, 320, 0, 321, 320, 323, 322, 
	321, 319, 322, 320, 323, 323, 5, 15, 
	17, 31, 34, 37, 42, 71, 74, 101, 
	180, 318, 323, 0, 54, 325, 53, 54, 
	326, 53, 54, 327, 53, 54, 328, 53, 
	54, 69, 53, 54, 330, 53, 54, 331, 
	53, 54, 69, 53, 54, 333, 53, 54, 
	334, 69, 53, 54, 69, 53, 54, 336, 
	53, 54, 337, 53, 54, 338, 53, 54, 
	339, 53, 54, 340, 53, 54, 341, 53, 
	54, 342, 53, 54, 343, 53, 54, 344, 
	53, 54, 345, 53, 54, 346, 53, 54, 
	347, 53, 54, 348, 53, 54, 349, 53, 
	54, 70, 53, 54, 351, 69, 53, 54, 
	352, 53, 54, 353, 53, 54, 354, 53, 
	54, 355, 53, 54, 356, 53, 54, 357, 
	53, 54, 70, 358, 53, 54, 359, 53, 
	54, 360, 53, 54, 361, 53, 54, 362, 
	53, 54, 363, 53, 54, 364, 53, 54, 
	365, 53, 54, 366, 53, 54, 367, 53, 
	54, 349, 53, 0, 0
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
	0, 95, 7, 0, 7, 39, 47, 0, 
	0, 39, 95, 7, 7, 39, 103, 21, 
	0, 47, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 39, 50, 99, 19, 0, 39, 39, 
	39, 39, 0, 23, 107, 23, 23, 44, 
	23, 0, 47, 0, 1, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 124, 50, 
	47, 0, 47, 0, 65, 29, 77, 65, 
	77, 77, 77, 77, 77, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 11, 
	0, 47, 11, 0, 115, 27, 53, 50, 
	27, 56, 50, 56, 56, 56, 56, 56, 
	56, 59, 27, 39, 0, 39, 0, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 124, 50, 47, 
	0, 47, 0, 74, 77, 74, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 17, 0, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 39, 124, 50, 47, 0, 47, 
	0, 62, 29, 62, 77, 77, 77, 77, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 9, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 9, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 9, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 0, 39, 0, 39, 0, 
	39, 0, 39, 0, 39, 0, 39, 0, 
	39, 0, 0, 39, 124, 50, 47, 0, 
	47, 0, 68, 29, 77, 68, 77, 77, 
	77, 77, 77, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 13, 0, 47, 
	13, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 13, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 13, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 0, 39, 0, 39, 0, 39, 
	0, 39, 124, 50, 47, 0, 47, 0, 
	71, 29, 77, 71, 77, 77, 77, 77, 
	77, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 15, 0, 47, 15, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 15, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 0, 0, 0, 
	39, 47, 33, 33, 80, 33, 33, 39, 
	0, 35, 0, 39, 0, 0, 47, 0, 
	0, 35, 0, 0, 47, 0, 86, 83, 
	37, 89, 83, 89, 89, 89, 89, 89, 
	89, 92, 0, 39, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 11, 0, 47, 0, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 11, 0, 0, 47, 0, 0, 
	47, 0, 0, 47, 0, 0, 47, 0, 
	0, 47, 0, 0, 47, 0, 0, 47, 
	0, 0, 47, 0, 0, 47, 0, 0, 
	47, 0, 0, 0, 0
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
	39
};

static const int lexer_start = 1;
static const int lexer_first_final = 368;
static const int lexer_error = 0;

static const int lexer_en_main = 1;


#line 243 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"

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
    
    
#line 951 "ext/gherkin_lexer_ro/gherkin_lexer_ro.c"
	{
	cs = lexer_start;
	}

#line 425 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
    
#line 958 "ext/gherkin_lexer_ro/gherkin_lexer_ro.c"
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
#line 86 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
		MARK(content_start, p);
    lexer->current_line = lexer->line_number;
  }
	break;
	case 1:
#line 91 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    MARK(content_start, p);
  }
	break;
	case 2:
#line 95 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    lexer->current_line = lexer->line_number;
    lexer->start_col = p - data - lexer->last_newline;
  }
	break;
	case 3:
#line 100 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    int len = LEN(content_start, PTR_TO(final_newline));

    if (len < 0) len = 0;

    store_pystring_content(listener, lexer->start_col, PTR_TO(content_start), len, lexer->current_line);
  }
	break;
	case 4:
#line 108 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_KW_END_CON(feature);
  }
	break;
	case 5:
#line 112 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_KW_END_CON(background);
  }
	break;
	case 6:
#line 116 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_KW_END_CON(scenario);
  }
	break;
	case 7:
#line 120 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_KW_END_CON(scenario_outline);
  }
	break;
	case 8:
#line 124 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_KW_END_CON(examples);
  }
	break;
	case 9:
#line 128 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    store_kw_con(listener, "step",
      PTR_TO(keyword_start), LEN(keyword_start, PTR_TO(keyword_end)),
      PTR_TO(content_start), LEN(content_start, p), 
      lexer->current_line);
  }
	break;
	case 10:
#line 135 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_ATTR(comment);
    lexer->mark = 0;
  }
	break;
	case 11:
#line 140 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    STORE_ATTR(tag);
    lexer->mark = 0;
  }
	break;
	case 12:
#line 145 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    lexer->line_number += 1;
    MARK(final_newline, p);
  }
	break;
	case 13:
#line 150 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    MARK(last_newline, p + 1);
  }
	break;
	case 14:
#line 154 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    if (lexer->mark == 0) {
      MARK(mark, p);
    }
  }
	break;
	case 15:
#line 160 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    MARK(keyword_end, p);
    MARK(keyword_start, PTR_TO(mark));
    MARK(content_start, p + 1);
    lexer->mark = 0;
  }
	break;
	case 16:
#line 167 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    MARK(content_end, p);
  }
	break;
	case 17:
#line 171 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    p = p - 1;
    lexer->current_line = lexer->line_number;
    current_row = rb_ary_new();
  }
	break;
	case 18:
#line 177 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
		MARK(content_start, p);
  }
	break;
	case 19:
#line 181 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
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
#line 192 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
	{
    rb_funcall(listener, rb_intern("row"), 2, current_row, INT2FIX(lexer->current_line));
  }
	break;
	case 21:
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
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
#line 1226 "ext/gherkin_lexer_ro/gherkin_lexer_ro.c"
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
#line 196 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"
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
#line 1285 "ext/gherkin_lexer_ro/gherkin_lexer_ro.c"
		}
	}
	}

	_out: {}
	}

#line 426 "/home/moorthi/work/gherkin/tasks/../ragel/i18n/ro.c.rl"

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

void Init_gherkin_lexer_ro()
{
  mGherkin = rb_define_module("Gherkin");
  rb_eGherkinLexingError = rb_const_get(mGherkin, rb_intern("LexingError"));

  mCLexer = rb_define_module_under(mGherkin, "CLexer");
  cI18nLexer = rb_define_class_under(mCLexer, "Ro", rb_cObject);
  rb_define_alloc_func(cI18nLexer, CLexer_alloc);
  rb_define_method(cI18nLexer, "initialize", CLexer_init, 1);
  rb_define_method(cI18nLexer, "scan", CLexer_scan, 1);
}

