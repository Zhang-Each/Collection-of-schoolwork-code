class Assembly:
    register = {"$zero": 'NULL', "$at": "NULL", "$v0": 'NULL', "$v1": 'NULL', "$a0": 'NULL', "$a1": 'NULL',
                "$a2": 'NULL', "$a3": 'NULL', "$t0": 'NULL', "$t1": 'NULL', "$t2": 'NULL', "$t3": 'NULL',
                "$t4": 'NULL', "$t5": 'NULL', "$t6": 'NULL', "$t7": 'NULL', "$s0": 'NULL', "$s1": 'NULL',
                "$s2": 'NULL', "$s3": 'NULL', "$s4": 'NULL', "$s5": 'NULL', "$s6": 'NULL', "$s7": 'NULL',
                "$t8": 'NULL', "$t9": 'NULL', "$k0": 'NULL', "$k1": 'NULL', "gp": 'NULL', "sp": 'NULL',
                "fp": 'NULL', "ra": 'NULL'}

    def __init__(self):
        self.register["$zero"] = 0

    def execute(self, instructions):
        i = 0
        # print(len(instructions))
        while i != len(instructions):
            i = self.singleLine(instructions[i], i)
        return self.getResult()

    def debug(self, instructions):
        i = 0
        # print(len(instructions))
        result = ""
        while i != len(instructions):
            result += "Execute Instruction " + str(i+1) + ": " + " ".join(instructions[i]) + "\n"
            i = self.singleLine(instructions[i], i)
            single_step = self.getResult()
            result += single_step
        return result

    def singleLine(self, mips, i):
        op = mips[0]
        if op == "add" or op == "addu":
            self.add(mips)
            return i + 1
        elif op == "addi":
            self.addi(mips)
            return i + 1
        elif op == "sub" or op == "subu":
            self.sub(mips)
            return i + 1
        elif op == "and":
            self.and_mips(mips)
            return i + 1
        elif op == "or":
            self.or_mips(mips)
            return i + 1
        elif op == "nor":
            self.nor(mips)
            return i + 1
        elif op == "xor":
            self.xor(mips)
            return i + 1
        elif op == "andi":
            self.addi(mips)
            return i + 1
        elif op == "ori":
            self.ori(mips)
            return i + 1
        elif op == "xori":
            self.xori(mips)
            return i + 1
        elif op == "nori":
            self.nori(mips)
            return i + 1
        elif op == "sll":
            self.sll(mips)
            return i + 1
        elif op == "srl":
            self.srl(mips)
            return i + 1
        elif op == "sra":
            self.sra(mips)
            return i + 1
        elif op == "sllv":
            self.sllv(mips)
            return i + 1
        elif op == "srlv":
            self.srlv(mips)
            return i + 1
        elif op == "srav":
            self.srav(mips)
            return i + 1
        elif op == "lw":
            self.lw(mips)
            return i + 1
        elif op == "sw":
            self.sw(mips)
            return i + 1
        elif op == "slt":
            self.slt(mips)
            return i + 1
        elif op == "sltu":
            self.sltu(mips)
            return i + 1
        elif op == "slti":
            self.slti(mips)
            return i + 1
        elif op == "sltiu":
            self.sltiu(mips)
            return i + 1
        elif op == "beq":
            result = self.beq(mips)
            if result == 1:
                return int(mips[3])
            else:
                return i + 1
        elif op == "bne":
            result = self.bne(mips)
            if result == 1:
                return int(mips[3])
            else:
                return i + 1
        elif op == "j" or op == "jal":
            return int(mips[1]) // 4

    def getResult(self):
        result = "----------Registers---------\n"
        for i in self.register:
            result += str(i) + '=' + str(self.register[i]) + '\n'
        return result

    def add(self, mips):
        self.register[mips[1]] = self.register[mips[2]] + self.register[mips[3]]

    def addi(self, mips):
        self.register[mips[1]] = self.register[mips[2]] + int(mips[3])

    def sub(self, mips):
        self.register[mips[1]] = self.register[mips[2]] - self.register[mips[3]]

    def and_mips(self, mips):
        self.register[mips[1]] = self.register[mips[2]] & self.register[mips[3]]

    def or_mips(self, mips):
        self.register[mips[1]] = self.register[mips[2]] | self.register[mips[3]]

    def xor(self, mips):
        self.register[mips[1]] = self.register[mips[2]] ^ self.register[mips[3]]

    def nor(self, mips):
        self.register[mips[1]] = ~(self.register[mips[2]] ^ self.register[mips[3]])

    def andi(self, mips):
        self.register[mips[1]] = self.register[mips[2]] & int(mips[3])

    def ori(self, mips):
        self.register[mips[1]] = self.register[mips[2]] | int(mips[3])

    def xori(self, mips):
        self.register[mips[1]] = self.register[mips[2]] ^ int(mips[3])

    def nori(self, mips):
        self.register[mips[1]] = ~(self.register[mips[2]] ^ int(mips[3]))

    def sll(self, mips):
        self.register[mips[1]] = self.register[mips[2]] << int(mips[3])

    def srl(self, mips):
        self.register[mips[1]] = self.register[mips[2]] >> int(mips[3])

    def sra(self, mips):
        self.register[mips[1]] = self.register[mips[2]] >> int(mips[3])

    def sllv(self, mips):
        self.register[mips[1]] = self.register[mips[2]] << self.register[mips[3]]

    def srlv(self, mips):
        self.register[mips[1]] = self.register[mips[2]] >> self.register[mips[3]]

    def srav(self, mips):
        self.register[mips[1]] = self.register[mips[2]] >> self.register[mips[3]]

    def lw(self, mips):
        self.register[mips[1]] = self.register[mips[2]][int(mips[3]) // 4]

    def sw(self, mips):
        self.register[mips[2]][int(mips[3]) // 4] = self.register[mips[1]]

    def slt(self, mips):
        if self.register[mips[2]] < self.register[mips[3]]:
            self.register[mips[1]] = 1
        else:
            self.register[mips[1]] = 0

    def sltu(self, mips):
        if self.register[mips[2]] < self.register[mips[3]]:
            self.register[mips[1]] = 1
        else:
            self.register[mips[1]] = 0

    def slti(self, mips):
        if self.register[mips[2]] < int(mips[3]):
            self.register[mips[1]] = 1
        else:
            self.register[mips[1]] = 0

    def sltiu(self, mips):
        if self.register[mips[2]] < int(mips[3]):
            self.register[mips[1]] = 1
        else:
            self.register[mips[1]] = 0

    def beq(self, mips):
        if self.register[mips[1]] == self.register[mips[2]]:
            return 1
        else:
            return 0

    def bne(self, mips):
        if self.register[mips[1]] != self.register[mips[2]]:
            return 1
        else:
            return 0


def assembly(mips):
    mips_assembler = Assembly()
    # print("1")
    return mips_assembler.execute(mips)


def debug(mips):
    debug_assembler = Assembly()
    return debug_assembler.debug(mips)
