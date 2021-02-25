import tkinter as tk  # 使用Tkinter前需要先导入
import processor
import assembler

# 实例化object，建立窗口window
window = tk.Tk()
window.title('MIPS Assembler')
window.geometry('800x400')
label1 = tk.Label(window, text="MIPS转换器")
label1.grid(row=0, sticky='n')
box1 = tk.Text(window, height=20, width=40)
box1.grid(row=1, column=0)
box2 = tk.Text(window, height=20, width=40)
box2.grid(row=1, column=1)
box3 = tk.Text(window, height=20, width=40)
box3.grid(row=1, column=2)

global split_mips


# button1的作用是是对机器码进行翻译并将内容显示在box2中
def get_info():
    info = box1.get('0.0', 'end')
    global split_mips
    info, split_mips = processor.process(info)[0], processor.process(info)[1]
    box2.insert("insert", info)
    # split_mips是切分好的单条mips指令的列表， 用于在汇编过程中使用，减少了对整条指令的切分这样的一个复杂的过程
    print(split_mips)


# button2的作用是清除box2中的内容
def clear_info():
    box2.delete('0.0', 'end')
    # box3.delete('0.0', 'end')


# 生成汇编的结果
def assemble():
    global split_mips
    result = assembler.assembly(split_mips)
    box3.insert("insert", result)


def debug():
    global split_mips
    result = assembler.debug(split_mips)
    box3.insert("insert", result)


button1 = tk.Button(window, height=2, width=10, command=get_info, text="Compile")
button2 = tk.Button(window, height=2, width=10, command=clear_info, text="Clear")
button3 = tk.Button(window, height=2, width=10, command=assemble, text="Assemble")
button4 = tk.Button(window, height=2, width=10, command=debug, text="Debug")
button1.grid(row=2, column=0)
button2.grid(row=2, column=1)
button3.grid(row=2, column=2)
button4.grid(row=3, column=0)

window.mainloop()
