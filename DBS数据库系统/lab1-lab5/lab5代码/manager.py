import mysql.connector


def check_select():
    print("Please input the information of the book you want, choose the query you want:")
    print("1. 通过书名查找")
    print("2. 通过编号查找")
    print("3. 通过作者查找")
    print("4. 通过出版年份查找")
    print("5. 显示所有书籍的信息")
    choose = int(input("输入你的选择:"))
    if choose == 1:
        info = input("输入书名:")
    elif choose == 2:
        info = input("输入书本编号:")
    elif choose == 3:
        info = input("输入作者姓名:")
    elif choose == 4:
        info = input("输入出版年份的范围(after或者before): ")
    elif choose == 5:
        return choose, "all"
    else:
        return check_select()
    return choose, info


def print_book(x, book):
    print("----------------")
    print("书名: ", x)
    print("编号: ", book[x][0])
    print("作者: ", book[x][1])
    print("剩余数量: ", book[x][2])
    print("总数: ", book[x][3])
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
    elif kind == 4:
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
    # 查询所有图书的信息
    elif kind == 5:
        count = 0
        for x in book:
            print_book(x, book)
            count += 1
        print("Find totally ", count, " books")


def add_book(mydb):
    mycursor = mydb.cursor()
    sql = "insert into books values"
    print("请输入新增图书的相关信息：")
    name = input("书名:")
    book_id = input("编号:")
    author = input("作者:")
    num = int(input("数量:"))
    year = input("出版年份:")
    name = "'" + name + "',"
    book_id = "'" + book_id + "',"
    author = "'" + author + "',"
    amount = str(num) + ","
    total_amount = amount
    sql += "(" + name + book_id + author + amount + total_amount + year + ");"
    mycursor.execute(sql)
    mydb.commit()
    print("新增书籍成功!")


def delete_book(mydb):
    mycursor = mydb.cursor()
    print("请输入你想要删除的图书信息:")
    print("1. 输入书名")
    print("2. 输入编号")
    choice = int(input("输入操作类型:"))
    if choice == 1:
        name = input("输入书名:")
        sql = "delete from books where book_name = " + "'" + name + "';"
        mycursor.execute(sql)
        mydb.commit()
        print("下架成功！")
    elif choice == 2:
        book_id = input("输入编号:")
        sql = "delete from books where book_id = " + "'" + book_id + "';"
        mycursor.execute(sql)
        mydb.commit()
        print("下架成功！")
    else:
        print("发生错误，请重试！")


class Manager:
    def __init__(self, name):
        self.name = name

    def print_operation(self):
        print("----------------------------------------------------------------")
        print("Dear Manager " + self.name, end='. ')
        print("本系统支持如下操作:")
        print("1. 查询信息")
        print("2. 上架新书")
        print("3. 下架旧书")
        print("4. 退出系统")

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
            op_code = int(input("你的选择是:"))
            # 查询当前图书的信息
            if op_code == 1:
                check_book(mydb)
            # 上架新书
            elif op_code == 2:
                add_book(mydb)
            # 下架旧书
            elif op_code == 3:
                program_end = 0
                delete_book(mydb)
            # 退出管理系统
            else:
                program_end = 1
