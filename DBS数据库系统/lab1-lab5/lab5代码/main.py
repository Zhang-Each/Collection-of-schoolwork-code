import mysql.connector
import login
import normal
import manager

# 连接数据库
mydb = mysql.connector.connect(
    host="localhost",  # 数据库主机地址
    user="root",  # 数据库用户名
    passwd="zjxczyc123"  # 数据库密码
)
print("Access to the library database!")

# 建立cursor进行操作
mycursor = mydb.cursor()
mycursor.execute("use library;")
mycursor.execute("select * from user;")
# mydb.commit()  # 更新时必须写这一句话

# 读取用户的账号列表
user_list = {}
for x in mycursor:
    name = x[0]
    code = x[1]
    is_admin = x[2]
    user_list[name] = [code, is_admin]
# print(user_list)

program_end = 0
while program_end != 1:
    success_log, user_name = login.log_in(user_list)
    if success_log > 0:
        print("Log in success!")
        # 图书管理员可以进行的操作
        if success_log == 1:
            print("You are manager of the library!")
            manager_user = manager.Manager(user_name)
            manager_user.run()
        # 普通用户可以进行的操作
        else:
            print("You are a normal user of library!")
            normal_user = normal.NormalUser(user_name)
            normal_user.run()
        # print(user_name)
        # 如果是可以正常使用的用户则使用完成后要跳出该循环
        program_end = 1

    # 以下两种情况需要重新输入密码直到正确为止才可以登录
    elif success_log == 0:
        print("PassWord Error! Log in failed! Please try again!")
    elif success_log == -1:
        print("User ID doesn't exist!")
print("-----------See you next time!-------------")
