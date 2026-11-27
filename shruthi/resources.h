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
#define STR_RES_CRV1 60  // crv1
#define STR_RES_CRV2 61  // crv2
#define STR_RES_ENV1_CURVE 62  // env1 curve
#define STR_RES_ENV2_CURVE 63  // env2 curve
#define STR_RES_ENV_CURVES 64  // env curves
#define STR_RES_PROF 65  // prof
#define STR_RES_COFS 66  // cofs
#define STR_RES_RMAX 67  // rmax
#define STR_RES_PROFILE 68  // profile
#define STR_RES_FILTER_CAL 69  // filter cal
#define STR_RES_OSCILLATOR_1 70  // oscillator 1
#define STR_RES_OSCILLATOR_2 71  // oscillator 2
#define STR_RES_MIXER 72  // mixer
#define STR_RES_FILTER 73  // filter
#define STR_RES_FILTERS 74  // filter+
#define STR_RES_MODE_1 75  // mode 1
#define STR_RES_MODE_2 76  // mode 2
#define STR_RES_MD1 77  // md1
#define STR_RES_MD2 78  // md2
#define STR_RES_ENVELOPE_1 79  // envelope 1
#define STR_RES_ENVELOPE_2 80  // envelope 2
#define STR_RES_SEQUENCER 81  // sequencer
#define STR_RES_ARPEGGIO 82  // arpeggio
#define STR_RES_CH1 83  // ch1
#define STR_RES_CH2 84  // ch2
#define STR_RES_11 85  // 1
#define STR_RES_12 86  // 2
#define STR_RES_STEP_SEQUENCER 87  // step sequencer
#define STR_RES_KEYBOARD 88  // keyboard
#define STR_RES_MIDI 89  // midi
#define STR_RES_SYSTEM 90  // system
#define STR_RES_PERFORMANCE 91  // performance
#define STR_RES_PARAM__1 92  // param. 1
#define STR_RES_PARAM__2 93  // param. 2
#define STR_RES_PR1 94  // pr1
#define STR_RES_PR2 95  // pr2
#define STR_RES_FX_ 96  // fx.
#define STR_RES_FX_PROG_ 97  // fx prog.
#define STR_RES_LPF 98  // lpf
#define STR_RES_BPF 99  // bpf
#define STR_RES_HPF 100  // hpf
#define STR_RES_LPL 101  // lp<
#define STR_RES_BPL 102  // bp<
#define STR_RES_HPL 103  // hp<
#define STR_RES_SLP 104  // +lp
#define STR_RES_SBP 105  // +bp
#define STR_RES_SHP 106  // +hp
#define STR_RES_GLP 107  // >lp
#define STR_RES_GBP 108  // >bp
#define STR_RES_GHP 109  // >hp
#define STR_RES_LP4 110  // lp4
#define STR_RES_LP3 111  // lp3
#define STR_RES_LP2 112  // lp2
#define STR_RES_LP1 113  // lp1
#define STR_RES_HP1 114  // hp1
#define STR_RES_HP2 115  // hp2
#define STR_RES_HP3 116  // hp3
#define STR_RES_BP2 117  // bp2
#define STR_RES_BP4 118  // bp4
#define STR_RES_NOTCH 119  // notch
#define STR_RES_PHASER 120  // phaser
#define STR_RES_H2LP 121  // h2lp
#define STR_RES_H3LP 122  // h3lp
#define STR_RES_NSLP 123  // n+lp
#define STR_RES_PSLP 124  // p+lp
#define STR_RES_LP 125  // lp
#define STR_RES_BP 126  // bp
#define STR_RES_HP 127  // hp
#define STR_RES_AP 128  // ap
#define STR_RES_LIQUID 129  // liquid
#define STR_RES_MS 130  // ms
#define STR_RES_WOBBLY 131  // wobbly
#define STR_RES_WHACKY 132  // whacky
#define STR_RES_PW1 133  // pw1
#define STR_RES_PW2 134  // pw2
#define STR_RES_51 135  // 1
#define STR_RES_52 136  // 2
#define STR_RES_5 137  // 
#define STR_RES_5F 138  // f
#define STR_RES_MIX 139  // mix
#define STR_RES_NOI 140  // noi
#define STR_RES_SUB 141  // sub
#define STR_RES_CUT 142  // cut
#define STR_RES_RES 143  // res
#define STR_RES_VCA 144  // vca
#define STR_RES_CV1 145  // cv1
#define STR_RES_CV2 146  // cv2
#define STR_RES_TR1 147  // tr1
#define STR_RES_A1 148  // a1
#define STR_RES_D1 149  // d1
#define STR_RES_S1 150  // s1
#define STR_RES_R1 151  // r1
#define STR_RES_TR2 152  // tr2
#define STR_RES_A2 153  // a2
#define STR_RES_D2 154  // d2
#define STR_RES_S2 155  // s2
#define STR_RES_R2 156  // r2
#define STR_RES__ATK 157  // atk
#define STR_RES__LF1 158  // lf1
#define STR_RES__LF2 159  // lf2
#define STR_RES_IN1 160  // in1
#define STR_RES_IN2 161  // in2
#define STR_RES_OUT 162  // out
#define STR_RES___OFF 163  // off
#define STR_RES_ADD 164  // add
#define STR_RES_PRD 165  // prd
#define STR_RES_MAX 166  // max
#define STR_RES_MIN 167  // min
#define STR_RES__XOR 168  // xor
#define STR_RES_GE 169  // >=
#define STR_RES_LE 170  // <=
#define STR_RES_QTZ 171  // qtz
#define STR_RES_LAG 172  // lag
#define STR_RES_PWM1 173  // pwm1
#define STR_RES_PWM2 174  // pwm2
#define STR_RES_OSC1 175  // osc1
#define STR_RES_OSC2 176  // osc2
#define STR_RES_OSC1S2 177  // osc1+2
#define STR_RES_FINE 178  // fine
#define STR_RES__MIX 179  // mix
#define STR_RES_NOISE 180  // noise
#define STR_RES_SUBOSC 181  // subosc
#define STR_RES_CUTOFF 182  // cutoff
#define STR_RES_RESO 183  // reso
#define STR_RES__VCA 184  // vca
#define STR_RES_CV_1 185  // cv 1
#define STR_RES_CV_2 186  // cv 2
#define STR_RES_TRG_E1 187  // trg e1
#define STR_RES_ATK__1 188  // atk. 1
#define STR_RES_DEC__1 189  // dec. 1
#define STR_RES_SUS__1 190  // sus. 1
#define STR_RES_REL__1 191  // rel. 1
#define STR_RES_TRG_E2 192  // trg e2
#define STR_RES_ATK__2 193  // atk. 2
#define STR_RES_DEC__2 194  // dec. 2
#define STR_RES_SUS__2 195  // sus. 2
#define STR_RES_REL__2 196  // rel. 2
#define STR_RES_ATK1S2 197  // atk1+2
#define STR_RES__LFO_1 198  // lfo 1
#define STR_RES__LFO_2 199  // lfo 2
#define STR_RES_DISTRT 200  // distrt
#define STR_RES_CRUSHR 201  // crushr
#define STR_RES_SCMBFL 202  // +cmbfl
#define STR_RES_CMBFL 203  // -cmbfl
#define STR_RES_RINGMD 204  // ringmd
#define STR_RES_DELAY 205  // delay
#define STR_RES_FB_DLY 206  // fb dly
#define STR_RES_DUBDLY 207  // dubdly
#define STR_RES__FBDLY 208  // !fbdly
#define STR_RES__DBDLY 209  // !dbdly
#define STR_RES__16_DL 210  // /16 dl
#define STR_RES__12_DL 211  // /12 dl
#define STR_RES__8_DLY 212  // /8 dly
#define STR_RES_3_16DL 213  // 3/16dl
#define STR_RES_LOOPER 214  // looper
#define STR_RES_PITCH 215  // pitch
#define STR_RES_LGF 216  // l>f
#define STR_RES_HGF 217  // h>f
#define STR_RES_FGL 218  // f>l
#define STR_RES_FGH 219  // f>h
#define STR_RES_GFX 220  // >fx
#define STR_RES_LF1 221  // lf1
#define STR_RES_LF2 222  // lf2
#define STR_RES_SEQ 223  // seq
#define STR_RES__SQ1 224  // sq1
#define STR_RES__SQ2 225  // sq2
#define STR_RES_ARP 226  // arp
#define STR_RES_WHL 227  // whl
#define STR_RES_AFT 228  // aft
#define STR_RES_BND 229  // bnd
#define STR_RES_OFS 230  // ofs
#define STR_RES__CV1 231  // cv1
#define STR_RES__CV2 232  // cv2
#define STR_RES_CV3 233  // cv3
#define STR_RES_CV4 234  // cv4
#define STR_RES_CCA 235  // ccA
#define STR_RES_CCB 236  // ccB
#define STR_RES_BRE 237  // bre
#define STR_RES_PED 238  // ped
#define STR_RES__NOI 239  // noi
#define STR_RES_EN1 240  // en1
#define STR_RES_EN2 241  // en2
#define STR_RES_VEL 242  // vel
#define STR_RES_RND 243  // rnd
#define STR_RES_NOT 244  // not
#define STR_RES_GAT 245  // gat
#define STR_RES_AUD 246  // aud
#define STR_RES_OP1 247  // op1
#define STR_RES_OP2 248  // op2
#define STR_RES_E4 249  // =4
#define STR_RES_E8 250  // =8
#define STR_RES_E16 251  // =16
#define STR_RES_E32 252  // =32
#define STR_RES_LFO_1 253  // lfo 1
#define STR_RES_LFO_2 254  // lfo 2
#define STR_RES_STPSEQ 255  // stpseq
#define STR_RES_STPSQ1 256  // stpsq1
#define STR_RES_STPSQ2 257  // stpsq2
#define STR_RES__ARP 258  // arp
#define STR_RES_MWHEEL 259  // mwheel
#define STR_RES_AFTTCH 260  // afttch
#define STR_RES_BENDER 261  // bender
#define STR_RES_OFFSET 262  // offset
#define STR_RES__CV_1 263  // cv 1
#define STR_RES__CV_2 264  // cv 2
#define STR_RES_CV_3 265  // cv 3
#define STR_RES_CV_4 266  // cv 4
#define STR_RES_CC_A 267  // cc A
#define STR_RES_CC_B 268  // cc B
#define STR_RES_BREATH 269  // breath
#define STR_RES_PEDAL 270  // pedal
#define STR_RES__NOISE 271  // noise
#define STR_RES_ENV_1 272  // env 1
#define STR_RES_ENV_2 273  // env 2
#define STR_RES_VELO 274  // velo
#define STR_RES_RANDOM 275  // random
#define STR_RES_NOTE 276  // note
#define STR_RES_GATE 277  // gate
#define STR_RES_AUDIO 278  // audio
#define STR_RES_OP__1 279  // op. 1
#define STR_RES_OP__2 280  // op. 2
#define STR_RES_E_4 281  // = 4
#define STR_RES_E_8 282  // = 8
#define STR_RES_E_16 283  // = 16
#define STR_RES_E_32 284  // = 32
#define STR_RES_PATCH 285  // patch
#define STR_RES_SEQUENCE 286  // sequence
#define STR_RES_SAVE_MIDI_KBD 287  // save midi/kbd
#define STR_RES_SETTINGS_ 288  // settings?
#define STR_RES_START_FULL_MIDI 289  // start full midi
#define STR_RES_BACKUP_ 290  // backup?
#define STR_RES_BROWSE 291  // browse
#define STR_RES_SAVE 292  // save
#define STR_RES_COMPARE 293  // compare
#define STR_RES_ 294  // ----
#define STR_RES_V 295  // v
#define STR_RES_MUTABLE___YA8_05 296  // mutable   YA.05
#define STR_RES_INSTRUMENTS_671 297  // instruments -1
#define STR_RES_SHRUTHI_CLASSIC 298  // shruthi classic
#define STR_RES_4_KNOBS 299  // (4 knobs)
#define STR_RES_SHRUTHI_XT 300  // shruthi xt
#define STR_RES_CLASSIC_FCD72 301  // classic (fcd72)
#define STR_RES__SHRUTHI_XT 302  // shruthi xt
#define STR_RES_FULL_CONTROL 303  // (full control)
#define STR_RES_LETS_JAM_ 304  // let's jam!
#define STR_RES_EXTERN 305  // extern
#define STR_RES_SUM 306  // sum
#define STR_RES_SYNC 307  // sync
#define STR_RES_RING 308  // ring
#define STR_RES_XOR 309  // xor
#define STR_RES_FUZZ 310  // fuzz
#define STR_RES_GG4 311  // >>4
#define STR_RES_GG8 312  // >>8
#define STR_RES_FOLD 313  // fold
#define STR_RES_BITS 314  // bits
#define STR_RES_DUO 315  // duo
#define STR_RES_2STEPS 316  // 2steps
#define STR_RES_4STEPS 317  // 4steps
#define STR_RES_8STEPS 318  // 8steps
#define STR_RES_SEQMIX 319  // seqmix
#define STR_RES_STP 320  // stp
#define STR_RES___ARP 321  // arp
#define STR_RES__SEQ 322  // seq
#define STR_RES_FREE 323  // free
#define STR_RES_SLAVE 324  // slave
#define STR_RES_MASTER 325  // master
#define STR_RES_1SHOT 326  // 1shot
#define STR_RES_1_1 327  // 1/1
#define STR_RES_1_2 328  // 1/2
#define STR_RES_1_3 329  // 1/3
#define STR_RES_1_4 330  // 1/4
#define STR_RES_1_6 331  // 1/6
#define STR_RES_1_8 332  // 1/8
#define STR_RES__12 333  // /12
#define STR_RES__16 334  // /16
#define STR_RES__24 335  // /24
#define STR_RES__32 336  // /32
#define STR_RES__48 337  // /48
#define STR_RES__96 338  // /96
#define STR_RES_SWING 339  // swing
#define STR_RES_SHUFFLE 340  // shuffle
#define STR_RES_PUSH 341  // push
#define STR_RES__LAG 342  // lag
#define STR_RES_HUMAN 343  // human
#define STR_RES_MONKEY 344  // monkey
#define STR_RES__OFF 345  // off
#define STR_RES_THRU 346  // thru
#define STR_RES___SEQ 347  // seq
#define STR_RES_CTRL 348  // ctrl
#define STR_RES_FULL 349  // full
#define STR_RES_1TV 350  // 1~|
#define STR_RES_2T1 351  // 2~1
#define STR_RES_3T2 352  // 3~2
#define STR_RES_4T3 353  // 4~3
#define STR_RES_5T4 354  // 5~4
#define STR_RES_6T5 355  // 6~5
#define STR_RES_7T6 356  // 7~6
#define STR_RES_8T7 357  // 8~7
#define STR_RES_TRI 358  // tri
#define STR_RES_SQR 359  // sqr
#define STR_RES_S_H 360  // s&h
#define STR_RES_RAMP 361  // ramp
#define STR_RES_STEP 362  // step
#define STR_RES_3 363  // 
#define STR_RES_4 364  // 
#define STR_RES_34 365  // 
#define STR_RES__ 366  // ?
#define STR_RES_PLAYED 367  // played
#define STR_RES_OFF 368  // off
#define STR_RES_ON 369  // on
#define STR_RES_SQ1 370  // sq1
#define STR_RES__TR1 371  // tr1
#define STR_RES_PL1 372  // pl1
#define STR_RES_SQ2 373  // sq2
#define STR_RES__TR2 374  // tr2
#define STR_RES_PL2 375  // pl2
#define STR_RES_CLICK 376  // click
#define STR_RES_GLITCH 377  // glitch
#define STR_RES_BLOW 378  // blow
#define STR_RES_METAL 379  // metal
#define STR_RES_POP 380  // pop
#define STR_RES_NONE 381  // none
#define STR_RES_SAW 382  // saw
#define STR_RES_CSAW 383  // csaw
#define STR_RES_OLDSAW 384  // oldsaw
#define STR_RES_SQUARE 385  // square
#define STR_RES_DPWM 386  // dpwm
#define STR_RES_TRIANG 387  // triang
#define STR_RES_ZSAW 388  // zsaw
#define STR_RES_LPZSAW 389  // lpzsaw
#define STR_RES_PKZSAW 390  // pkzsaw
#define STR_RES_HPZSAW 391  // hpzsaw
#define STR_RES_LPZPULSE 392  // lpzpulse
#define STR_RES_PKZPULSE 393  // pkzpulse
#define STR_RES_HPZPULSE 394  // hpzpulse
#define STR_RES_ZSYNC 395  // zsync
#define STR_RES_ZTRI 396  // ztri
#define STR_RES_PAD 397  // pad
#define STR_RES_QPWM 398  // qpwm
#define STR_RES_FM 399  // fm
#define STR_RES_FMFB 400  // fmfb
#define STR_RES_8BITS 401  // 8bits
#define STR_RES_CRUSH 402  // crush
#define STR_RES___NOISE 403  // noise
#define STR_RES_VOWEL 404  // vowel
#define STR_RES_WAVES 405  // waves
#define STR_RES_TAMPUR 406  // tampur
#define STR_RES_DIGITL 407  // digitl
#define STR_RES_METALL 408  // metall
#define STR_RES_BOWED 409  // bowed
#define STR_RES_SLAP 410  // slap
#define STR_RES_ORGAN 411  // organ
#define STR_RES_MALE 412  // male
#define STR_RES_USER 413  // user
#define STR_RES_BELISH 414  // belish
#define STR_RES_POLATD 415  // polatd
#define STR_RES_CELLO 416  // cello
#define STR_RES_CLPSWP 417  // clpswp
#define STR_RES_FEMALE 418  // female
#define STR_RES_FMTVOC 419  // fmtvoc
#define STR_RES_FRMNT2 420  // frmnt2
#define STR_RES_RES3HP 421  // res3hp
#define STR_RES_ELECTP 422  // electp
#define STR_RES_VIBES 423  // vibes
#define STR_RES_WAVQUENCE 424  // wavquence
#define STR_RES__LPF 425  // lpf
#define STR_RES_SSM 426  // ssm
#define STR_RES_SVF 427  // svf
#define STR_RES_DSP 428  // dsp
#define STR_RES_PVK 429  // pvk
#define STR_RES_4PM 430  // 4pm
#define STR_RES_DLY 431  // dly
#define STR_RES_SP 432  // sp
#define STR_RES_SPLASH 433  // splash
#define STR_RES__FILTER 434  // filter
#define STR_RES_PRESET 435  // preset
#define STR_RES____OFF 436  // off
#define STR_RES_CS80 437  // cs80
#define STR_RES_IR31 438  // ir31
#define STR_RES__PVK 439  // pvk
#define STR_RES_SMR4 440  // smr4
#define STR_RES_EQUAL 441  // equal
#define STR_RES_JUST 442  // just
#define STR_RES_PYTHAG 443  // pythag
#define STR_RES_1_4_EB 444  // 1/4 eb
#define STR_RES_1_4_E 445  // 1/4 e
#define STR_RES_1_4_EA 446  // 1/4 ea
#define STR_RES_BHAIRA 447  // bhaira
#define STR_RES_GUNAKR 448  // gunakr
#define STR_RES_MARWA 449  // marwa
#define STR_RES_SHREE 450  // shree
#define STR_RES_PURVI 451  // purvi
#define STR_RES_BILAWA 452  // bilawa
#define STR_RES_YAMAN 453  // yaman
#define STR_RES_KAFI 454  // kafi
#define STR_RES_BHIMPA 455  // bhimpa
#define STR_RES_DARBAR 456  // darbar
#define STR_RES_BAGESH 457  // bagesh
#define STR_RES_RAGESH 458  // ragesh
#define STR_RES_KHAMAJ 459  // khamaj
#define STR_RES_MIMAL 460  // mi'mal
#define STR_RES_PARAME 461  // parame
#define STR_RES_RANGES 462  // ranges
#define STR_RES_GANGES 463  // ganges
#define STR_RES_KAMESH 464  // kamesh
#define STR_RES_PALAS_ 465  // palas
#define STR_RES_NATBHA 466  // natbha
#define STR_RES_M_KAUN 467  // m.kaun
#define STR_RES_BAIRAG 468  // bairag
#define STR_RES_B_TODI 469  // b.todi
#define STR_RES_CHANDR 470  // chandr
#define STR_RES_KAUSHI 471  // kaushi
#define STR_RES_JOGESH 472  // jogesh
#define STR_RES_RASIA 473  // rasia
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
