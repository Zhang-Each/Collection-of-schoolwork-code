def log_in(user_list):
    """
    :function:check the log in
    :param user_list
    :return:0 if access failed, 1 if user is admin, 2 for normal user, -1 if not exist
    """
    print("-------------Log In---------------------")
    user_name = input("Please input your User-ID:")
    user_word = input("Please input your pass-word:")
    # print(user_name, user_word)
    # 用户存在且密码正确
    if user_name not in user_list:
        return -1, "error"
    if user_name in user_list and user_word == user_list[user_name][0]:
        if user_list[user_name][1] == 0:
            return 2, user_name  # 普通用户
        else:
            return 1, user_name  # 管理员
    else:
        return 0, "error"
