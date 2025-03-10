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
    /*28*/ MOV_AT_ABS_A,
    /*29*/ MOV_AT_ABS_A_ZP,
    /*30*/ MOV_AT_ABS_B,
    /*31*/ MOV_AT_ABS_B_ZP,
    /*32*/ MOV_AT_ABS_INT,
    /*33*/ MOV_AT_ABS_INT_ZP,
    /*34*/ MOV_AT_ABS_IMM,
    /*35*/ MOV_AT_ABS_IMM_ZP,
    /*36*/ MOV_AT_T_A,
    /*37*/ MOV_AT_T_B,
    /*38*/ MOV_AT_T_INT,
    /*39*/ MOV_AT_A_B,
    /*40*/ MOV_AT_A_TH,
    /*41*/ MOV_AT_A_TL,
    /*42*/ MOV_AT_B_A,
    /*43*/ MOV_AT_B_TH,
    /*44*/ MOV_AT_B_TL,
    /*45*/ MOV_AT_TH_A,
    /*46*/ MOV_AT_TH_B,
    /*47*/ MOV_AT_TH_TL,
    /*48*/ MOV_AT_TL_A,
    /*49*/ MOV_AT_TL_B,
    /*50*/ MOV_AT_TL_TH,
    /*51*/ MOV_AT_T_IMM,
    /*52*/ MOV_AT_A_IMM,
    /*53*/ MOV_AT_B_IMM,
    /*54*/ MOV_AT_TH_IMM,
    /*55*/ MOV_AT_TL_IMM,
    /*56*/ NEG_A_A,
    /*57*/ NEG_A_B,
    /*58*/ NEG_B_A,
    /*59*/ NEG_B_B,
    /*60*/ NEG_MEM_A,
    /*61*/ NEG_MEM_B,
    /*62*/ NEG_MEM_ZP_A,
    /*63*/ NEG_MEM_ZP_B,
    /*64*/ NEG_STC_A,
    /*65*/ NEG_STC_B,
    /*66*/ ADD_A,
    /*67*/ ADD_B,
    /*68*/ ADD_MEM,
    /*69*/ ADD_MEM_ZP,
    /*70*/ ADD_STC,
    /*71*/ SUB_A_AB,
    /*72*/ SUB_A_BA,
    /*73*/ SUB_B_AB,
    /*74*/ SUB_B_BA,
    /*75*/ SUB_MEM_AB,
    /*76*/ SUB_MEM_BA,
    /*77*/ SUB_MEM_ZP_AB,
    /*78*/ SUB_MEM_ZP_BA,
    /*79*/ SUB_STC_AB,
    /*80*/ SUB_STC_BA,
    /*81*/ DIV2_A_A,
    /*82*/ DIV2_A_B,
    /*83*/ DIV2_B_A,
    /*84*/ DIV2_B_B,
    /*85*/ DIV2_MEM_A,
    /*86*/ DIV2_MEM_B,
    /*87*/ DIV2_MEM_ZP_A,
    /*88*/ DIV2_MEM_ZP_B,
    /*89*/ DIV2_STC_A,
    /*90*/ DIV2_STC_B,
    /*91*/ INV_A_A,
    /*92*/ INV_A_B,
    /*93*/ INV_B_A,
    /*94*/ INV_B_B,
    /*95*/ INV_MEM_A,
    /*96*/ INV_MEM_B,
    /*97*/ INV_MEM_ZP_A,
    /*98*/ INV_MEM_ZP_B,
    /*99*/ INV_STC_A,
    /*100*/ INV_STC_B,
    /*101*/ OR_A,
    /*102*/ OR_B,
    /*103*/ OR_MEM,
    /*104*/ OR_MEM_ZP,
    /*105*/ OR_STC,
    /*106*/ AND_A,
    /*107*/ AND_B,
    /*108*/ AND_MEM,
    /*109*/ AND_MEM_ZP,
    /*110*/ AND_STC,
    /*111*/ XOR_A,
    /*112*/ XOR_B,
    /*113*/ XOR_MEM,
    /*114*/ XOR_MEM_ZP,
    /*115*/ XOR_STC,
    /*116*/ SHR_A_A,
    /*117*/ SHR_A_B,
    /*118*/ SHR_B_A,
    /*119*/ SHR_B_B,
    /*120*/ SHR_MEM_A,
    /*121*/ SHR_MEM_B,
    /*122*/ SHR_MEM_ZP_A,
    /*123*/ SHR_MEM_ZP_B,
    /*124*/ SHR_STC_A,
    /*125*/ SHR_STC_B,
    /*126*/ SHL_A_A,
    /*127*/ SHL_A_B,
    /*128*/ SHL_B_A,
    /*129*/ SHL_B_B,
    /*130*/ SHL_MEM_A,
    /*131*/ SHL_MEM_B,
    /*132*/ SHL_MEM_ZP_A,
    /*133*/ SHL_MEM_ZP_B,
    /*134*/ SHL_STC_A,
    /*135*/ SHL_STC_B,
    /*136*/ CMP_A_B,
    /*137*/ CMP_B_A,
    /*138*/ CMP_TH_TL,
    /*139*/ CMP_TL_TH,
    /*140*/ CMP_TH_A,
    /*141*/ CMP_A_TH,
    /*142*/ CMP_TH_B,
    /*143*/ CMP_B_TH,
    /*144*/ CMP_TL_A,
    /*145*/ CMP_A_TL,
    /*146*/ CMP_TL_B,
    /*147*/ CMP_B_TL,
    /*148*/ CMP_INT_A,
    /*149*/ CMP_A_INT,
    /*150*/ CMP_INT_B,
    /*151*/ CMP_B_INT,
    /*152*/ CLR_A,
    /*153*/ CLR_B,
    /*154*/ CLR_TH,
    /*155*/ CLR_TL,
    /*156*/ CLR_T,
    /*157*/ INC_A,
    /*158*/ INC_B,
    /*159*/ INC_T,
    /*160*/ DEC_A,
    /*161*/ DEC_B,
    /*162*/ DEC_T,
    /*163*/ JMP_IMM,
    /*164*/ JMP_IMM_S,
    /*165*/ JMP_IMM_NS,
    /*166*/ JMP_IMM_T_S,
    /*167*/ JMP_IMM_T_NS,
    /*168*/ JMP_IMM_P,
    /*169*/ JMP_IMM_NP,
    /*170*/ JMP_IMM_T_P,
    /*171*/ JMP_IMM_T_NP,
    /*172*/ JMP_IMM_Z,
    /*173*/ JMP_IMM_NZ,
    /*174*/ JMP_IMM_T_Z,
    /*175*/ JMP_IMM_T_NZ,
    /*176*/ JMP_IMM_C,
    /*177*/ JMP_IMM_NC,
    /*178*/ JMP_IMM_T_C,
    /*179*/ JMP_IMM_T_NC,
    /*180*/ JMP_IMM_O,
    /*181*/ JMP_IMM_NO,
    /*182*/ JMP_IMM_T_O,
    /*183*/ JMP_IMM_T_NO,
    /*184*/ JMP_REL,
    /*185*/ JMP_REL_S,
    /*186*/ JMP_REL_NS,
    /*187*/ JMP_REL_TL_S,
    /*188*/ JMP_REL_TL_NS,
    /*189*/ JMP_REL_P,
    /*190*/ JMP_REL_NP,
    /*191*/ JMP_REL_TL_P,
    /*192*/ JMP_REL_TL_NP,
    /*193*/ JMP_REL_Z,
    /*194*/ JMP_REL_NZ,
    /*195*/ JMP_REL_TL_Z,
    /*196*/ JMP_REL_TL_NZ,
    /*197*/ JMP_REL_C,
    /*198*/ JMP_REL_NC,
    /*199*/ JMP_REL_TL_C,
    /*200*/ JMP_REL_TL_NC,
    /*201*/ JMP_REL_O,
    /*202*/ JMP_REL_NO,
    /*203*/ JMP_REL_TL_O,
    /*204*/ JMP_REL_TL_NO,
    /*205*/ JMP_FUN,
    /*206*/ JMP_RET,
    /*207*/ PUSH_A,
    /*208*/ PUSH_B,
    /*209*/ PUSH_TH,
    /*210*/ PUSH_TL,
    /*211*/ PUSH_F,
    /*212*/ PUSH_INT,
    /*213*/ PUSH_T,
    /*214*/ PUSH_IMM,
    /*215*/ PUSH_ABS,
    /*216*/ PUSH_ABS_ZP,
    /*217*/ POP_A,
    /*218*/ POP_B,
    /*219*/ POP_TH,
    /*220*/ POP_TL,
    /*221*/ POP_T,
    /*222*/ POP_MEM,
    /*223*/ POP_MEM_ZP,
    /*224*/ NOP,
    /*225*/ SKIP,
    /*226*/ SKIP_1,
    /*227*/ SKIP_2,
    /*228*/ ISR,
    /*229*/ IRET,
    /*230*/ INT0,
    /*231*/ HALT,
    /*232*/ LABEL  // this is not a hardware instruction, but a label for the assembler
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
  static constexpr std::size_t typesCount_ = 234;
  static std::string typeToString_[typesCount_];
  static std::string typeToAssembly_[typesCount_];

  Type type_;
  std::vector<std::string> operands_;
};
}  // namespace machine_code

#endif  // MACHINE_CODE_MACHINE_INSTRUCTION_HPP