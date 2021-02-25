import mysql.connector


def check_select():
    print("Please input the information of the book you want, choose the query you want:")
    print("1. 通过书名查找")
    print("2. 通过编号查找")
    print("3. 通过作者查找")
    print("4. 通过出版年份查找")
    choose = int(input("输入你的选择:"))
    if choose == 1:
        info = input("输入书名:")
    elif choose == 2:
        info = input("输入书本编号:")
    elif choose == 3:
        info = input("输入作者姓名:")
    elif choose == 4:
        info = input("输入出版年份的范围(after或者before): ")
    else:
        return check_select()
    return choose, info


def print_book(x, book):
    print("----------------")
    print("书名: ", x)
    print("编号: ", book[x][0])
    print("作者: ", book[x][1])
    print("剩余数量: ", book[x][2])
    print("出版年份: ", book[x][4])
    print("----------------")


def check_book(mydb):
    mycursor = mydb.cursor()
    mycursor.execute("select * from books;")
    book = {}
    # 同样也是读取当前数据库中的内容，根据查询条件列出符合的项
    for i in mycursor:
        book[i[0]] = [i[1], i[2], i[3], i[4], i[5]]
    kind, info = check_select()
    # 情况1，通过书名来查询
    print("------------Query Result--------------")
    if kind == 1:
        for x in book:
            if x == info:
                print_book(x, book)
    # 情况2，通过ID来查询
    elif kind == 2:
        for x in book:
            if book[x][0] == info:
                print_book(x, book)
    # 情况3，通过作者来查询
    elif kind == 3:
        count = 0
        for x in book:
            if book[x][1] == info:
                print_book(x, book)
                count += 1
        print("Find totally ", count, " books")
    # 根据出版年份来查询
    else:
        op = info.split(' ')
        count = 0
        if op[0] == "after":
            for x in book:
                if int(book[x][4]) >= int(op[1]):
                    print_book(x, book)
                    count += 1
        elif op[0] == "before":
            for x in book:
                if int(book[x][4]) <= int(op[1]):
                    print_book(x, book)
                    count += 1
        print("Find totally ", count, " books")


def return_book(mydb, name):
    mycursor = mydb.cursor()
    mycursor.execute("select book_name,amount from books;")
    book = {}
    # 读取所有图书馆中存在的藏书和当前的数量
    for i in mycursor:
        book[i[0]] = i[1]
    # print(book)
    book_name = input("Please input the name of book:")
    # 没有找到输入的书名
    if book_name not in book:
        print("No such book!")
        return 0
    else:
        new_amount = book[book_name] + 1
        sql = "update books set amount=" + str(new_amount) + " where book_name=" + "'" + book_name + "';"
        mycursor.execute(sql)
        mydb.commit()
        # 生成一条归还记录
        sql_history = "insert into history values (" + "'" + book_name + "'," + str(1) + ",'" + name + "');"
        mycursor.execute(sql_history)
        mydb.commit()
        # print(sql_history)
        # 更新用户信息中的借阅数目
        mycursor.execute("select borrow from user where user_id = " + "'" + name + "';")
        for i in mycursor:
            num = i[0] - 1
        mycursor.execute("update user set borrow=" + str(num) + " where user_id=" + "'" + name + "';")
        mydb.commit()
        print("Success to return this book!")


def borrow_book(mydb, name):
    mycursor = mydb.cursor()
    mycursor.execute("select book_name,amount from books;")
    book = {}
    # 读取所有图书馆中存在的藏书和当前的数量
    for i in mycursor:
        book[i[0]] = i[1]
    # print(book)
    book_name = input("Please input the name of book:")
    # 没有找到输入的书名
    if book_name not in book:
        print("No such book!")
        return 0
    # 书借完了就会借书失败
    elif book[book_name] == 0:
        print("The books are all lent by others!")
        return 0
    # 正常借书
    else:
        new_amount = book[book_name] - 1
        sql = "update books set amount=" + str(new_amount) + " where book_name=" + "'" + book_name + "';"
        mycursor.execute(sql)
        mydb.commit()
        # 生成一条借阅记录
        sql_history = "insert into history values (" + "'" + book_name + "'," + str(0) + ",'" + name + "');"
        mycursor.execute(sql_history)
        mydb.commit()
        # print(sql_history)
        # 更新用户信息中的借阅数目
        mycursor.execute("select borrow from user where user_id = " + "'" + name + "';")
        for i in mycursor:
            num = i[0] + 1
        mycursor.execute("update user set borrow=" + str(num) + " where user_id=" + "'" + name + "';")
        mydb.commit()
        print("Success to borrow this book!")


def log_out_user(mydb, name):
    mycursor = mydb.cursor()
    # 获取用户的密码
    mycursor.execute("select passwd,borrow from user where user_id=" + "'" + name + "';")
    for i in mycursor:
        true_pass_word = i[0]
        borrow_num = i[1]
    input_pass_word = input("请输入您的密码以确认注销:")
    # 密码错误则结束
    if input_pass_word != true_pass_word:
        print("密码错误!")
        return
    # 如果有未归还的书则不能注销
    elif borrow_num > 0:
        print("有书未归还，请在归还所有书籍之后再注销账号！")
        return
    # 正常情况，密码被修改了
    else:
        sql = "delete from user where user_id="+"'"+name+"';"
        mycursor.execute(sql)
        mydb.commit()
        print("账户已经注销!")


def change_password(mydb, name):
    mycursor = mydb.cursor()
    # 获取用户的密码
    mycursor.execute("select passwd from user where user_id=" + "'" + name + "';")
    for i in mycursor:
        true_pass_word = i[0]
    input_pass_word = input("请输入您的密码以确认:")
    if input_pass_word != true_pass_word:
        print("密码错误!")
        return
    else:
        new_password = input("请输入新密码:")
        new_password_again = input("请确认新密码:")
        if new_password != new_password_again:
            print("两次输入的密码不一致!")
            return
        else:
            sql = "update user set passwd="+"'"+new_password+"'"+"where user_id="+"'"+name+"';"
            mycursor.execute(sql)
            mydb.commit()
            print("修改密码成功!")


class NormalUser:
    def __init__(self, name):
        self.name = name
        print("Welcome to the library management system!")

    def print_operation(self):
        print("----------------------------------------------------------------")
        print("Dear " + self.name, end='. ')
        print("本系统支持如下操作:")
        print("1. 查询信息")
        print("2. 借取书籍")
        print("3. 归还书籍")
        print("4. 退出系统")
        print("5. 注销账户")
        print("6. 修改密码")

    def run(self):
        mydb = mysql.connector.connect(
            host="localhost",  # 数据库主机地址
            user="root",  # 数据库用户名
            passwd="zjxczyc123"  # 数据库密码
        )
        mycursor = mydb.cursor()
        mycursor.execute("use library;")

        program_end = 0
        while program_end != 1:
            self.print_operation()
            op_code = int(input("输入你的选择:"))
            # 查询书本信息
            if op_code == 1:
                check_book(mydb)
            # 借书
            elif op_code == 2:
                borrow_book(mydb, self.name)
            # 还书
            elif op_code == 3:
                return_book(mydb, self.name)
            # 退出
            elif op_code == 4:
                program_end = 1
            elif op_code == 5:
                log_out_user(mydb, self.name)
            elif op_code == 6:
                change_password(mydb, self.name)

