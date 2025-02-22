#ifndef MACHINE_CODE_MACHINE_INSTRUCTION_HPP
#define MACHINE_CODE_MACHINE_INSTRUCTION_HPP

#include <string>
#include <vector>

namespace machine_code {
class MachineInstruction {
 public:
  enum Type {
    /**/ UNDEF,
    /*0*/ MOV_A_B,
    /*1*/ MOV_A_TH,
    /*2*/ MOV_A_TL,
    /*3*/ MOV_A_F,
    /*4*/ MOV_A_INT,
    /*5*/ MOV_B_A,
    /*6*/ MOV_B_TH,
    /*7*/ MOV_B_TL,
    /*8*/ MOV_B_F,
    /*9*/ MOV_B_INT,
    /*10*/ MOV_TH_A,
    /*11*/ MOV_TH_B,
    /*12*/ MOV_TH_TL,
    /*13*/ MOV_TH_F,
    /*14*/ MOV_TH_INT,
    /*15*/ MOV_TL_A,
    /*16*/ MOV_TL_B,
    /*17*/ MOV_TL_TH,
    /*18*/ MOV_TL_F,
    /*19*/ MOV_TL_INT,
    /*20*/ MOV_A_IMM,
    /*21*/ MOV_B_IMM,
    /*22*/ MOV_TH_IMM,
    /*23*/ MOV_TL_IMM,
    /*24*/ MOV_A_ABS,
    /*25*/ MOV_A_ABS_ZP,
    /*26*/ MOV_B_ABS,
    /*27*/ MOV_B_ABS_ZP,
    /*28*/ MOV_A_AT_T,
    /*29*/ MOV_B_AT_T,
    /*30*/ MOV_A_AT_B,
    /*31*/ MOV_A_AT_TH,
    /*32*/ MOV_A_AT_TL,
    /*33*/ MOV_B_AT_A,
    /*34*/ MOV_B_AT_TH,
    /*35*/ MOV_B_AT_TL,
    /*36*/ MOV_TH_AT_A,
    /*37*/ MOV_TH_AT_B,
    /*38*/ MOV_TH_AT_TL,
    /*39*/ MOV_TL_AT_A,
    /*40*/ MOV_TL_AT_B,
    /*41*/ MOV_TL_AT_TH,
    /*42*/ MOV_AT_ABS_A,
    /*43*/ MOV_AT_ABS_A_ZP,
    /*44*/ MOV_AT_ABS_B,
    /*45*/ MOV_AT_ABS_B_ZP,
    /*46*/ MOV_AT_ABS_INT,
    /*47*/ MOV_AT_ABS_INT_ZP,
    /*48*/ MOV_AT_ABS_IMM,
    /*49*/ MOV_AT_ABS_IMM_ZP,
    /*50*/ MOV_AT_T_A,
    /*51*/ MOV_AT_T_B,
    /*52*/ MOV_AT_T_INT,
    /*53*/ MOV_AT_A_B,
    /*54*/ MOV_AT_A_TH,
    /*55*/ MOV_AT_A_TL,
    /*56*/ MOV_AT_B_A,
    /*57*/ MOV_AT_B_TH,
    /*58*/ MOV_AT_B_TL,
    /*59*/ MOV_AT_TH_A,
    /*60*/ MOV_AT_TH_B,
    /*61*/ MOV_AT_TH_TL,
    /*62*/ MOV_AT_TL_A,
    /*63*/ MOV_AT_TL_B,
    /*64*/ MOV_AT_TL_TH,
    /*65*/ MOV_AT_T_IMM,
    /*66*/ MOV_AT_A_IMM,
    /*67*/ MOV_AT_B_IMM,
    /*68*/ MOV_AT_TH_IMM,
    /*69*/ MOV_AT_TL_IMM,
    /*70*/ NEG_A_A,
    /*71*/ NEG_A_B,
    /*72*/ NEG_B_A,
    /*73*/ NEG_B_B,
    /*74*/ NEG_MEM_A,
    /*75*/ NEG_MEM_B,
    /*76*/ NEG_MEM_ZP_A,
    /*77*/ NEG_MEM_ZP_B,
    /*78*/ NEG_STC_A,
    /*79*/ NEG_STC_B,
    /*80*/ ADD_A,
    /*81*/ ADD_B,
    /*82*/ ADD_MEM,
    /*83*/ ADD_MEM_ZP,
    /*84*/ ADD_STC,
    /*85*/ SUB_A_AB,
    /*86*/ SUB_A_BA,
    /*87*/ SUB_B_AB,
    /*88*/ SUB_B_BA,
    /*89*/ SUB_MEM_AB,
    /*90*/ SUB_MEM_BA,
    /*91*/ SUB_MEM_ZP_AB,
    /*92*/ SUB_MEM_ZP_BA,
    /*93*/ SUB_STC_AB,
    /*94*/ SUB_STC_BA,
    /*95*/ DIV2_A_A,
    /*96*/ DIV2_A_B,
    /*97*/ DIV2_B_A,
    /*98*/ DIV2_B_B,
    /*99*/ DIV2_MEM_A,
    /*100*/ DIV2_MEM_B,
    /*101*/ DIV2_MEM_ZP_A,
    /*102*/ DIV2_MEM_ZP_B,
    /*103*/ DIV2_STC_A,
    /*104*/ DIV2_STC_B,
    /*105*/ INV_A_A,
    /*106*/ INV_A_B,
    /*107*/ INV_B_A,
    /*108*/ INV_B_B,
    /*109*/ INV_MEM_A,
    /*110*/ INV_MEM_B,
    /*111*/ INV_MEM_ZP_A,
    /*112*/ INV_MEM_ZP_B,
    /*113*/ INV_STC_A,
    /*114*/ INV_STC_B,
    /*115*/ OR_A,
    /*116*/ OR_B,
    /*117*/ OR_MEM,
    /*118*/ OR_MEM_ZP,
    /*119*/ OR_STC,
    /*120*/ AND_A,
    /*121*/ AND_B,
    /*122*/ AND_MEM,
    /*123*/ AND_MEM_ZP,
    /*124*/ AND_STC,
    /*125*/ XOR_A,
    /*126*/ XOR_B,
    /*127*/ XOR_MEM,
    /*128*/ XOR_MEM_ZP,
    /*129*/ XOR_STC,
    /*130*/ SHR_A_A,
    /*131*/ SHR_A_B,
    /*132*/ SHR_B_A,
    /*133*/ SHR_B_B,
    /*134*/ SHR_MEM_A,
    /*135*/ SHR_MEM_B,
    /*136*/ SHR_MEM_ZP_A,
    /*137*/ SHR_MEM_ZP_B,
    /*138*/ SHR_STC_A,
    /*139*/ SHR_STC_B,
    /*140*/ SHL_A_A,
    /*141*/ SHL_A_B,
    /*142*/ SHL_B_A,
    /*143*/ SHL_B_B,
    /*144*/ SHL_MEM_A,
    /*145*/ SHL_MEM_B,
    /*146*/ SHL_MEM_ZP_A,
    /*147*/ SHL_MEM_ZP_B,
    /*148*/ SHL_STC_A,
    /*149*/ SHL_STC_B,
    /*150*/ CMP_A_B,
    /*151*/ CMP_B_A,
    /*152*/ CMP_TH_TL,
    /*153*/ CMP_TL_TH,
    /*154*/ CMP_TH_A,
    /*155*/ CMP_A_TH,
    /*156*/ CMP_TH_B,
    /*157*/ CMP_B_TH,
    /*158*/ CMP_TL_A,
    /*159*/ CMP_A_TL,
    /*160*/ CMP_TL_B,
    /*161*/ CMP_B_TL,
    /*162*/ CMP_INT_A,
    /*163*/ CMP_A_INT,
    /*164*/ CMP_INT_B,
    /*165*/ CMP_B_INT,
    /*166*/ CLR_A,
    /*167*/ CLR_B,
    /*168*/ CLR_TH,
    /*169*/ CLR_TL,
    /*170*/ CLR_T,
    /*171*/ INC_A,
    /*172*/ INC_B,
    /*173*/ INC_T,
    /*174*/ DEC_A,
    /*175*/ DEC_B,
    /*176*/ DEC_T,
    /*177*/ JMP_IMM,
    /*178*/ JMP_IMM_S,
    /*179*/ JMP_IMM_NS,
    /*180*/ JMP_IMM_T_S,
    /*181*/ JMP_IMM_T_NS,
    /*182*/ JMP_IMM_P,
    /*183*/ JMP_IMM_NP,
    /*184*/ JMP_IMM_T_P,
    /*185*/ JMP_IMM_T_NP,
    /*186*/ JMP_IMM_Z,
    /*187*/ JMP_IMM_NZ,
    /*188*/ JMP_IMM_T_Z,
    /*189*/ JMP_IMM_T_NZ,
    /*190*/ JMP_IMM_C,
    /*191*/ JMP_IMM_NC,
    /*192*/ JMP_IMM_T_C,
    /*193*/ JMP_IMM_T_NC,
    /*194*/ JMP_IMM_O,
    /*195*/ JMP_IMM_NO,
    /*196*/ JMP_IMM_T_O,
    /*197*/ JMP_IMM_T_NO,
    /*198*/ JMP_REL,
    /*199*/ JMP_REL_S,
    /*200*/ JMP_REL_NS,
    /*201*/ JMP_REL_TL_S,
    /*202*/ JMP_REL_TL_NS,
    /*203*/ JMP_REL_P,
    /*204*/ JMP_REL_NP,
    /*205*/ JMP_REL_TL_P,
    /*206*/ JMP_REL_TL_NP,
    /*207*/ JMP_REL_Z,
    /*208*/ JMP_REL_NZ,
    /*209*/ JMP_REL_TL_Z,
    /*210*/ JMP_REL_TL_NZ,
    /*211*/ JMP_REL_C,
    /*212*/ JMP_REL_NC,
    /*213*/ JMP_REL_TL_C,
    /*214*/ JMP_REL_TL_NC,
    /*215*/ JMP_REL_O,
    /*216*/ JMP_REL_NO,
    /*217*/ JMP_REL_TL_O,
    /*218*/ JMP_REL_TL_NO,
    /*219*/ JMP_FUN,
    /*220*/ JMP_RET,
    /*221*/ PUSH_A,
    /*222*/ PUSH_B,
    /*223*/ PUSH_TH,
    /*224*/ PUSH_TL,
    /*225*/ PUSH_F,
    /*226*/ PUSH_INT,
    /*227*/ PUSH_T,
    /*228*/ PUSH_IMM,
    /*229*/ PUSH_ABS,
    /*230*/ PUSH_ABS_ZP,
    /*231*/ POP_A,
    /*232*/ POP_B,
    /*233*/ POP_TH,
    /*234*/ POP_TL,
    /*235*/ POP_T,
    /*236*/ POP_MEM,
    /*237*/ POP_MEM_ZP,
    /*238*/ NOP,
    /*239*/ SKIP,
    /*240*/ SKIP_1,
    /*241*/ SKIP_2,
    /*242*/ ISR,
    /*243*/ IRET,
    /*244*/ INT0,
    /*245*/ INT1,
    /*246*/ INT2,
    /*247*/ INT3,
    /*248*/ INT4,
    /*249*/ HALT,
    /*250*/ LABEL  // this is not a hardware instruction, but a label for the assembler
  };

  MachineInstruction() = default;
  MachineInstruction(Type type) : type_(type), operands_{} {}
  MachineInstruction(Type type, std::vector<std::string> operands) : type_(type), operands_(std::move(operands)) {}

  MachineInstruction(const MachineInstruction&) = default;
  MachineInstruction(MachineInstruction&&) = default;

  MachineInstruction& operator=(const MachineInstruction&) = default;
  MachineInstruction& operator=(MachineInstruction&&) = default;

  ~MachineInstruction() = default;

  [[nodiscard]] Type getType() const { return type_; }
  [[nodiscard]] const std::vector<std::string>& getOperands() const { return operands_; }

  [[nodiscard]] std::string getBinaryCode() const { return typeToAssembly_[type_]; }

  [[nodiscard]] std::string toString() const {
    std::string operands;
    for (const auto& operand : operands_) {
      operands += " " + operand;
    }
    return typeToString_[type_] + operands;
  }

  [[nodiscard]] std::string toAssembly() const {
    std::string operands;
    for (const auto& operand : operands_) {
      operands += " " + operand;
    }
    return typeToAssembly_[type_] + operands;
  }

  void replaceOperand(const std::string& oldOperand, const std::vector<std::string>& newOperands) {
    const std::vector<std::string> operandsCopy = operands_;
    operands_.clear();
    for (const auto& operand : operandsCopy) {
      if (operand == oldOperand) {
        operands_.insert(operands_.end(), newOperands.begin(), newOperands.end());
      }
      else {
        operands_.push_back(operand);
      }
    }
  }

 private:
  static constexpr std::size_t typesCount_ = 252;
  static std::string typeToString_[typesCount_];
  static std::string typeToAssembly_[typesCount_];

  Type type_;
  std::vector<std::string> operands_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_MACHINE_INSTRUCTION_HPP