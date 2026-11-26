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
#define STR_RES_OSCILLATOR_1 65  // oscillator 1
#define STR_RES_OSCILLATOR_2 66  // oscillator 2
#define STR_RES_MIXER 67  // mixer
#define STR_RES_FILTER 68  // filter
#define STR_RES_FILTERS 69  // filter+
#define STR_RES_MODE_1 70  // mode 1
#define STR_RES_MODE_2 71  // mode 2
#define STR_RES_MD1 72  // md1
#define STR_RES_MD2 73  // md2
#define STR_RES_ENVELOPE_1 74  // envelope 1
#define STR_RES_ENVELOPE_2 75  // envelope 2
#define STR_RES_SEQUENCER 76  // sequencer
#define STR_RES_ARPEGGIO 77  // arpeggio
#define STR_RES_CH1 78  // ch1
#define STR_RES_CH2 79  // ch2
#define STR_RES_11 80  // 1
#define STR_RES_12 81  // 2
#define STR_RES_STEP_SEQUENCER 82  // step sequencer
#define STR_RES_KEYBOARD 83  // keyboard
#define STR_RES_MIDI 84  // midi
#define STR_RES_SYSTEM 85  // system
#define STR_RES_PERFORMANCE 86  // performance
#define STR_RES_PARAM__1 87  // param. 1
#define STR_RES_PARAM__2 88  // param. 2
#define STR_RES_PR1 89  // pr1
#define STR_RES_PR2 90  // pr2
#define STR_RES_FX_ 91  // fx.
#define STR_RES_FX_PROG_ 92  // fx prog.
#define STR_RES_LPF 93  // lpf
#define STR_RES_BPF 94  // bpf
#define STR_RES_HPF 95  // hpf
#define STR_RES_LPL 96  // lp<
#define STR_RES_BPL 97  // bp<
#define STR_RES_HPL 98  // hp<
#define STR_RES_SLP 99  // +lp
#define STR_RES_SBP 100  // +bp
#define STR_RES_SHP 101  // +hp
#define STR_RES_GLP 102  // >lp
#define STR_RES_GBP 103  // >bp
#define STR_RES_GHP 104  // >hp
#define STR_RES_LP4 105  // lp4
#define STR_RES_LP3 106  // lp3
#define STR_RES_LP2 107  // lp2
#define STR_RES_LP1 108  // lp1
#define STR_RES_HP1 109  // hp1
#define STR_RES_HP2 110  // hp2
#define STR_RES_HP3 111  // hp3
#define STR_RES_BP2 112  // bp2
#define STR_RES_BP4 113  // bp4
#define STR_RES_NOTCH 114  // notch
#define STR_RES_PHASER 115  // phaser
#define STR_RES_H2LP 116  // h2lp
#define STR_RES_H3LP 117  // h3lp
#define STR_RES_NSLP 118  // n+lp
#define STR_RES_PSLP 119  // p+lp
#define STR_RES_LP 120  // lp
#define STR_RES_BP 121  // bp
#define STR_RES_HP 122  // hp
#define STR_RES_AP 123  // ap
#define STR_RES_LIQUID 124  // liquid
#define STR_RES_MS 125  // ms
#define STR_RES_WOBBLY 126  // wobbly
#define STR_RES_WHACKY 127  // whacky
#define STR_RES_PW1 128  // pw1
#define STR_RES_PW2 129  // pw2
#define STR_RES_51 130  // 1
#define STR_RES_52 131  // 2
#define STR_RES_5 132  // 
#define STR_RES_5F 133  // f
#define STR_RES_MIX 134  // mix
#define STR_RES_NOI 135  // noi
#define STR_RES_SUB 136  // sub
#define STR_RES_CUT 137  // cut
#define STR_RES_RES 138  // res
#define STR_RES_VCA 139  // vca
#define STR_RES_CV1 140  // cv1
#define STR_RES_CV2 141  // cv2
#define STR_RES_TR1 142  // tr1
#define STR_RES_A1 143  // a1
#define STR_RES_D1 144  // d1
#define STR_RES_S1 145  // s1
#define STR_RES_R1 146  // r1
#define STR_RES_TR2 147  // tr2
#define STR_RES_A2 148  // a2
#define STR_RES_D2 149  // d2
#define STR_RES_S2 150  // s2
#define STR_RES_R2 151  // r2
#define STR_RES__ATK 152  // atk
#define STR_RES__LF1 153  // lf1
#define STR_RES__LF2 154  // lf2
#define STR_RES_IN1 155  // in1
#define STR_RES_IN2 156  // in2
#define STR_RES_OUT 157  // out
#define STR_RES___OFF 158  // off
#define STR_RES_ADD 159  // add
#define STR_RES_PRD 160  // prd
#define STR_RES_MAX 161  // max
#define STR_RES_MIN 162  // min
#define STR_RES__XOR 163  // xor
#define STR_RES_GE 164  // >=
#define STR_RES_LE 165  // <=
#define STR_RES_QTZ 166  // qtz
#define STR_RES_LAG 167  // lag
#define STR_RES_PWM1 168  // pwm1
#define STR_RES_PWM2 169  // pwm2
#define STR_RES_OSC1 170  // osc1
#define STR_RES_OSC2 171  // osc2
#define STR_RES_OSC1S2 172  // osc1+2
#define STR_RES_FINE 173  // fine
#define STR_RES__MIX 174  // mix
#define STR_RES_NOISE 175  // noise
#define STR_RES_SUBOSC 176  // subosc
#define STR_RES_CUTOFF 177  // cutoff
#define STR_RES_RESO 178  // reso
#define STR_RES__VCA 179  // vca
#define STR_RES_CV_1 180  // cv 1
#define STR_RES_CV_2 181  // cv 2
#define STR_RES_TRG_E1 182  // trg e1
#define STR_RES_ATK__1 183  // atk. 1
#define STR_RES_DEC__1 184  // dec. 1
#define STR_RES_SUS__1 185  // sus. 1
#define STR_RES_REL__1 186  // rel. 1
#define STR_RES_TRG_E2 187  // trg e2
#define STR_RES_ATK__2 188  // atk. 2
#define STR_RES_DEC__2 189  // dec. 2
#define STR_RES_SUS__2 190  // sus. 2
#define STR_RES_REL__2 191  // rel. 2
#define STR_RES_ATK1S2 192  // atk1+2
#define STR_RES__LFO_1 193  // lfo 1
#define STR_RES__LFO_2 194  // lfo 2
#define STR_RES_DISTRT 195  // distrt
#define STR_RES_CRUSHR 196  // crushr
#define STR_RES_SCMBFL 197  // +cmbfl
#define STR_RES_CMBFL 198  // -cmbfl
#define STR_RES_RINGMD 199  // ringmd
#define STR_RES_DELAY 200  // delay
#define STR_RES_FB_DLY 201  // fb dly
#define STR_RES_DUBDLY 202  // dubdly
#define STR_RES__FBDLY 203  // !fbdly
#define STR_RES__DBDLY 204  // !dbdly
#define STR_RES__16_DL 205  // /16 dl
#define STR_RES__12_DL 206  // /12 dl
#define STR_RES__8_DLY 207  // /8 dly
#define STR_RES_3_16DL 208  // 3/16dl
#define STR_RES_LOOPER 209  // looper
#define STR_RES_PITCH 210  // pitch
#define STR_RES_LGF 211  // l>f
#define STR_RES_HGF 212  // h>f
#define STR_RES_FGL 213  // f>l
#define STR_RES_FGH 214  // f>h
#define STR_RES_GFX 215  // >fx
#define STR_RES_LF1 216  // lf1
#define STR_RES_LF2 217  // lf2
#define STR_RES_SEQ 218  // seq
#define STR_RES__SQ1 219  // sq1
#define STR_RES__SQ2 220  // sq2
#define STR_RES_ARP 221  // arp
#define STR_RES_WHL 222  // whl
#define STR_RES_AFT 223  // aft
#define STR_RES_BND 224  // bnd
#define STR_RES_OFS 225  // ofs
#define STR_RES__CV1 226  // cv1
#define STR_RES__CV2 227  // cv2
#define STR_RES_CV3 228  // cv3
#define STR_RES_CV4 229  // cv4
#define STR_RES_CCA 230  // ccA
#define STR_RES_CCB 231  // ccB
#define STR_RES_BRE 232  // bre
#define STR_RES_PED 233  // ped
#define STR_RES__NOI 234  // noi
#define STR_RES_EN1 235  // en1
#define STR_RES_EN2 236  // en2
#define STR_RES_VEL 237  // vel
#define STR_RES_RND 238  // rnd
#define STR_RES_NOT 239  // not
#define STR_RES_GAT 240  // gat
#define STR_RES_AUD 241  // aud
#define STR_RES_OP1 242  // op1
#define STR_RES_OP2 243  // op2
#define STR_RES_E4 244  // =4
#define STR_RES_E8 245  // =8
#define STR_RES_E16 246  // =16
#define STR_RES_E32 247  // =32
#define STR_RES_LFO_1 248  // lfo 1
#define STR_RES_LFO_2 249  // lfo 2
#define STR_RES_STPSEQ 250  // stpseq
#define STR_RES_STPSQ1 251  // stpsq1
#define STR_RES_STPSQ2 252  // stpsq2
#define STR_RES__ARP 253  // arp
#define STR_RES_MWHEEL 254  // mwheel
#define STR_RES_AFTTCH 255  // afttch
#define STR_RES_BENDER 256  // bender
#define STR_RES_OFFSET 257  // offset
#define STR_RES__CV_1 258  // cv 1
#define STR_RES__CV_2 259  // cv 2
#define STR_RES_CV_3 260  // cv 3
#define STR_RES_CV_4 261  // cv 4
#define STR_RES_CC_A 262  // cc A
#define STR_RES_CC_B 263  // cc B
#define STR_RES_BREATH 264  // breath
#define STR_RES_PEDAL 265  // pedal
#define STR_RES__NOISE 266  // noise
#define STR_RES_ENV_1 267  // env 1
#define STR_RES_ENV_2 268  // env 2
#define STR_RES_VELO 269  // velo
#define STR_RES_RANDOM 270  // random
#define STR_RES_NOTE 271  // note
#define STR_RES_GATE 272  // gate
#define STR_RES_AUDIO 273  // audio
#define STR_RES_OP__1 274  // op. 1
#define STR_RES_OP__2 275  // op. 2
#define STR_RES_E_4 276  // = 4
#define STR_RES_E_8 277  // = 8
#define STR_RES_E_16 278  // = 16
#define STR_RES_E_32 279  // = 32
#define STR_RES_PATCH 280  // patch
#define STR_RES_SEQUENCE 281  // sequence
#define STR_RES_SAVE_MIDI_KBD 282  // save midi/kbd
#define STR_RES_SETTINGS_ 283  // settings?
#define STR_RES_START_FULL_MIDI 284  // start full midi
#define STR_RES_BACKUP_ 285  // backup?
#define STR_RES_BROWSE 286  // browse
#define STR_RES_SAVE 287  // save
#define STR_RES_COMPARE 288  // compare
#define STR_RES_ 289  // ----
#define STR_RES_V 290  // v
#define STR_RES_MUTABLE___YA8_05 291  // mutable   YA.05
#define STR_RES_INSTRUMENTS_671 292  // instruments -1
#define STR_RES_SHRUTHI_CLASSIC 293  // shruthi classic
#define STR_RES_4_KNOBS 294  // (4 knobs)
#define STR_RES_SHRUTHI_XT 295  // shruthi xt
#define STR_RES_CLASSIC_FCD72 296  // classic (fcd72)
#define STR_RES__SHRUTHI_XT 297  // shruthi xt
#define STR_RES_FULL_CONTROL 298  // (full control)
#define STR_RES_LETS_JAM_ 299  // let's jam!
#define STR_RES_EXTERN 300  // extern
#define STR_RES_SUM 301  // sum
#define STR_RES_SYNC 302  // sync
#define STR_RES_RING 303  // ring
#define STR_RES_XOR 304  // xor
#define STR_RES_FUZZ 305  // fuzz
#define STR_RES_GG4 306  // >>4
#define STR_RES_GG8 307  // >>8
#define STR_RES_FOLD 308  // fold
#define STR_RES_BITS 309  // bits
#define STR_RES_DUO 310  // duo
#define STR_RES_2STEPS 311  // 2steps
#define STR_RES_4STEPS 312  // 4steps
#define STR_RES_8STEPS 313  // 8steps
#define STR_RES_SEQMIX 314  // seqmix
#define STR_RES_STP 315  // stp
#define STR_RES___ARP 316  // arp
#define STR_RES__SEQ 317  // seq
#define STR_RES_FREE 318  // free
#define STR_RES_SLAVE 319  // slave
#define STR_RES_MASTER 320  // master
#define STR_RES_1SHOT 321  // 1shot
#define STR_RES_1_1 322  // 1/1
#define STR_RES_1_2 323  // 1/2
#define STR_RES_1_3 324  // 1/3
#define STR_RES_1_4 325  // 1/4
#define STR_RES_1_6 326  // 1/6
#define STR_RES_1_8 327  // 1/8
#define STR_RES__12 328  // /12
#define STR_RES__16 329  // /16
#define STR_RES__24 330  // /24
#define STR_RES__32 331  // /32
#define STR_RES__48 332  // /48
#define STR_RES__96 333  // /96
#define STR_RES_SWING 334  // swing
#define STR_RES_SHUFFLE 335  // shuffle
#define STR_RES_PUSH 336  // push
#define STR_RES__LAG 337  // lag
#define STR_RES_HUMAN 338  // human
#define STR_RES_MONKEY 339  // monkey
#define STR_RES__OFF 340  // off
#define STR_RES_THRU 341  // thru
#define STR_RES___SEQ 342  // seq
#define STR_RES_CTRL 343  // ctrl
#define STR_RES_FULL 344  // full
#define STR_RES_1TV 345  // 1~|
#define STR_RES_2T1 346  // 2~1
#define STR_RES_3T2 347  // 3~2
#define STR_RES_4T3 348  // 4~3
#define STR_RES_5T4 349  // 5~4
#define STR_RES_6T5 350  // 6~5
#define STR_RES_7T6 351  // 7~6
#define STR_RES_8T7 352  // 8~7
#define STR_RES_TRI 353  // tri
#define STR_RES_SQR 354  // sqr
#define STR_RES_S_H 355  // s&h
#define STR_RES_RAMP 356  // ramp
#define STR_RES_STEP 357  // step
#define STR_RES_3 358  // 
#define STR_RES_4 359  // 
#define STR_RES_34 360  // 
#define STR_RES__ 361  // ?
#define STR_RES_PLAYED 362  // played
#define STR_RES_OFF 363  // off
#define STR_RES_ON 364  // on
#define STR_RES_SQ1 365  // sq1
#define STR_RES__TR1 366  // tr1
#define STR_RES_PL1 367  // pl1
#define STR_RES_SQ2 368  // sq2
#define STR_RES__TR2 369  // tr2
#define STR_RES_PL2 370  // pl2
#define STR_RES_CLICK 371  // click
#define STR_RES_GLITCH 372  // glitch
#define STR_RES_BLOW 373  // blow
#define STR_RES_METAL 374  // metal
#define STR_RES_POP 375  // pop
#define STR_RES_NONE 376  // none
#define STR_RES_SAW 377  // saw
#define STR_RES_CSAW 378  // csaw
#define STR_RES_OLDSAW 379  // oldsaw
#define STR_RES_SQUARE 380  // square
#define STR_RES_DPWM 381  // dpwm
#define STR_RES_TRIANG 382  // triang
#define STR_RES_ZSAW 383  // zsaw
#define STR_RES_LPZSAW 384  // lpzsaw
#define STR_RES_PKZSAW 385  // pkzsaw
#define STR_RES_HPZSAW 386  // hpzsaw
#define STR_RES_LPZPULSE 387  // lpzpulse
#define STR_RES_PKZPULSE 388  // pkzpulse
#define STR_RES_HPZPULSE 389  // hpzpulse
#define STR_RES_ZSYNC 390  // zsync
#define STR_RES_ZTRI 391  // ztri
#define STR_RES_PAD 392  // pad
#define STR_RES_QPWM 393  // qpwm
#define STR_RES_FM 394  // fm
#define STR_RES_FMFB 395  // fmfb
#define STR_RES_8BITS 396  // 8bits
#define STR_RES_CRUSH 397  // crush
#define STR_RES___NOISE 398  // noise
#define STR_RES_VOWEL 399  // vowel
#define STR_RES_WAVES 400  // waves
#define STR_RES_TAMPUR 401  // tampur
#define STR_RES_DIGITL 402  // digitl
#define STR_RES_METALL 403  // metall
#define STR_RES_BOWED 404  // bowed
#define STR_RES_SLAP 405  // slap
#define STR_RES_ORGAN 406  // organ
#define STR_RES_MALE 407  // male
#define STR_RES_USER 408  // user
#define STR_RES_BELISH 409  // belish
#define STR_RES_POLATD 410  // polatd
#define STR_RES_CELLO 411  // cello
#define STR_RES_CLPSWP 412  // clpswp
#define STR_RES_FEMALE 413  // female
#define STR_RES_FMTVOC 414  // fmtvoc
#define STR_RES_FRMNT2 415  // frmnt2
#define STR_RES_RES3HP 416  // res3hp
#define STR_RES_ELECTP 417  // electp
#define STR_RES_VIBES 418  // vibes
#define STR_RES_WAVQUENCE 419  // wavquence
#define STR_RES__LPF 420  // lpf
#define STR_RES_SSM 421  // ssm
#define STR_RES_SVF 422  // svf
#define STR_RES_DSP 423  // dsp
#define STR_RES_PVK 424  // pvk
#define STR_RES_4PM 425  // 4pm
#define STR_RES_DLY 426  // dly
#define STR_RES_SP 427  // sp
#define STR_RES_SPLASH 428  // splash
#define STR_RES__FILTER 429  // filter
#define STR_RES_PRESET 430  // preset
#define STR_RES_EQUAL 431  // equal
#define STR_RES_JUST 432  // just
#define STR_RES_PYTHAG 433  // pythag
#define STR_RES_1_4_EB 434  // 1/4 eb
#define STR_RES_1_4_E 435  // 1/4 e
#define STR_RES_1_4_EA 436  // 1/4 ea
#define STR_RES_BHAIRA 437  // bhaira
#define STR_RES_GUNAKR 438  // gunakr
#define STR_RES_MARWA 439  // marwa
#define STR_RES_SHREE 440  // shree
#define STR_RES_PURVI 441  // purvi
#define STR_RES_BILAWA 442  // bilawa
#define STR_RES_YAMAN 443  // yaman
#define STR_RES_KAFI 444  // kafi
#define STR_RES_BHIMPA 445  // bhimpa
#define STR_RES_DARBAR 446  // darbar
#define STR_RES_BAGESH 447  // bagesh
#define STR_RES_RAGESH 448  // ragesh
#define STR_RES_KHAMAJ 449  // khamaj
#define STR_RES_MIMAL 450  // mi'mal
#define STR_RES_PARAME 451  // parame
#define STR_RES_RANGES 452  // ranges
#define STR_RES_GANGES 453  // ganges
#define STR_RES_KAMESH 454  // kamesh
#define STR_RES_PALAS_ 455  // palas
#define STR_RES_NATBHA 456  // natbha
#define STR_RES_M_KAUN 457  // m.kaun
#define STR_RES_BAIRAG 458  // bairag
#define STR_RES_B_TODI 459  // b.todi
#define STR_RES_CHANDR 460  // chandr
#define STR_RES_KAUSHI 461  // kaushi
#define STR_RES_JOGESH 462  // jogesh
#define STR_RES_RASIA 463  // rasia
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
