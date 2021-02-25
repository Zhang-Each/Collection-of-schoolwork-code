class MIPS:
    # the basic instructions of mips
    # the R instructions
    instruction_r = {"100000": "add", "100001": "addu", "100010": "sub", "100011": "subu", "100100": "and",
                     "100101": "or", "100110": "xor", "100111": "nor", "101010": "slt", "101011": "sltu",
                     "000000": "sll", "000010": "srl", "000011": "sra", "000100": "sllv", "000110": "srlv",
                     "000111": "srav", "001000": "jr"}
    # the I instructions
    instruction_i = {"001000": "addi", "001001": "addiu", "001100": "andi", "001101": "ori", "001110": "xori",
                     "000100": "beq", "000101": "bne", "001010": "slti", "001111": "lui", "100011": "lw",
                     "100001": "lh", "100101": "lhu", "101011": "sw", "101001": "sh"}
    # the J instructions
    instruction_j = {"000010": "j", "000011": "jr"}

    # the registers
    register = {"00000": "$zero", "000001": "$at", "00010": "$v0", "00011": "$v1", "00100": "$a0", "00101": "$a1",
                "00110": "$a2", "00111": "$a3", "01000": "$t0", "01001": "$t1", "01010": "$t2", "01011": "$t3",
                "01100": "$t4", "01101": "$t5", "$01110": "$t6", "01111": "$t7", "10000": "$s0", "10001": "$s1",
                "10010": "$s2", "10011": "$s3", "10100": "$s4", "10101": "$s5", "10110": "$s6", "10111": "$s7",
                "11000": "$t8", "11001": "$t9", "11010": "$k0", "11011": "$k1", "11100": "gp", "11101": "sp",
                "11110": "fp", "11111": "ra"}

    def __init__(self, line):
        self.machine_code = line

    def getInstruction(self, op):
        return self.instruction_r[op]

    def getRegister(self, r):
        return self.register[r]

    # calculate the value of shamt for R instructions
    def getShamt(self):
        shamt = self.machine_code[21:26]
        result = 0
        binary_num = [16, 8, 4, 2, 1]
        for i in range(0, 5):
            if shamt[i] == '1':
                result += binary_num[i]
        return str(result)

    # the main function of machine_code change
    def translate(self):
        op_code = self.machine_code[0:6]
        if op_code == "000000":
            return self.translate_R()
        elif op_code in self.instruction_i:
            return self.translate_I()
        else:
            return self.translate_J()

    def translate_R(self):
        func = self.machine_code[26:32]
        rs = self.machine_code[6:11]
        rt = self.machine_code[11:16]
        rd = self.machine_code[16:21]
        r_2 = ["000000", "000010", "000011"]

        # kind 3: jr
        if func == "001000":
            op_reg = self.getRegister(rs)
            split_mips = [self.getInstruction(func), op_reg]
        # kind 2:
        elif func == "000000" or func == "000010" or func == "000011":
            shamt = self.getShamt()
            op_reg = self.getRegister(rd) + ',' + self.getRegister(rt) + ',' + shamt
            split_mips = [self.getInstruction(func), self.getRegister(rd), self.getRegister(rt), shamt]
        # kind 1: the most common
        else:
            op_reg = self.getRegister(rd) + "," + self.getRegister(rs) + "," + self.getRegister(rt)
            split_mips = [self.getInstruction(func), self.getRegister(rd), self.getRegister(rs), self.getRegister(rt)]
        result = self.getInstruction(func) + " " + op_reg

        return result, split_mips

    # I 型指令的返回的结构都按照操作码，两个寄存器和立即数这样的形式返回
    def translate_I(self):
        op_code = self.machine_code[0:6]
        rs = self.machine_code[6:11]
        rt = self.machine_code[11:16]  # 被操作寄存器
        immediate = self.getImmediate(16)
        result = ""
        kind_1 = ["001000", "001001", "001100", "101011", "001110", "000100", "000101"]
        # 第一类，形如xxx rs，rt，immediate
        if op_code in kind_1:
            result += self.instruction_i[op_code] + " "
            op_reg = self.register[rt] + "," + self.register[rs] + ","
            result += op_reg + immediate
            split_mips = [self.instruction_i[op_code], self.register[rt], self.register[rs], immediate]
        # 第二类，形如xxx rs，immediate（rt）
        else:
            # Instruction-i II
            result += self.instruction_i[op_code] + " "
            result += self.getRegister(rt) + "," + immediate + '(' + self.register[rs] + ')'
            split_mips = [self.instruction_i[op_code], self.register[rt], self.register[rs], immediate]
        return result, split_mips

    # 翻译J类指令的成员函数
    def translate_J(self):
        result = ""
        op_code = self.machine_code[0:6]
        result += self.instruction_j[op_code]
        immediate = self.getImmediate(26)
        result += " " + immediate
        split_mips = [self.instruction_j[op_code], immediate]
        return result, split_mips

    # 计算立即数，n表示立即数的位数，有16位和26位两种
    def getImmediate(self, n):
        result = 0
        if n == 16:
            num = self.machine_code[16:32]
        elif n == 26:
            num = self.machine_code[6:32]
        for i in range(n):
            if num[i] == '1':
                result += 2 ** (n - 1 - i)
        return str(result)


# 对每条指令进行处理的函数
def process(info):
    machine_codes = info.split('\n')
    mips = []
    split_mips = []
    for i in range(0, len(machine_codes) - 1):
        instruction = MIPS(machine_codes[i])
        a, b = instruction.translate()
        mips.append(a)
        split_mips.append(b)
    result = '\n'.join(mips)
    return result, split_mips
