#include "machine_instruction.hpp"

namespace machine_code {
std::string MachineInstruction::typeToString_[typesCount_] = {
    /**/ "undefined instruction",
    /*0*/ "mov B to A",
    /*1*/ "mov TH to A",
    /*2*/ "mov TL to A",
    /*3*/ "mov F to A",
    /*4*/ "mov INT to A",
    /*5*/ "mov A to B",
    /*6*/ "mov TH to B",
    /*7*/ "mov TL to B",
    /*8*/ "mov F to B",
    /*9*/ "mov INT to B",
    /*10*/ "mov A to TH",
    /*11*/ "mov B to TH",
    /*12*/ "mov TL to TH",
    /*13*/ "mov F to TH",
    /*14*/ "mov INT to TH",
    /*15*/ "mov A to TL",
    /*16*/ "mov B to TL",
    /*17*/ "mov TH to TL",
    /*18*/ "mov F to TL",
    /*19*/ "mov INT to TL",
    /*20*/ "mov immediate to A",
    /*21*/ "mov immediate to B",
    /*22*/ "mov immediate to TH",
    /*23*/ "mov immediate to TL",
    /*24*/ "mov absolute to A",
    /*25*/ "mov absolute zero page to A",
    /*26*/ "mov absolute to B",
    /*27*/ "mov absolute zero page to B",
    /*28*/ "mov A to absolute memory",
    /*29*/ "mov A to absolute zero page memory",
    /*30*/ "mov B to absolute memory",
    /*31*/ "mov B to absolute zero page memory",
    /*32*/ "mov INT to absolute memory",
    /*33*/ "mov INT to absolute zero page memory",
    /*34*/ "mov immediate to absolute memory",
    /*35*/ "mov immediate to absolute zero page memory",
    /*36*/ "mov A to memory pointed by T",
    /*37*/ "mov B to memory pointed by T",
    /*38*/ "mov INT to memory pointed by T",
    /*39*/ "mov B to zero page memory pointed by A",
    /*40*/ "mov TH to zero page memory pointed by A",
    /*41*/ "mov TL to zero page memory pointed by A",
    /*42*/ "mov A to zero page memory pointed by B",
    /*43*/ "mov TH to zero page memory pointed by B",
    /*44*/ "mov TL to zero page memory pointed by B",
    /*45*/ "mov A to zero page memory pointed by TH",
    /*46*/ "mov B to zero page memory pointed by TH",
    /*47*/ "mov TL to zero page memory pointed by TH",
    /*48*/ "mov A to zero page memory pointed by TL",
    /*49*/ "mov B to zero page memory pointed by TL",
    /*50*/ "mov TH to zero page memory pointed by TL",
    /*51*/ "mov immediate to memory pointed by T",
    /*52*/ "mov immediate to zero page memory pointed by A",
    /*53*/ "mov immediate to zero page memory pointed by B",
    /*54*/ "mov immediate to zero page memory pointed by TH",
    /*55*/ "mov immediate to zero page memory pointed by TL",
    /*56*/ "mov -A to A",
    /*57*/ "mov -B to A",
    /*58*/ "mov -A to B",
    /*59*/ "mov -B to B",
    /*60*/ "mov -A to absolute memory",
    /*61*/ "mov -B to absolute memory",
    /*62*/ "mov -A to absolute zero page memory",
    /*63*/ "mov -B to absolute zero page memory",
    /*64*/ "mov -A to stack",
    /*65*/ "mov -B to stack",
    /*66*/ "mov A+B to A",
    /*67*/ "mov A+B to B",
    /*68*/ "mov A+B to absolute memory",
    /*69*/ "mov A+B to absolute zero page memory",
    /*70*/ "mov A+B to stack",
    /*71*/ "mov A-B to A",
    /*72*/ "mov B-A to A",
    /*73*/ "mov A-B to B",
    /*74*/ "mov B-A to B",
    /*75*/ "mov A-B to absolute memory",
    /*76*/ "mov B-A to absolute memory",
    /*77*/ "mov A-B to absolute zero page memory",
    /*78*/ "mov B-A to absolute zero page memory",
    /*79*/ "mov A-B to stack",
    /*80*/ "mov B-A to stack",
    /*81*/ "mov A/2 to A",
    /*82*/ "mov B/2 to A",
    /*83*/ "mov A/2 to B",
    /*84*/ "mov B/2 to B",
    /*85*/ "mov A/2 to absolute memory",
    /*86*/ "mov B/2 to absolute memory",
    /*87*/ "mov A/2 to absolute zero page memory",
    /*88*/ "mov B/2 to absolute zero page memory",
    /*89*/ "mov A/2 to stack",
    /*90*/ "mov B/2 to stack",
    /*91*/ "mov ~A to A",
    /*92*/ "mov ~B to A",
    /*93*/ "mov ~A to B",
    /*94*/ "mov ~B to B",
    /*95*/ "mov ~A to absolute memory",
    /*96*/ "mov ~B to absolute memory",
    /*97*/ "mov ~A to absolute zero page memory",
    /*98*/ "mov ~B to absolute zero page memory",
    /*99*/ "mov ~A to stack",
    /*100*/ "mov ~B to stack",
    /*101*/ "mov A|B to A",
    /*102*/ "mov A|B to B",
    /*103*/ "mov A|B to absolute memory",
    /*104*/ "mov A|B to absolute zero page memory",
    /*105*/ "mov A|B to stack",
    /*106*/ "mov A&B to A",
    /*107*/ "mov A&B to B",
    /*108*/ "mov A&B to absolute memory",
    /*109*/ "mov A&B to absolute zero page memory",
    /*110*/ "mov A&B to stack",
    /*111*/ "mov A^B to A",
    /*112*/ "mov A^B to B",
    /*113*/ "mov A^B to absolute memory",
    /*114*/ "mov A^B to absolute zero page memory",
    /*115*/ "mov A^B to stack",
    /*116*/ "mov A>>1 to A",
    /*117*/ "mov B>>1 to A",
    /*118*/ "mov A>>1 to B",
    /*119*/ "mov B>>1 to B",
    /*120*/ "mov A>>1 to absolute memory",
    /*121*/ "mov B>>1 to absolute memory",
    /*122*/ "mov A>>1 to absolute zero page memory",
    /*123*/ "mov B>>1 to absolute zero page memory",
    /*124*/ "mov A>>1 to stack",
    /*125*/ "mov B>>1 to stack",
    /*126*/ "mov A<<1 to A",
    /*127*/ "mov B<<1 to A",
    /*128*/ "mov A<<1 to B",
    /*129*/ "mov B<<1 to B",
    /*130*/ "mov A<<1 to absolute memory",
    /*131*/ "mov B<<1 to absolute memory",
    /*132*/ "mov A<<1 to absolute zero page memory",
    /*133*/ "mov B<<1 to absolute zero page memory",
    /*134*/ "mov A<<1 to stack",
    /*135*/ "mov B<<1 to stack",
    /*136*/ "save flags of A-B",
    /*137*/ "save flags of B-A",
    /*138*/ "save flags of TH-TL",
    /*139*/ "save flags of TL-TH",
    /*140*/ "save flags of TH-A",
    /*141*/ "save flags of A-TH",
    /*142*/ "save flags of TH-B",
    /*143*/ "save flags of B-TH",
    /*144*/ "save flags of TL-A",
    /*145*/ "save flags of A-TL",
    /*146*/ "save flags of TL-B",
    /*147*/ "save flags of B-TL",
    /*148*/ "save flags of INT-A",
    /*149*/ "save flags of A-INT",
    /*150*/ "save flags of INT-B",
    /*151*/ "save flags of B-INT",
    /*152*/ "mov 0 to A",
    /*153*/ "mov 0 to B",
    /*154*/ "mov 0 to TH",
    /*155*/ "mov 0 to TL",
    /*156*/ "mov 0 to T",
    /*157*/ "mov A+1 to A",
    /*158*/ "mov B+1 to B",
    /*159*/ "mov T+1 to T",
    /*160*/ "mov A-1 to A",
    /*161*/ "mov B-1 to B",
    /*162*/ "mov T-1 to T",
    /*163*/ "jump to immediate",
    /*164*/ "jump to immediate if sign flag set",
    /*165*/ "jump to immediate if sign flag not set",
    /*166*/ "jump to immediate pointed by T if sign flag set",
    /*167*/ "jump to immediate pointed by T if sign flag not set",
    /*168*/ "jump to immediate if parity flag set",
    /*169*/ "jump to immediate if parity flag not set",
    /*170*/ "jump to immediate pointed by T if parity flag set",
    /*171*/ "jump to immediate pointed by T if parity flag not set",
    /*172*/ "jump to immediate if zero flag set",
    /*173*/ "jump to immediate if zero flag not set",
    /*174*/ "jump to immediate pointed by T if zero flag set",
    /*175*/ "jump to immediate pointed by T if zero flag not set",
    /*176*/ "jump to immediate if carry flag set",
    /*177*/ "jump to immediate if carry flag not set",
    /*178*/ "jump to immediate pointed by T if carry flag set",
    /*179*/ "jump to immediate pointed by T if carry flag not set",
    /*180*/ "jump to immediate if overflow flag set",
    /*181*/ "jump to immediate if overflow flag not set",
    /*182*/ "jump to immediate pointed by T if overflow flag set",
    /*183*/ "jump to immediate pointed by T if overflow flag not set",
    /*184*/ "jump relative",
    /*185*/ "jump relative if sign flag set",
    /*186*/ "jump relative if sign flag not set",
    /*187*/ "jump relative from TL if sign flag set",
    /*188*/ "jump relative from TL if sign flag not set",
    /*189*/ "jump relative if parity flag set",
    /*190*/ "jump relative if parity flag not set",
    /*191*/ "jump relative from TL if parity flag set",
    /*192*/ "jump relative from TL if parity flag not set",
    /*193*/ "jump relative if zero flag set",
    /*194*/ "jump relative if zero flag not set",
    /*195*/ "jump relative from TL if zero flag set",
    /*196*/ "jump relative from TL if zero flag not set",
    /*197*/ "jump relative if carry flag set",
    /*198*/ "jump relative if carry flag not set",
    /*199*/ "jump relative from TL if carry flag set",
    /*200*/ "jump relative from TL if carry flag not set",
    /*201*/ "jump relative if overflow flag set",
    /*202*/ "jump relative if overflow flag not set",
    /*203*/ "jump relative from TL if overflow flag set",
    /*204*/ "jump relative from TL if overflow flag not set",
    /*205*/ "push PC to stack and jump to immediate",
    /*206*/ "pop PC from stack and jump to it",
    /*207*/ "push A to stack",
    /*208*/ "push B to stack",
    /*209*/ "push TH to stack",
    /*210*/ "push TL to stack",
    /*211*/ "push F to stack",
    /*212*/ "push INT to stack",
    /*213*/ "push T to stack",
    /*214*/ "push immediate to stack",
    /*215*/ "push absolute to stack",
    /*216*/ "push absolute zero page to stack",
    /*217*/ "pop to A from stack",
    /*218*/ "pop to B from stack",
    /*219*/ "pop to TH from stack",
    /*220*/ "pop to TL from stack",
    /*221*/ "pop to T from stack",
    /*222*/ "pop to memory from stack",
    /*223*/ "pop to zero page memory from stack",
    /*224*/ "do nothing",
    /*225*/ "skip",
    /*226*/ "skip next 1 instruction",
    /*227*/ "skip next 2 instructions",
    /*228*/ "enter interrupt service routine",
    /*229*/ "return from interrupt service routine",
    /*230*/ "trigger interrupt 0",
    /*231*/ "halt",
    /*232*/ "label"};

std::string MachineInstruction::typeToAssembly_[typesCount_] = {/**/ "Undefined Instruction",
                                                                /*0*/ "0b00000001",
                                                                /*1*/ "0b00000010",
                                                                /*2*/ "0b00000011",
                                                                /*3*/ "0b00000100",
                                                                /*4*/ "0b00000101",
                                                                /*5*/ "0b00000110",
                                                                /*6*/ "0b00000111",
                                                                /*7*/ "0b00001000",
                                                                /*8*/ "0b00001001",
                                                                /*9*/ "0b00001010",
                                                                /*10*/ "0b00001011",
                                                                /*11*/ "0b00001100",
                                                                /*12*/ "0b00001101",
                                                                /*13*/ "0b00001110",
                                                                /*14*/ "0b00001111",
                                                                /*15*/ "0b00010000",
                                                                /*16*/ "0b00010001",
                                                                /*17*/ "0b00010010",
                                                                /*18*/ "0b00010011",
                                                                /*19*/ "0b00010100",
                                                                /*20*/ "0b00010101",
                                                                /*21*/ "0b00010110",
                                                                /*22*/ "0b00010111",
                                                                /*23*/ "0b00011000",
                                                                /*24*/ "0b00011001",
                                                                /*25*/ "0b00011010",
                                                                /*26*/ "0b00011011",
                                                                /*27*/ "0b00011100",
                                                                /*28*/ "0b00011101",
                                                                /*29*/ "0b00011110",
                                                                /*30*/ "0b00011111",
                                                                /*31*/ "0b00100000",
                                                                /*32*/ "0b00100001",
                                                                /*33*/ "0b00100010",
                                                                /*34*/ "0b00100011",
                                                                /*35*/ "0b00100100",
                                                                /*36*/ "0b00100101",
                                                                /*37*/ "0b00100110",
                                                                /*38*/ "0b00100111",
                                                                /*39*/ "0b00101000",
                                                                /*40*/ "0b00101001",
                                                                /*41*/ "0b00101010",
                                                                /*42*/ "0b00101011",
                                                                /*43*/ "0b00101100",
                                                                /*44*/ "0b00101101",
                                                                /*45*/ "0b00101110",
                                                                /*46*/ "0b00101111",
                                                                /*47*/ "0b00110000",
                                                                /*48*/ "0b00110001",
                                                                /*49*/ "0b00110010",
                                                                /*50*/ "0b00110011",
                                                                /*51*/ "0b00110100",
                                                                /*52*/ "0b00110101",
                                                                /*53*/ "0b00110110",
                                                                /*54*/ "0b00110111",
                                                                /*55*/ "0b00111000",
                                                                /*56*/ "0b00111001",
                                                                /*57*/ "0b00111010",
                                                                /*58*/ "0b00111011",
                                                                /*59*/ "0b00111100",
                                                                /*60*/ "0b00111101",
                                                                /*61*/ "0b00111110",
                                                                /*62*/ "0b00111111",
                                                                /*63*/ "0b01000000",
                                                                /*64*/ "0b01000001",
                                                                /*65*/ "0b01000010",
                                                                /*66*/ "0b01000011",
                                                                /*67*/ "0b01000100",
                                                                /*68*/ "0b01000101",
                                                                /*69*/ "0b01000110",
                                                                /*70*/ "0b01000111",
                                                                /*71*/ "0b01001000",
                                                                /*72*/ "0b01001001",
                                                                /*73*/ "0b01001010",
                                                                /*74*/ "0b01001011",
                                                                /*75*/ "0b01001100",
                                                                /*76*/ "0b01001101",
                                                                /*77*/ "0b01001110",
                                                                /*78*/ "0b01001111",
                                                                /*79*/ "0b01010000",
                                                                /*80*/ "0b01010001",
                                                                /*81*/ "0b01010010",
                                                                /*82*/ "0b01010011",
                                                                /*83*/ "0b01010100",
                                                                /*84*/ "0b01010101",
                                                                /*85*/ "0b01010110",
                                                                /*86*/ "0b01010111",
                                                                /*87*/ "0b01011000",
                                                                /*88*/ "0b01011001",
                                                                /*89*/ "0b01011010",
                                                                /*90*/ "0b01011011",
                                                                /*91*/ "0b01011100",
                                                                /*92*/ "0b01011101",
                                                                /*93*/ "0b01011110",
                                                                /*94*/ "0b01011111",
                                                                /*95*/ "0b01100000",
                                                                /*96*/ "0b01100001",
                                                                /*97*/ "0b01100010",
                                                                /*98*/ "0b01100011",
                                                                /*99*/ "0b01100100",
                                                                /*100*/ "0b01100101",
                                                                /*101*/ "0b01100110",
                                                                /*102*/ "0b01100111",
                                                                /*103*/ "0b01101000",
                                                                /*104*/ "0b01101001",
                                                                /*105*/ "0b01101010",
                                                                /*106*/ "0b01101011",
                                                                /*107*/ "0b01101100",
                                                                /*108*/ "0b01101101",
                                                                /*109*/ "0b01101110",
                                                                /*110*/ "0b01101111",
                                                                /*111*/ "0b01110000",
                                                                /*112*/ "0b01110001",
                                                                /*113*/ "0b01110010",
                                                                /*114*/ "0b01110011",
                                                                /*115*/ "0b01110100",
                                                                /*116*/ "0b01110101",
                                                                /*117*/ "0b01110110",
                                                                /*118*/ "0b01110111",
                                                                /*119*/ "0b01111000",
                                                                /*120*/ "0b01111001",
                                                                /*121*/ "0b01111010",
                                                                /*122*/ "0b01111011",
                                                                /*123*/ "0b01111100",
                                                                /*124*/ "0b01111101",
                                                                /*125*/ "0b01111110",
                                                                /*126*/ "0b01111111",
                                                                /*127*/ "0b10000000",
                                                                /*128*/ "0b10000001",
                                                                /*129*/ "0b10000010",
                                                                /*130*/ "0b10000011",
                                                                /*131*/ "0b10000100",
                                                                /*132*/ "0b10000101",
                                                                /*133*/ "0b10000110",
                                                                /*134*/ "0b10000111",
                                                                /*135*/ "0b10001000",
                                                                /*136*/ "0b10001001",
                                                                /*137*/ "0b10001010",
                                                                /*138*/ "0b10001011",
                                                                /*139*/ "0b10001100",
                                                                /*140*/ "0b10001101",
                                                                /*141*/ "0b10001110",
                                                                /*142*/ "0b10001111",
                                                                /*143*/ "0b10010000",
                                                                /*144*/ "0b10010001",
                                                                /*145*/ "0b10010010",
                                                                /*146*/ "0b10010011",
                                                                /*147*/ "0b10010100",
                                                                /*148*/ "0b10010101",
                                                                /*149*/ "0b10010110",
                                                                /*150*/ "0b10010111",
                                                                /*151*/ "0b10011000",
                                                                /*152*/ "0b10011001",
                                                                /*153*/ "0b10011010",
                                                                /*154*/ "0b10011011",
                                                                /*155*/ "0b10011100",
                                                                /*156*/ "0b10011101",
                                                                /*157*/ "0b10011110",
                                                                /*158*/ "0b10011111",
                                                                /*159*/ "0b10100000",
                                                                /*160*/ "0b10100001",
                                                                /*161*/ "0b10100010",
                                                                /*162*/ "0b10100011",
                                                                /*163*/ "0b10100100",
                                                                /*164*/ "0b10100101",
                                                                /*165*/ "0b10100110",
                                                                /*166*/ "0b10100111",
                                                                /*167*/ "0b10101000",
                                                                /*168*/ "0b10101001",
                                                                /*169*/ "0b10101010",
                                                                /*170*/ "0b10101011",
                                                                /*171*/ "0b10101100",
                                                                /*172*/ "0b10101101",
                                                                /*173*/ "0b10101110",
                                                                /*174*/ "0b10101111",
                                                                /*175*/ "0b10110000",
                                                                /*176*/ "0b10110001",
                                                                /*177*/ "0b10110010",
                                                                /*178*/ "0b10110011",
                                                                /*179*/ "0b10110100",
                                                                /*180*/ "0b10110101",
                                                                /*181*/ "0b10110110",
                                                                /*182*/ "0b10110111",
                                                                /*183*/ "0b10111000",
                                                                /*184*/ "0b10111001",
                                                                /*185*/ "0b10111010",
                                                                /*186*/ "0b10111011",
                                                                /*187*/ "0b10111100",
                                                                /*188*/ "0b10111101",
                                                                /*189*/ "0b10111110",
                                                                /*190*/ "0b10111111",
                                                                /*191*/ "0b11000000",
                                                                /*192*/ "0b11000001",
                                                                /*193*/ "0b11000010",
                                                                /*194*/ "0b11000011",
                                                                /*195*/ "0b11000100",
                                                                /*196*/ "0b11000101",
                                                                /*197*/ "0b11000110",
                                                                /*198*/ "0b11000111",
                                                                /*199*/ "0b11001000",
                                                                /*200*/ "0b11001001",
                                                                /*201*/ "0b11001010",
                                                                /*202*/ "0b11001011",
                                                                /*203*/ "0b11001100",
                                                                /*204*/ "0b11001101",
                                                                /*205*/ "0b11001110",
                                                                /*206*/ "0b11001111",
                                                                /*207*/ "0b11010000",
                                                                /*208*/ "0b11010001",
                                                                /*209*/ "0b11010010",
                                                                /*210*/ "0b11010011",
                                                                /*211*/ "0b11010100",
                                                                /*212*/ "0b11010101",
                                                                /*213*/ "0b11010110",
                                                                /*214*/ "0b11010111",
                                                                /*215*/ "0b11011000",
                                                                /*216*/ "0b11011001",
                                                                /*217*/ "0b11011010",
                                                                /*218*/ "0b11011011",
                                                                /*219*/ "0b11011100",
                                                                /*220*/ "0b11011101",
                                                                /*221*/ "0b11011110",
                                                                /*222*/ "0b11011111",
                                                                /*223*/ "0b11100000",
                                                                /*224*/ "0b11100001",
                                                                /*225*/ "0b11100010",
                                                                /*226*/ "0b11100011",
                                                                /*227*/ "0b11100100",
                                                                /*228*/ "0b11100101",
                                                                /*229*/ "0b11100110",
                                                                /*230*/ "0b11100111",
                                                                /*231*/ "0b11101100",
                                                                /*232*/ ""};
}  // namespace machine_code