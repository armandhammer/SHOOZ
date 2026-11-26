// Copyright 2009 Olivier Gillet.
//
// Author: Olivier Gillet (ol.gillet@gmail.com)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// -----------------------------------------------------------------------------
//
// Resources definitions.
//
// Automatically generated with:
// make resources


#ifndef SHRUTHI_RESOURCES_H_
#define SHRUTHI_RESOURCES_H_


#include "avrlib/base.h"

#include <avr/pgmspace.h>


#include "avrlib/resources_manager.h"

namespace shruthi {

typedef uint16_t ResourceId;

extern const prog_char* const string_table[];

extern const prog_uint16_t* const lookup_table_table[];

extern const prog_uint32_t* const lookup_table32_table[];

extern const prog_uint8_t* const waveform_table[];

extern const prog_uint8_t* const character_table[];

extern const prog_uint16_t lut_res_lfo_increments[] PROGMEM;
extern const prog_uint16_t lut_res_env_portamento_increments[] PROGMEM;
extern const prog_uint16_t lut_res_oscillator_increments[] PROGMEM;
extern const prog_uint16_t lut_res_fm_frequency_ratios[] PROGMEM;
extern const prog_uint16_t lut_res_scale_just[] PROGMEM;
extern const prog_uint16_t lut_res_scale_pythagorean[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_eb[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_e[] PROGMEM;
extern const prog_uint16_t lut_res_scale_1_4_ea[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gunakri[] PROGMEM;
extern const prog_uint16_t lut_res_scale_marwa[] PROGMEM;
extern const prog_uint16_t lut_res_scale_shree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_purvi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bilawal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_yaman[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bhimpalasree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_darbari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rageshree[] PROGMEM;
extern const prog_uint16_t lut_res_scale_khamaj[] PROGMEM;
extern const prog_uint16_t lut_res_scale_mimal[] PROGMEM;
extern const prog_uint16_t lut_res_scale_parameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_rangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_gangeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kameshwari[] PROGMEM;
extern const prog_uint16_t lut_res_scale_palas_kafi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_natbhairav[] PROGMEM;
extern const prog_uint16_t lut_res_scale_m_kauns[] PROGMEM;
extern const prog_uint16_t lut_res_scale_bairagi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_b_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_chandradeep[] PROGMEM;
extern const prog_uint16_t lut_res_scale_kaushik_todi[] PROGMEM;
extern const prog_uint16_t lut_res_scale_jogeshwari[] PROGMEM;
extern const prog_uint16_t lut_res_arpeggiator_patterns[] PROGMEM;
extern const prog_uint16_t lut_res_groove_swing[] PROGMEM;
extern const prog_uint16_t lut_res_groove_shuffle[] PROGMEM;
extern const prog_uint16_t lut_res_groove_push[] PROGMEM;
extern const prog_uint16_t lut_res_groove_lag[] PROGMEM;
extern const prog_uint16_t lut_res_groove_human[] PROGMEM;
extern const prog_uint16_t lut_res_groove_monkey[] PROGMEM;
extern const prog_uint8_t wav_res_formant_sine[] PROGMEM;
extern const prog_uint8_t wav_res_formant_square[] PROGMEM;
extern const prog_uint8_t wav_res_sine[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_0[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_1[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_2[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_3[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_4[] PROGMEM;
extern const prog_uint8_t wav_res_bandlimited_saw_5[] PROGMEM;
extern const prog_uint8_t wav_res_vowel_data[] PROGMEM;
extern const prog_uint8_t wav_res_distortion[] PROGMEM;
extern const prog_uint8_t wav_res_env_expo[] PROGMEM;
extern const prog_uint8_t wav_res_ssm2164_linearization[] PROGMEM;
extern const prog_uint8_t wav_res_division_table[] PROGMEM;
extern const prog_uint8_t wav_res_blep_table[] PROGMEM;
extern const prog_uint8_t wav_res_waves[] PROGMEM;
extern const prog_uint8_t wav_res_wavetables[] PROGMEM;
extern const prog_uint8_t wav_res_version[] PROGMEM;
extern const prog_uint8_t chr_res_special_characters[] PROGMEM;
#define STR_RES_SHAPE 0  // shape
#define STR_RES_PARAMETER 1  // parameter
#define STR_RES_RESONANCE 2  // resonance
#define STR_RES_PRM 3  // prm
#define STR_RES_RANGE 4  // range
#define STR_RES_RNG 5  // rng
#define STR_RES_OP_ 6  // op.
#define STR_RES_OPERATOR 7  // operator
#define STR_RES_DETUNE 8  // detune
#define STR_RES_OSC_MIX 9  // osc mix
#define STR_RES_SUB_OSC_ 10  // sub osc.
#define STR_RES_ENV1TVCF 11  // env1~vcf
#define STR_RES_LFO2TVCF 12  // lfo2~vcf
#define STR_RES_ATTACK 13  // attack
#define STR_RES_ATK 14  // atk
#define STR_RES_DECAY 15  // decay
#define STR_RES_SUSTAIN 16  // sustain
#define STR_RES_RELEASE 17  // release
#define STR_RES_RATE 18  // rate
#define STR_RES_MODULATION 19  // modulation
#define STR_RES_OPERATORS 20  // operators
#define STR_RES_MOD_ 21  // mod.
#define STR_RES_SOURCE 22  // source
#define STR_RES_SRC 23  // src
#define STR_RES_DEST_ 24  // dest.
#define STR_RES_DST 25  // dst
#define STR_RES_AMOUNT 26  // amount
#define STR_RES_AMT 27  // amt
#define STR_RES_MODE 28  // mode
#define STR_RES_OVERDRIVE 29  // overdrive
#define STR_RES__FM 30  // fm
#define STR_RES_FLAVOUR 31  // flavour
#define STR_RES_TIME 32  // time
#define STR_RES_LEVEL 33  // level
#define STR_RES_FDB 34  // fdb
#define STR_RES_FEEDBACK 35  // feedback
#define STR_RES_EQ_ 36  // eq.
#define STR_RES_FDBCK_EQ_ 37  // fdbck eq.
#define STR_RES_TEMPO 38  // tempo
#define STR_RES_BPM 39  // bpm
#define STR_RES_GROOVE 40  // groove
#define STR_RES_DIRECTION 41  // direction
#define STR_RES_PATTERN 42  // pattern
#define STR_RES_DIVISION 43  // division
#define STR_RES_START 44  // start
#define STR_RES_LENGTH 45  // length
#define STR_RES_OCTAVE 46  // octave
#define STR_RES_RAGA 47  // raga
#define STR_RES_PORTA 48  // porta
#define STR_RES_PRT 49  // prt
#define STR_RES_LEGATO 50  // legato
#define STR_RES_TUNING 51  // tuning
#define STR_RES_MIDI_CHAN 52  // midi chan
#define STR_RES_CHN 53  // chn
#define STR_RES_MIDI_OUT 54  // midi out
#define STR_RES_PAUSE 55  // pause
#define STR_RES_STARTPAGE 56  // startpage
#define STR_RES_SNAP 57  // snap
#define STR_RES_VINT 58  // vint
#define STR_RES_VINTAGE 59  // vintage
#define STR_RES_OSCILLATOR_1 60  // oscillator 1
#define STR_RES_OSCILLATOR_2 61  // oscillator 2
#define STR_RES_MIXER 62  // mixer
#define STR_RES_FILTER 63  // filter
#define STR_RES_FILTERS 64  // filter+
#define STR_RES_MODE_1 65  // mode 1
#define STR_RES_MODE_2 66  // mode 2
#define STR_RES_MD1 67  // md1
#define STR_RES_MD2 68  // md2
#define STR_RES_ENVELOPE_1 69  // envelope 1
#define STR_RES_ENVELOPE_2 70  // envelope 2
#define STR_RES_SEQUENCER 71  // sequencer
#define STR_RES_ARPEGGIO 72  // arpeggio
#define STR_RES_CH1 73  // ch1
#define STR_RES_CH2 74  // ch2
#define STR_RES_11 75  // 1
#define STR_RES_12 76  // 2
#define STR_RES_STEP_SEQUENCER 77  // step sequencer
#define STR_RES_KEYBOARD 78  // keyboard
#define STR_RES_MIDI 79  // midi
#define STR_RES_SYSTEM 80  // system
#define STR_RES_PERFORMANCE 81  // performance
#define STR_RES_PARAM__1 82  // param. 1
#define STR_RES_PARAM__2 83  // param. 2
#define STR_RES_PR1 84  // pr1
#define STR_RES_PR2 85  // pr2
#define STR_RES_FX_ 86  // fx.
#define STR_RES_FX_PROG_ 87  // fx prog.
#define STR_RES_LPF 88  // lpf
#define STR_RES_BPF 89  // bpf
#define STR_RES_HPF 90  // hpf
#define STR_RES_LPL 91  // lp<
#define STR_RES_BPL 92  // bp<
#define STR_RES_HPL 93  // hp<
#define STR_RES_SLP 94  // +lp
#define STR_RES_SBP 95  // +bp
#define STR_RES_SHP 96  // +hp
#define STR_RES_GLP 97  // >lp
#define STR_RES_GBP 98  // >bp
#define STR_RES_GHP 99  // >hp
#define STR_RES_LP4 100  // lp4
#define STR_RES_LP3 101  // lp3
#define STR_RES_LP2 102  // lp2
#define STR_RES_LP1 103  // lp1
#define STR_RES_HP1 104  // hp1
#define STR_RES_HP2 105  // hp2
#define STR_RES_HP3 106  // hp3
#define STR_RES_BP2 107  // bp2
#define STR_RES_BP4 108  // bp4
#define STR_RES_NOTCH 109  // notch
#define STR_RES_PHASER 110  // phaser
#define STR_RES_H2LP 111  // h2lp
#define STR_RES_H3LP 112  // h3lp
#define STR_RES_NSLP 113  // n+lp
#define STR_RES_PSLP 114  // p+lp
#define STR_RES_LP 115  // lp
#define STR_RES_BP 116  // bp
#define STR_RES_HP 117  // hp
#define STR_RES_AP 118  // ap
#define STR_RES_LIQUID 119  // liquid
#define STR_RES_MS 120  // ms
#define STR_RES_WOBBLY 121  // wobbly
#define STR_RES_WHACKY 122  // whacky
#define STR_RES_PW1 123  // pw1
#define STR_RES_PW2 124  // pw2
#define STR_RES_51 125  // 1
#define STR_RES_52 126  // 2
#define STR_RES_5 127  // 
#define STR_RES_5F 128  // f
#define STR_RES_MIX 129  // mix
#define STR_RES_NOI 130  // noi
#define STR_RES_SUB 131  // sub
#define STR_RES_CUT 132  // cut
#define STR_RES_RES 133  // res
#define STR_RES_VCA 134  // vca
#define STR_RES_CV1 135  // cv1
#define STR_RES_CV2 136  // cv2
#define STR_RES_TR1 137  // tr1
#define STR_RES_A1 138  // a1
#define STR_RES_D1 139  // d1
#define STR_RES_S1 140  // s1
#define STR_RES_R1 141  // r1
#define STR_RES_TR2 142  // tr2
#define STR_RES_A2 143  // a2
#define STR_RES_D2 144  // d2
#define STR_RES_S2 145  // s2
#define STR_RES_R2 146  // r2
#define STR_RES__ATK 147  // atk
#define STR_RES__LF1 148  // lf1
#define STR_RES__LF2 149  // lf2
#define STR_RES_IN1 150  // in1
#define STR_RES_IN2 151  // in2
#define STR_RES_OUT 152  // out
#define STR_RES___OFF 153  // off
#define STR_RES_ADD 154  // add
#define STR_RES_PRD 155  // prd
#define STR_RES_MAX 156  // max
#define STR_RES_MIN 157  // min
#define STR_RES__XOR 158  // xor
#define STR_RES_GE 159  // >=
#define STR_RES_LE 160  // <=
#define STR_RES_QTZ 161  // qtz
#define STR_RES_LAG 162  // lag
#define STR_RES_PWM1 163  // pwm1
#define STR_RES_PWM2 164  // pwm2
#define STR_RES_OSC1 165  // osc1
#define STR_RES_OSC2 166  // osc2
#define STR_RES_OSC1S2 167  // osc1+2
#define STR_RES_FINE 168  // fine
#define STR_RES__MIX 169  // mix
#define STR_RES_NOISE 170  // noise
#define STR_RES_SUBOSC 171  // subosc
#define STR_RES_CUTOFF 172  // cutoff
#define STR_RES_RESO 173  // reso
#define STR_RES__VCA 174  // vca
#define STR_RES_CV_1 175  // cv 1
#define STR_RES_CV_2 176  // cv 2
#define STR_RES_TRG_E1 177  // trg e1
#define STR_RES_ATK__1 178  // atk. 1
#define STR_RES_DEC__1 179  // dec. 1
#define STR_RES_SUS__1 180  // sus. 1
#define STR_RES_REL__1 181  // rel. 1
#define STR_RES_TRG_E2 182  // trg e2
#define STR_RES_ATK__2 183  // atk. 2
#define STR_RES_DEC__2 184  // dec. 2
#define STR_RES_SUS__2 185  // sus. 2
#define STR_RES_REL__2 186  // rel. 2
#define STR_RES_ATK1S2 187  // atk1+2
#define STR_RES__LFO_1 188  // lfo 1
#define STR_RES__LFO_2 189  // lfo 2
#define STR_RES_DISTRT 190  // distrt
#define STR_RES_CRUSHR 191  // crushr
#define STR_RES_SCMBFL 192  // +cmbfl
#define STR_RES_CMBFL 193  // -cmbfl
#define STR_RES_RINGMD 194  // ringmd
#define STR_RES_DELAY 195  // delay
#define STR_RES_FB_DLY 196  // fb dly
#define STR_RES_DUBDLY 197  // dubdly
#define STR_RES__FBDLY 198  // !fbdly
#define STR_RES__DBDLY 199  // !dbdly
#define STR_RES__16_DL 200  // /16 dl
#define STR_RES__12_DL 201  // /12 dl
#define STR_RES__8_DLY 202  // /8 dly
#define STR_RES_3_16DL 203  // 3/16dl
#define STR_RES_LOOPER 204  // looper
#define STR_RES_PITCH 205  // pitch
#define STR_RES_LGF 206  // l>f
#define STR_RES_HGF 207  // h>f
#define STR_RES_FGL 208  // f>l
#define STR_RES_FGH 209  // f>h
#define STR_RES_GFX 210  // >fx
#define STR_RES_LF1 211  // lf1
#define STR_RES_LF2 212  // lf2
#define STR_RES_SEQ 213  // seq
#define STR_RES__SQ1 214  // sq1
#define STR_RES__SQ2 215  // sq2
#define STR_RES_ARP 216  // arp
#define STR_RES_WHL 217  // whl
#define STR_RES_AFT 218  // aft
#define STR_RES_BND 219  // bnd
#define STR_RES_OFS 220  // ofs
#define STR_RES__CV1 221  // cv1
#define STR_RES__CV2 222  // cv2
#define STR_RES_CV3 223  // cv3
#define STR_RES_CV4 224  // cv4
#define STR_RES_CCA 225  // ccA
#define STR_RES_CCB 226  // ccB
#define STR_RES_BRE 227  // bre
#define STR_RES_PED 228  // ped
#define STR_RES__NOI 229  // noi
#define STR_RES_EN1 230  // en1
#define STR_RES_EN2 231  // en2
#define STR_RES_VEL 232  // vel
#define STR_RES_RND 233  // rnd
#define STR_RES_NOT 234  // not
#define STR_RES_GAT 235  // gat
#define STR_RES_AUD 236  // aud
#define STR_RES_OP1 237  // op1
#define STR_RES_OP2 238  // op2
#define STR_RES_E4 239  // =4
#define STR_RES_E8 240  // =8
#define STR_RES_E16 241  // =16
#define STR_RES_E32 242  // =32
#define STR_RES_LFO_1 243  // lfo 1
#define STR_RES_LFO_2 244  // lfo 2
#define STR_RES_STPSEQ 245  // stpseq
#define STR_RES_STPSQ1 246  // stpsq1
#define STR_RES_STPSQ2 247  // stpsq2
#define STR_RES__ARP 248  // arp
#define STR_RES_MWHEEL 249  // mwheel
#define STR_RES_AFTTCH 250  // afttch
#define STR_RES_BENDER 251  // bender
#define STR_RES_OFFSET 252  // offset
#define STR_RES__CV_1 253  // cv 1
#define STR_RES__CV_2 254  // cv 2
#define STR_RES_CV_3 255  // cv 3
#define STR_RES_CV_4 256  // cv 4
#define STR_RES_CC_A 257  // cc A
#define STR_RES_CC_B 258  // cc B
#define STR_RES_BREATH 259  // breath
#define STR_RES_PEDAL 260  // pedal
#define STR_RES__NOISE 261  // noise
#define STR_RES_ENV_1 262  // env 1
#define STR_RES_ENV_2 263  // env 2
#define STR_RES_VELO 264  // velo
#define STR_RES_RANDOM 265  // random
#define STR_RES_NOTE 266  // note
#define STR_RES_GATE 267  // gate
#define STR_RES_AUDIO 268  // audio
#define STR_RES_OP__1 269  // op. 1
#define STR_RES_OP__2 270  // op. 2
#define STR_RES_E_4 271  // = 4
#define STR_RES_E_8 272  // = 8
#define STR_RES_E_16 273  // = 16
#define STR_RES_E_32 274  // = 32
#define STR_RES_PATCH 275  // patch
#define STR_RES_SEQUENCE 276  // sequence
#define STR_RES_SAVE_MIDI_KBD 277  // save midi/kbd
#define STR_RES_SETTINGS_ 278  // settings?
#define STR_RES_START_FULL_MIDI 279  // start full midi
#define STR_RES_BACKUP_ 280  // backup?
#define STR_RES_BROWSE 281  // browse
#define STR_RES_SAVE 282  // save
#define STR_RES_COMPARE 283  // compare
#define STR_RES_ 284  // ----
#define STR_RES_V 285  // v
#define STR_RES_MUTABLE___YA8_05 286  // mutable   YA.05
#define STR_RES_INSTRUMENTS_671 287  // instruments -1
#define STR_RES_SHRUTHI_CLASSIC 288  // shruthi classic
#define STR_RES_4_KNOBS 289  // (4 knobs)
#define STR_RES_SHRUTHI_XT 290  // shruthi xt
#define STR_RES_CLASSIC_FCD72 291  // classic (fcd72)
#define STR_RES__SHRUTHI_XT 292  // shruthi xt
#define STR_RES_FULL_CONTROL 293  // (full control)
#define STR_RES_LETS_JAM_ 294  // let's jam!
#define STR_RES_EXTERN 295  // extern
#define STR_RES_SUM 296  // sum
#define STR_RES_SYNC 297  // sync
#define STR_RES_RING 298  // ring
#define STR_RES_XOR 299  // xor
#define STR_RES_FUZZ 300  // fuzz
#define STR_RES_GG4 301  // >>4
#define STR_RES_GG8 302  // >>8
#define STR_RES_FOLD 303  // fold
#define STR_RES_BITS 304  // bits
#define STR_RES_DUO 305  // duo
#define STR_RES_2STEPS 306  // 2steps
#define STR_RES_4STEPS 307  // 4steps
#define STR_RES_8STEPS 308  // 8steps
#define STR_RES_SEQMIX 309  // seqmix
#define STR_RES_STP 310  // stp
#define STR_RES___ARP 311  // arp
#define STR_RES__SEQ 312  // seq
#define STR_RES_FREE 313  // free
#define STR_RES_SLAVE 314  // slave
#define STR_RES_MASTER 315  // master
#define STR_RES_1SHOT 316  // 1shot
#define STR_RES_1_1 317  // 1/1
#define STR_RES_1_2 318  // 1/2
#define STR_RES_1_3 319  // 1/3
#define STR_RES_1_4 320  // 1/4
#define STR_RES_1_6 321  // 1/6
#define STR_RES_1_8 322  // 1/8
#define STR_RES__12 323  // /12
#define STR_RES__16 324  // /16
#define STR_RES__24 325  // /24
#define STR_RES__32 326  // /32
#define STR_RES__48 327  // /48
#define STR_RES__96 328  // /96
#define STR_RES_SWING 329  // swing
#define STR_RES_SHUFFLE 330  // shuffle
#define STR_RES_PUSH 331  // push
#define STR_RES__LAG 332  // lag
#define STR_RES_HUMAN 333  // human
#define STR_RES_MONKEY 334  // monkey
#define STR_RES__OFF 335  // off
#define STR_RES_THRU 336  // thru
#define STR_RES___SEQ 337  // seq
#define STR_RES_CTRL 338  // ctrl
#define STR_RES_FULL 339  // full
#define STR_RES_1TV 340  // 1~|
#define STR_RES_2T1 341  // 2~1
#define STR_RES_3T2 342  // 3~2
#define STR_RES_4T3 343  // 4~3
#define STR_RES_5T4 344  // 5~4
#define STR_RES_6T5 345  // 6~5
#define STR_RES_7T6 346  // 7~6
#define STR_RES_8T7 347  // 8~7
#define STR_RES_TRI 348  // tri
#define STR_RES_SQR 349  // sqr
#define STR_RES_S_H 350  // s&h
#define STR_RES_RAMP 351  // ramp
#define STR_RES_STEP 352  // step
#define STR_RES_3 353  // 
#define STR_RES_4 354  // 
#define STR_RES_34 355  // 
#define STR_RES__ 356  // ?
#define STR_RES_PLAYED 357  // played
#define STR_RES_OFF 358  // off
#define STR_RES_ON 359  // on
#define STR_RES_SQ1 360  // sq1
#define STR_RES__TR1 361  // tr1
#define STR_RES_PL1 362  // pl1
#define STR_RES_SQ2 363  // sq2
#define STR_RES__TR2 364  // tr2
#define STR_RES_PL2 365  // pl2
#define STR_RES_CLICK 366  // click
#define STR_RES_GLITCH 367  // glitch
#define STR_RES_BLOW 368  // blow
#define STR_RES_METAL 369  // metal
#define STR_RES_POP 370  // pop
#define STR_RES_NONE 371  // none
#define STR_RES_SAW 372  // saw
#define STR_RES_CSAW 373  // csaw
#define STR_RES_OLDSAW 374  // oldsaw
#define STR_RES_SQUARE 375  // square
#define STR_RES_DPWM 376  // dpwm
#define STR_RES_TRIANG 377  // triang
#define STR_RES_ZSAW 378  // zsaw
#define STR_RES_LPZSAW 379  // lpzsaw
#define STR_RES_PKZSAW 380  // pkzsaw
#define STR_RES_HPZSAW 381  // hpzsaw
#define STR_RES_LPZPULSE 382  // lpzpulse
#define STR_RES_PKZPULSE 383  // pkzpulse
#define STR_RES_HPZPULSE 384  // hpzpulse
#define STR_RES_ZSYNC 385  // zsync
#define STR_RES_ZTRI 386  // ztri
#define STR_RES_PAD 387  // pad
#define STR_RES_QPWM 388  // qpwm
#define STR_RES_FM 389  // fm
#define STR_RES_FMFB 390  // fmfb
#define STR_RES_8BITS 391  // 8bits
#define STR_RES_CRUSH 392  // crush
#define STR_RES___NOISE 393  // noise
#define STR_RES_VOWEL 394  // vowel
#define STR_RES_WAVES 395  // waves
#define STR_RES_TAMPUR 396  // tampur
#define STR_RES_DIGITL 397  // digitl
#define STR_RES_METALL 398  // metall
#define STR_RES_BOWED 399  // bowed
#define STR_RES_SLAP 400  // slap
#define STR_RES_ORGAN 401  // organ
#define STR_RES_MALE 402  // male
#define STR_RES_USER 403  // user
#define STR_RES_BELISH 404  // belish
#define STR_RES_POLATD 405  // polatd
#define STR_RES_CELLO 406  // cello
#define STR_RES_CLPSWP 407  // clpswp
#define STR_RES_FEMALE 408  // female
#define STR_RES_FMTVOC 409  // fmtvoc
#define STR_RES_FRMNT2 410  // frmnt2
#define STR_RES_RES3HP 411  // res3hp
#define STR_RES_ELECTP 412  // electp
#define STR_RES_VIBES 413  // vibes
#define STR_RES_WAVQUENCE 414  // wavquence
#define STR_RES__LPF 415  // lpf
#define STR_RES_SSM 416  // ssm
#define STR_RES_SVF 417  // svf
#define STR_RES_DSP 418  // dsp
#define STR_RES_PVK 419  // pvk
#define STR_RES_4PM 420  // 4pm
#define STR_RES_DLY 421  // dly
#define STR_RES_SP 422  // sp
#define STR_RES_SPLASH 423  // splash
#define STR_RES__FILTER 424  // filter
#define STR_RES_PRESET 425  // preset
#define STR_RES_EQUAL 426  // equal
#define STR_RES_JUST 427  // just
#define STR_RES_PYTHAG 428  // pythag
#define STR_RES_1_4_EB 429  // 1/4 eb
#define STR_RES_1_4_E 430  // 1/4 e
#define STR_RES_1_4_EA 431  // 1/4 ea
#define STR_RES_BHAIRA 432  // bhaira
#define STR_RES_GUNAKR 433  // gunakr
#define STR_RES_MARWA 434  // marwa
#define STR_RES_SHREE 435  // shree
#define STR_RES_PURVI 436  // purvi
#define STR_RES_BILAWA 437  // bilawa
#define STR_RES_YAMAN 438  // yaman
#define STR_RES_KAFI 439  // kafi
#define STR_RES_BHIMPA 440  // bhimpa
#define STR_RES_DARBAR 441  // darbar
#define STR_RES_BAGESH 442  // bagesh
#define STR_RES_RAGESH 443  // ragesh
#define STR_RES_KHAMAJ 444  // khamaj
#define STR_RES_MIMAL 445  // mi'mal
#define STR_RES_PARAME 446  // parame
#define STR_RES_RANGES 447  // ranges
#define STR_RES_GANGES 448  // ganges
#define STR_RES_KAMESH 449  // kamesh
#define STR_RES_PALAS_ 450  // palas
#define STR_RES_NATBHA 451  // natbha
#define STR_RES_M_KAUN 452  // m.kaun
#define STR_RES_BAIRAG 453  // bairag
#define STR_RES_B_TODI 454  // b.todi
#define STR_RES_CHANDR 455  // chandr
#define STR_RES_KAUSHI 456  // kaushi
#define STR_RES_JOGESH 457  // jogesh
#define STR_RES_RASIA 458  // rasia
#define LUT_RES_LFO_INCREMENTS 0
#define LUT_RES_LFO_INCREMENTS_SIZE 128
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS 1
#define LUT_RES_ENV_PORTAMENTO_INCREMENTS_SIZE 128
#define LUT_RES_OSCILLATOR_INCREMENTS 2
#define LUT_RES_OSCILLATOR_INCREMENTS_SIZE 97
#define LUT_RES_FM_FREQUENCY_RATIOS 3
#define LUT_RES_FM_FREQUENCY_RATIOS_SIZE 25
#define LUT_RES_SCALE_JUST 4
#define LUT_RES_SCALE_JUST_SIZE 12
#define LUT_RES_SCALE_PYTHAGOREAN 5
#define LUT_RES_SCALE_PYTHAGOREAN_SIZE 12
#define LUT_RES_SCALE_1_4_EB 6
#define LUT_RES_SCALE_1_4_EB_SIZE 12
#define LUT_RES_SCALE_1_4_E 7
#define LUT_RES_SCALE_1_4_E_SIZE 12
#define LUT_RES_SCALE_1_4_EA 8
#define LUT_RES_SCALE_1_4_EA_SIZE 12
#define LUT_RES_SCALE_BHAIRAV 9
#define LUT_RES_SCALE_BHAIRAV_SIZE 12
#define LUT_RES_SCALE_GUNAKRI 10
#define LUT_RES_SCALE_GUNAKRI_SIZE 12
#define LUT_RES_SCALE_MARWA 11
#define LUT_RES_SCALE_MARWA_SIZE 12
#define LUT_RES_SCALE_SHREE 12
#define LUT_RES_SCALE_SHREE_SIZE 12
#define LUT_RES_SCALE_PURVI 13
#define LUT_RES_SCALE_PURVI_SIZE 12
#define LUT_RES_SCALE_BILAWAL 14
#define LUT_RES_SCALE_BILAWAL_SIZE 12
#define LUT_RES_SCALE_YAMAN 15
#define LUT_RES_SCALE_YAMAN_SIZE 12
#define LUT_RES_SCALE_KAFI 16
#define LUT_RES_SCALE_KAFI_SIZE 12
#define LUT_RES_SCALE_BHIMPALASREE 17
#define LUT_RES_SCALE_BHIMPALASREE_SIZE 12
#define LUT_RES_SCALE_DARBARI 18
#define LUT_RES_SCALE_DARBARI_SIZE 12
#define LUT_RES_SCALE_BAGESHREE 19
#define LUT_RES_SCALE_BAGESHREE_SIZE 12
#define LUT_RES_SCALE_RAGESHREE 20
#define LUT_RES_SCALE_RAGESHREE_SIZE 12
#define LUT_RES_SCALE_KHAMAJ 21
#define LUT_RES_SCALE_KHAMAJ_SIZE 12
#define LUT_RES_SCALE_MIMAL 22
#define LUT_RES_SCALE_MIMAL_SIZE 12
#define LUT_RES_SCALE_PARAMESHWARI 23
#define LUT_RES_SCALE_PARAMESHWARI_SIZE 12
#define LUT_RES_SCALE_RANGESHWARI 24
#define LUT_RES_SCALE_RANGESHWARI_SIZE 12
#define LUT_RES_SCALE_GANGESHWARI 25
#define LUT_RES_SCALE_GANGESHWARI_SIZE 12
#define LUT_RES_SCALE_KAMESHWARI 26
#define LUT_RES_SCALE_KAMESHWARI_SIZE 12
#define LUT_RES_SCALE_PALAS_KAFI 27
#define LUT_RES_SCALE_PALAS_KAFI_SIZE 12
#define LUT_RES_SCALE_NATBHAIRAV 28
#define LUT_RES_SCALE_NATBHAIRAV_SIZE 12
#define LUT_RES_SCALE_M_KAUNS 29
#define LUT_RES_SCALE_M_KAUNS_SIZE 12
#define LUT_RES_SCALE_BAIRAGI 30
#define LUT_RES_SCALE_BAIRAGI_SIZE 12
#define LUT_RES_SCALE_B_TODI 31
#define LUT_RES_SCALE_B_TODI_SIZE 12
#define LUT_RES_SCALE_CHANDRADEEP 32
#define LUT_RES_SCALE_CHANDRADEEP_SIZE 12
#define LUT_RES_SCALE_KAUSHIK_TODI 33
#define LUT_RES_SCALE_KAUSHIK_TODI_SIZE 12
#define LUT_RES_SCALE_JOGESHWARI 34
#define LUT_RES_SCALE_JOGESHWARI_SIZE 12
#define LUT_RES_SCALE_RASIA 35
#define LUT_RES_SCALE_RASIA_SIZE 12
#define LUT_RES_ARPEGGIATOR_PATTERNS 36
#define LUT_RES_ARPEGGIATOR_PATTERNS_SIZE 15
#define LUT_RES_GROOVE_SWING 37
#define LUT_RES_GROOVE_SWING_SIZE 16
#define LUT_RES_GROOVE_SHUFFLE 38
#define LUT_RES_GROOVE_SHUFFLE_SIZE 16
#define LUT_RES_GROOVE_PUSH 39
#define LUT_RES_GROOVE_PUSH_SIZE 16
#define LUT_RES_GROOVE_LAG 40
#define LUT_RES_GROOVE_LAG_SIZE 16
#define LUT_RES_GROOVE_HUMAN 41
#define LUT_RES_GROOVE_HUMAN_SIZE 16
#define LUT_RES_GROOVE_MONKEY 42
#define LUT_RES_GROOVE_MONKEY_SIZE 16
#define WAV_RES_FORMANT_SINE 0
#define WAV_RES_FORMANT_SINE_SIZE 256
#define WAV_RES_FORMANT_SQUARE 1
#define WAV_RES_FORMANT_SQUARE_SIZE 256
#define WAV_RES_SINE 2
#define WAV_RES_SINE_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_0 3
#define WAV_RES_BANDLIMITED_SAW_0_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_1 4
#define WAV_RES_BANDLIMITED_SAW_1_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_2 5
#define WAV_RES_BANDLIMITED_SAW_2_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_3 6
#define WAV_RES_BANDLIMITED_SAW_3_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_4 7
#define WAV_RES_BANDLIMITED_SAW_4_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_5 8
#define WAV_RES_BANDLIMITED_SAW_5_SIZE 257
#define WAV_RES_BANDLIMITED_SAW_6 9
#define WAV_RES_BANDLIMITED_SAW_6_SIZE 257
#define WAV_RES_VOWEL_DATA 10
#define WAV_RES_VOWEL_DATA_SIZE 63
#define WAV_RES_DISTORTION 11
#define WAV_RES_DISTORTION_SIZE 256
#define WAV_RES_ENV_EXPO 12
#define WAV_RES_ENV_EXPO_SIZE 257
#define WAV_RES_SSM2164_LINEARIZATION 13
#define WAV_RES_SSM2164_LINEARIZATION_SIZE 64
#define WAV_RES_DIVISION_TABLE 14
#define WAV_RES_DIVISION_TABLE_SIZE 128
#define WAV_RES_BLEP_TABLE 15
#define WAV_RES_BLEP_TABLE_SIZE 128
#define WAV_RES_WAVES 16
#define WAV_RES_WAVES_SIZE 16383
#define WAV_RES_WAVETABLES 17
#define WAV_RES_WAVETABLES_SIZE 324
#define WAV_RES_VERSION 18
#define WAV_RES_VERSION_SIZE 2
#define CHR_RES_SPECIAL_CHARACTERS 0
#define CHR_RES_SPECIAL_CHARACTERS_SIZE 64
typedef avrlib::ResourcesManager<
    ResourceId,
    avrlib::ResourcesTables<
        string_table,
        lookup_table_table> > ResourcesManager; 

}  // namespace shruthi

#endif  // SHRUTHI_RESOURCES_H_
