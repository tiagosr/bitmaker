#ifndef NES_H
#define NES_H

#include <cstdint>

class CPU_2A03
{
public:
    CPU_2A03();
    uint8_t A, P, X, Y, S, CYC;
    union {
        uint16_t PC;
        uint8_t PCL, PCH; // assuming little-endian
    };
    union {
        uint16_t AB;
        uint8_t ABL, ABH; // assuming little-endian
    };
    uint8_t DATA;
    uint8_t _DL, _DB, _ADL, _ADH, _SB, _AI, _BI, _IR, _PCLS, _PCHS;
    uint8_t _ADDC, _HC, _ACR, _AVR, _ADD, _PCLC;
    uint16_t _CD, _DOR;

    bool RESET, IRQ, NMI, WR;

    void tick();

    const uint64_t sig_DL_DB    = 0x8000000000000000ll;
    const uint64_t sig_DL_ADL   = 0x4000000000000000ll;
    const uint64_t sig_DL_ADH   = 0x2000000000000000ll;
    const uint64_t sig_0_ADH    = 0x1800000000000000ll;
    const uint64_t sig_0_ADH0   = 0x1000000000000000ll;
    const uint64_t sig_0_ADH1_7 = 0x0800000000000000ll;
    const uint64_t sig_ADH_ABH  = 0x0400000000000000ll;
    const uint64_t sig_ADL_ABL  = 0x0200000000000000ll;
    const uint64_t sig_PCL_PCL  = 0x0100000000000000ll;
    const uint64_t sig_ADL_PCL  = 0x0080000000000000ll;
    const uint64_t sig_I_PC     = 0x0040000000000000ll;
    const uint64_t sig_PCL_DB   = 0x0020000000000000ll;
    const uint64_t sig_PCL_ADL  = 0x0010000000000000ll;
    const uint64_t sig_PCH_PCH  = 0x0008000000000000ll;
    const uint64_t sig_ADH_PCH  = 0x0004000000000000ll;
    const uint64_t sig_PCH_DB   = 0x0002000000000000ll;
    const uint64_t sig_PCH_ADH  = 0x0001000000000000ll;
    const uint64_t sig_SB_ADH   = 0x0000800000000000ll;
    const uint64_t sig_SB_DB    = 0x0000400000000000ll;
    const uint64_t sig_0_ADL2_0 = 0x0000380000000000ll;
    const uint64_t sig_0_ADL2   = 0x0000200000000000ll;
    const uint64_t sig_0_ADL1   = 0x0000100000000000ll;
    const uint64_t sig_0_ADL0   = 0x0000080000000000ll;
    const uint64_t sig_S_ADL    = 0x0000040000000000ll;
    const uint64_t sig_SB_S     = 0x0000020000000000ll;
    const uint64_t sig_S_S      = 0x0000010000000000ll;
    const uint64_t sig_S_SB     = 0x0000008000000000ll;
    const uint64_t sig__DB_ADD  = 0x0000004000000000ll;
    const uint64_t sig_DB_ADD   = 0x0000002000000000ll;
    const uint64_t sig_ADL_ADD  = 0x0000001000000000ll;
    const uint64_t sig_I_ADDC   = 0x0000000800000000ll;
    const uint64_t sig_DAA      = 0x0000000400000000ll;
    const uint64_t sig_DSA      = 0x0000000200000000ll;
    const uint64_t sig_SUMS     = 0x0000000100000000ll;
    const uint64_t sig_ANDS     = 0x0000000080000000ll;
    const uint64_t sig_EORS     = 0x0000000040000000ll;
    const uint64_t sig_ORS      = 0x0000000020000000ll;
    const uint64_t sig_SRS      = 0x0000000010000000ll;
    const uint64_t sig_ADD_ADL  = 0x0000000008000000ll;
    const uint64_t sig_ADD_SB   = 0x0000000006000000ll;
    const uint64_t sig_ADD_SB0_6= 0x0000000004000000ll;
    const uint64_t sig_ADD_SB7  = 0x0000000002000000ll;
    const uint64_t sig_0_ADD    = 0x0000000001000000ll;
    const uint64_t sig_SB_ADD   = 0x0000000000800000ll;
    const uint64_t sig_SB_AC    = 0x0000000000400000ll;
    const uint64_t sig_AC_DB    = 0x0000000000200000ll;
    const uint64_t sig_AC_SB    = 0x0000000000100000ll;
    const uint64_t sig_SB_X     = 0x0000000000080000ll;
    const uint64_t sig_X_SB     = 0x0000000000040000ll;
    const uint64_t sig_SB_Y     = 0x0000000000020000ll;
    const uint64_t sig_Y_SB     = 0x0000000000010000ll;
    const uint64_t sig_P_DB     = 0x0000000000008000ll;
    const uint64_t sig_DB0_C    = 0x0000000000004000ll;
    const uint64_t sig_IR5_C    = 0x0000000000002000ll;
    const uint64_t sig_ACR_C    = 0x0000000000001000ll;
    const uint64_t sig_DB1_Z    = 0x0000000000000800ll;
    const uint64_t sig_DBZ_Z    = 0x0000000000000400ll;
    const uint64_t sig_DB2_I    = 0x0000000000000200ll;
    const uint64_t sig_IR5_I    = 0x0000000000000100ll;
    const uint64_t sig_DB3_D    = 0x0000000000000080ll;
    const uint64_t sig_IR5_D    = 0x0000000000000040ll;
    const uint64_t sig_DB6_V    = 0x0000000000000020ll;
    const uint64_t sig_AVR_V    = 0x0000000000000010ll;
    const uint64_t sig_1_V      = 0x0000000000000008ll;
    const uint64_t sig_0_V      = 0x0000000000000004ll;
    const uint64_t sig_DB7_N    = 0x0000000000000002ll;

#define C(ones,zeroes,g,clk) \
    (ones<<24 | zeroes<<16 | \
    (g==1?0x800:(g==2?0x400:(g==3?0x200:0))) | \
    (clk==0?0x100:(clk==1?0x80:(clk==2?0x40:(clk==3?0x20:(clk==4?0x10:(clk==5?8:0)))))))

    constexpr uint32_t decode_rom[130] = {
        C(0b10000100, 0b01100000, 3, 9), // 002: STY
        C(0b00010000, 0b00001100, 1, 3), // 003: T3INDYA
        C(0b00011000, 0b00000100, 1, 2), // 004: T2ABSY
        C(0b11000000, 0b00110000, 3, 0), // 005: T0CPYINY
        C(0b10011000, 0b01100100, 3, 0), // 006: T0TYAA
        C(0b10001000, 0b00110100, 3, 0), // 007: T0DEYINY
        C(0b00000000, 0b11111100, 3, 5), // 008: T5INT
        C(0b10000000, 0b01000000, 2, 9), // 009: LDXSDX
        C(0b00010100, 0b00000000, 0, 2), // 010: T2ANYX
        C(0b00000000, 0b00011100, 1, 2), // 011: T2XIND
        C(0b10001000, 0b01110100, 2, 0), // 012: T0TXAA
        C(0b11001000, 0b00110100, 2, 0), // 013: T0DEX
        C(0b11100000, 0b00010000, 3, 0), // 014: T0CPXINX
        C(0b10011000, 0b01100100, 2, 0), // 015: T0TXS
        C(0b10000000, 0b01100000, 2, 9), // 016: SDX
        C(0b10100000, 0b01000000, 2, 0), // 017: T0TALDTSX
        C(0b11001000, 0b00110100, 2, 1), // 018: T1DEX
        C(0b11101000, 0b00010100, 3, 1), // 019: T1INX
        C(0b10111000, 0b01000100, 2, 0), // 020: T0TSX
        C(0b10001000, 0b00110100, 3, 1), // 021: T1DEYINY
        C(0b10100100, 0b01000000, 3, 0), // 022: T0LDY1
        C(0b10100000, 0b01010000, 3, 0), // 023: T0LDY2TAY
        C(0b00000000, 0b10010100, 3, 2), // 024: CCC
        C(0b00100000, 0b11011100, 3, 0), // 025: T0JSR
        C(0b00001000, 0b10110100, 3, 0), // 026: T0PSHASHP
        C(0b01100000, 0b10011100, 3, 4), // 027: T4RTS
        C(0b00101000, 0b10010100, 3, 3), // 028: T3PLAPLPA
        C(0b01000000, 0b10111100, 3, 5), // 029: T5RTI
        C(0b01100000, 0b10000000, 2, 9), // 030: RORRORA
        C(0b00100000, 0b11011100, 3, 2), // 031: T2JSR
        C(0b01001100, 0b10010000, 3, 9), // 032: JMPA
        C(0b00000000, 0b00000000, 0, 2), // 033: T2
        C(0b00001100, 0b00010000, 0, 2), // 034: T2EXT
        C(0b01000000, 0b10011100, 3, 9), // 035: RTIRTS
        C(0b00000000, 0b00011100, 1, 4), // 036: T4XIND
        C(0b00000000, 0b00000000, 0, 0), // 037: T0A
        C(0b00000000, 0b00001000, 0, 2), // 038: T2NANYABS
        C(0b01000000, 0b10111100, 3, 4), // 039: T4RTIA
        C(0b00000000, 0b11011100, 3, 4), // 040: T4JSRINT
        C(0b00000000, 0b10010000, 3, 3), // 041: NAME1:T3_RTI_RTS_JSR_JMP_INT_PULA_PUPL
        C(0b00010000, 0b00001100, 1, 3), // 042: T3INDYB
        C(0b00000000, 0b00011100, 1, 3), // 043: T3XIND
        C(0b00010000, 0b00001100, 1, 4), // 044: T4INDYA
        C(0b00010000, 0b00001100, 1, 2), // 045: T2INDY
        C(0b00011000, 0b00000000, 0, 3), // 046: T3ABSXYA
        C(0b00101000, 0b10010100, 3, 9), // 047: PULAPULP
        C(0b11100000, 0b00000000, 2, 9), // 048: INC
        C(0b01000000, 0b10100000, 1, 0), // 049: T0EOR
        C(0b11000000, 0b00100000, 1, 0), // 050: T0CMP
        C(0b11000000, 0b00010000, 3, 0), // 051: NAME2:T0_CPX_CPY_INX_INY
        C(0b01100000, 0b00000000, 1, 0), // 052: T0ADCSBC
        C(0b11100000, 0b00000000, 1, 0), // 053: T0SBC
        C(0b00100000, 0b11000000, 2, 9), // 054: ROLROLA
        C(0b01001100, 0b10010000, 3, 3), // 055: T3JMP
        C(0b00000000, 0b11100000, 1, 0), // 056: T0ORA
        C(0b00000000, 0b11000000, 2, 9), // 057: NAME8:ROL_ROLA_ASL_ASLA
        C(0b10011000, 0b01100100, 3, 0), // 058: T0TYAB
        C(0b10001000, 0b01110100, 2, 0), // 059: T0TXAB
        C(0b01100000, 0b00000000, 1, 1), // 060: T1ADCSBCA
        C(0b00000000, 0b10000000, 1, 1), // 061: NAME7:T1_AND_EOR_OR_ADC
        C(0b00001000, 0b10010100, 2, 1), // 062: NAME4:T1_ASLA_ROLA_LSRA
        C(0b01101000, 0b10010100, 3, 0), // 063: T0PULA
        C(0b00011000, 0b00000000, 0, 4), // 064: T4ABSXYA
        C(0b00010000, 0b00001100, 1, 5), // 065: T5INDY
        C(0b10100000, 0b01000000, 1, 0), // 066: T0LDA
        C(0b00000000, 0b00000000, 1, 0), // 067: T0G1
        C(0b00100000, 0b11000000, 1, 0), // 068: T0AND
        C(0b00100100, 0b11010000, 3, 0), // 069: T0BITA
        C(0b00001000, 0b10010100, 2, 0), // 070: NAME6:T0_ASLA_ROLA_LSRA
        C(0b10101000, 0b01010100, 2, 0), // 071: T0TAX
        C(0b10101000, 0b01010100, 3, 0), // 072: T0TAY
        C(0b01001000, 0b10010100, 2, 0), // 073: T0LSRA
        C(0b01000000, 0b10000000, 2, 9), // 074: LSRLSRA
        C(0b00100000, 0b11011100, 3, 5), // 075: T5JSRA
        C(0b00010000, 0b00001100, 3, 2), // 076: T2BR
        C(0b00000000, 0b11111100, 3, 2), // 077: T2INT
        C(0b00100000, 0b11011100, 3, 3), // 078: T3JSR
        C(0b00000100, 0b00001000, 0, 2), // 079: T2ANYZP
        C(0b00000000, 0b00001100, 1, 2), // 080: T2ANYIND
        C(0b00000000, 0b00000000, 0, 4), // 081: T4
        C(0b00000000, 0b00000000, 0, 3), // 082: T3
        C(0b00000000, 0b10111100, 3, 0), // 083: T0RTIINT
        C(0b01001100, 0b10010000, 3, 0), // 084: T0JMP
        C(0b00000000, 0b10010100, 3, 2), // 085: NAME3:T2_RTI_RTS_JSR_INT_PULA_PUPLP_PSHA_PSHP
        C(0b01100000, 0b10011100, 3, 5), // 086: T5RTS
        C(0b00001000, 0b00000000, 0, 2), // 087: T2ANYABS
        C(0b10000000, 0b01100000, 1, 9), // 088: STA
        C(0b01001000, 0b10110100, 3, 2), // 089: T2PSHA
        C(0b00010000, 0b00001100, 3, 0), // 090: T0BR
        C(0b00001000, 0b10010100, 3, 9), // 091: PSHPULA
        C(0b00000000, 0b00011100, 1, 5), // 092: T5XIND
        C(0b00001000, 0b00000000, 0, 3), // 093: T3ANYABS
        C(0b00010000, 0b00001100, 1, 4), // 094: T4INDYB
        C(0b00011000, 0b00000000, 0, 3), // 095: T3ABSXYB
        C(0b00000000, 0b10111100, 3, 9), // 096: RTIINT
        C(0b00100000, 0b11011100, 3, 9), // 097: JSR
        C(0b01001100, 0b10010000, 3, 9), // 098: JMPB
        C(0b11000000, 0b00011000, 3, 1), // 099: T1CPX2CY2
        C(0b00001000, 0b11010100, 2, 1), // 100: T1ASLARLA
        C(0b11001100, 0b00010000, 3, 1), // 101: T1CPX1CY1
        C(0b11000000, 0b00100000, 1, 1), // 102: T1CMP
        C(0b01100000, 0b00000000, 1, 1), // 103: T1ADCSBCB
        C(0b00000000, 0b11000000, 2, 9), // 104: NAME5:ROL_ROLA_ASL_ASLA
        C(0b01000000, 0b00000000, 2, 9), // 105: LSRRADCIC
        C(0b00100100, 0b11010000, 3, 1), // 106: T1BIT
        C(0b00001000, 0b11110100, 3, 2), // 107: T2PSHP
        C(0b00000000, 0b11111100, 3, 4), // 108: T4INT
        C(0b10000000, 0b01100000, 0, 9), // 109: STASTYSTX
        C(0b00011000, 0b00000000, 0, 4), // 110: T4ABSXYB
        C(0b00000000, 0b00001100, 1, 5), // 111: T5ANYIND
        C(0b00000100, 0b00011000, 0, 2), // 112: T2ZP
        C(0b00001100, 0b00010000, 0, 3), // 113: T3ABS
        C(0b00010100, 0b00001000, 0, 3), // 114: T3ZPX
        C(0b00001000, 0b10110100, 3, 2), // 115: T2PSHASHP
        C(0b01000000, 0b10011100, 3, 5), // 116: T5RTIRTS
        C(0b00100000, 0b11011100, 3, 5), // 117: T5JSRB
        C(0b01001100, 0b10010000, 3, 5), // 118: T4JMP
        C(0b01001100, 0b10110000, 3, 2), // 119: T2JMPABS
        C(0b00101000, 0b10010100, 3, 3), // 120: T3PLAPLPB
        C(0b00010000, 0b00001100, 3, 3), // 121: T3BR
        C(0b00100100, 0b11010000, 3, 0), // 122: T0BITB
        C(0b01000000, 0b10111100, 3, 4), // 123: T4RTIB
        C(0b00101000, 0b11010100, 3, 0), // 124: T0PULP
        C(0b00001000, 0b10010100, 3, 9), // 125: PSHPULB
        C(0b10111000, 0b01000100, 3, 9), // 126: CLV
        C(0b00011000, 0b11000100, 3, 0), // 127: T0CLCSEC
        C(0b01011000, 0b10000100, 3, 0), // 128: T0CLISEI
        C(0b11011000, 0b00000100, 3, 0), // 129: T0CLDSED
        C(0b00000000, 0b10000000, 0, 9), // 130: NI7P
        C(0b00000000, 0b01000000, 0, 9), // 131: NI6P
    };
#undef C()

    template <uint64_t decode>
    inline void inner_signals() {
        if(CYC == 1) {
            _DOR = _DB; // latch internal data output bus
        }
        else if(CYC == 2) {
            if(WR) { DATA = _DOR; } // output to external data bus
            _DL = DATA; // latch external data bus
            _ADH = _ADL = _DB = _SB = 255; // precharge internal buses
        }
        if(decode & sig_DL_DB) {_DB &= _DL; }
        if(decode & sig_DL_ADL) { _ADL &= _DL; }
        if(decode & sig_DL_ADH) { _ADH &= _DL; }
        if(decode & sig_0_ADH == sig_0_ADH) { _ADH = 0; }
        if(decode & sig_0_ADH == sig_0_ADH0) { _ADH &= 254; }
        if(decode & sig_0_ADH == sig_0_ADH1_7) { _ADH &= 1; }
        if(decode & sig_ADH_ABH) { ABH = _ADH; }
        if(decode & sig_ADL_ABL) { ABL = _ADL; }
        if(decode & sig_PCL_PCL) { _PCLS = PCL; }
        if(decode & sig_ADL_PCL) { PCL = _ADL; }
        if(decode & sig_I_PC) {
            _PCLC = _PCLS++ == 255? 1: 0;
            _PCHS += _PCLC;
        }
        if(decode & sig_PCL_DB) { _DB &= PCL; }
        if(decode & sig_PCL_ADL) { _ADL &= PCL; }
        if(decode & sig_PCH_PCH) { _PCHS = PCH; }
        if(decode & sig_ADH_PCH) { _PCHS = _ADH; }
        if(decode & sig_PCH_DB)  { _DB &= PCH; }
        if(decode & sig_PCH_ADH) { _ADH &= PCH; }
        if(decode & sig_SB_ADH) { _ADH &= _SB; _SB = _ADH; }
        if(decode & sig_SB_DB) { _SB &= _DB; _DB = _SB; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL2_0) { _ADL &= 0xf8; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL2 | sig_0_ADL1) { _ADL &= 0xf9; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL2 | sig_0_ADL0) { _ADL &= 0xfa; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL2) { _ADL &= 0xfb; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL1 | sig_0_ADL0) { _ADL &= 0xfc; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL1) { _ADL &= 0xfd; }
        if(decode & sig_0_ADL2_0 == sig_0_ADL0) { _ADL &= 0xfe; }
        if(decode & sig_S_ADL) { _ADL &= S; }
        if(decode & sig_SB_S) { S = _SB; }
        //if(decode & sig_S_S) { S = S; } // (recirculate stack pointer)
        if(decode & sig_S_SB) { _SB &= S; }
        if(decode & sig__DB_ADD) { _BI = ~_DB; }
        if(decode & sig_DB_ADD) { _BI = _DB; }
        if(decode & sig_ADL_ADD) { _BI = _ADL; }
        if(decode & sig_I_ADDC) { _ADDC = 1; }
        // DAA & DSA not implemented on 2A03
        if(decode & sig_SUMS) {
            bool carry6 = ((_BI&127)+(_AI&127)+_ADDC)>127;
            _CD = _BI + _AI + _ADDC;
            _HC = (_BI&15 + _AI&15 + _ADDC) > 15? 1 : 0;
            _ACR = _CD > 255 ? 1 : 0;
            _AVR = (!(!(!(_BI|_AI&128) && carry6)|(!(!(_BI&_AI&128) || carry6))))?1:0;
        }
        if(decode & sig_ANDS) { _CD = _BI&_AI; _HC = _ACR = _AVR = 0; }
        if(decode & sig_EORS) { _CD = _BI|_AI; _HC = _ACR = _AVR = 0; }
        if(decode & sig_ORS)  { _CD = _BI^_AI; _HC = _ACR = _AVR = 0; }
        if(decode & sig_SRS) {
            _CD = _BI << 1;
            _HC = _BI & 16;
            _ACR = _BI & 1;
            _AVR = 0;
        }
        if(decode & sig_ADD_ADL) { _ADL &= _ADD; }
        if(decode & sig_ADD_SB == sig_ADD_SB) { _SB &= _ADD; }
        if(decode & sig_ADD_SB == sig_ADD_SB0_6) { _SB &= 128 | _ADD&127; }
        if(decode & sig_ADD_SB == sig_ADD_SB7) { _SB &= 127 | _ADD&128; }
        if(decode & sig_0_ADD) { _ADD = 0; }
        if(decode & sig_SB_ADD) { _ADD = _SB; }
        if(decode & sig_SB_AC) { A = _SB; }
        if(decode & sig_AC_DB) { _DB &= A; }
        if(decode & sig_AC_SB) { _SB &= A; }
        if(decode & sig_SB_X) { X = _SB; }
        if(decode & sig_X_SB) { _SB &= X; }
        if(decode & sig_SB_Y) { Y = _SB; }
        if(decode & sig_Y_SB) { _SB &= Y; }
        if(decode & sig_P_DB) { _DB &= P; }
        if(decode & sig_DB0_C) { P &= 254 | _DB&1; }
        if(decode & sig_IR5_C) { P &= 254 | (_IR&16?1:0); }
        if(decode & sig_ACR_C) { P &= 254 | _ACR; }
        if(decode & sig_DB1_Z) { P &= 253 | _DB&2; }
        if(decode & sig_DBZ_Z) { P &= 253 | (_DB?0:2); }
        if(decode & sig_DB2_I) { P &= 251 | _DB&4; }
        if(decode & sig_IR5_I) { P &= 251 | (_IR&16?4:0); }
        if(decode & sig_DB3_D) { P &= 247 | _DB&8; }
        if(decode & sig_IR5_D) { P &= 247 | (_IR&16?8:0); }
        if(decode & sig_DB6_V) { P &= 191 | _DB&64; }
        if(decode & sig_AVR_V) { P &= 191 | _AVR*64; }
        if(decode & sig_1_V)   { P |= 64; }
        if(decode & sig_0_V)   { P &= 191; }
        if(decode & sig_DB7_N) { P &= 127 | _DB&128; }
    }



};

class PPU {
public:
    static constexpr uint32_t paletteNTSC[64] = {
        0x7c7c7c, 0x0000fc, 0x0000bc, 0x4428bc,
        0x940084, 0xa80020, 0xa81000, 0x881400,
        0x503000, 0x007800, 0x006800, 0x005800,
        0x004058, 0x000000, 0x000000, 0x000000,
        0xbcbcbc, 0x0078f8, 0x0058f8, 0x6844fc,
        0xd800fc, 0xe40058, 0xf83800, 0xe45c10,
        0xac7c00, 0x00b800, 0x00a800, 0x00a844,
        0x008888, 0x000000, 0x000000, 0x000000,
        0xf8f8f8, 0x3cbcfc, 0x6888fc, 0x9878f8,
        0xf878f8, 0xf85898, 0xf87858, 0xfca044,
        0xf8b800, 0xb8f818, 0x58d854, 0x58f898,
        0x00e8d8, 0x787878, 0x000000, 0x000000,
        0xfcfcfc, 0xa4e4fc, 0xb8b8f8, 0xd8b8f8,
        0xf8b8f8, 0xf8a4c0, 0xf0d0b0, 0xfce0a8,
        0xf8d878, 0xd8f878, 0xb8f8b8, 0xb8f8d8,
        0x00fcfc, 0xf8d8f8, 0x000000, 0x000000
    };

    uint32_t *palette;
    uint8_t PPUCTRL, PPUMASK, OAMADDR;
    uint8_t bgscroll_x, bgscroll_y, line_counter, line_sprite_counter;
    bool sprite0, spritelimit;
    uint8_t bgscroll_latch, address_latch;
    uint16_t ppuaddress, oamaddress;
    uint8_t OAM[256];

    PPU(): palette(paletteNTSC),
        PPUCTRL(0), PPUMASK(0), OAMADDR(0),
        bgscroll_x(0), bgscroll_y(0),
        line_counter(0), line_sprite_counter(0) {
    }
};

class NES {
public:
    CPU_2A03 cpu;
    PPU ppu;

    NES();
};

#endif // NES_H
