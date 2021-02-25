import re
import os
import time
import string



count_dict = []
number_of_word = 0


# count the appearance of words in the text file
def word_count(file_path):
    """
    :param file_path: the path of the text file
    :return: a dictionary of words' appearance
    """
    fp = open(file_path)
    count = {}
    global number_of_word
    for line in fp:
        # reduce the formats in the text.
        words = re.sub(r"[%s]+" % string.punctuation, "", line)
        words = re.sub("\n", " ", words).split(' ')
        words = [x.lower() for x in words]
        # words = re.sub(r"[%s]+" % string.punctuation, "", line).split(' ')
        for single_word in words:
            number_of_word += 1
            if single_word in count.keys():
                count[single_word] += 1
            else:
                count[single_word] = 1
    # print(count)
    global count_dict
    count_dict.append(count)
    # print(count)


# find all the file path
def get_file_path():
    """
    :no param
    :return: a list of all the file paths
    """
    file_path = ".\\test data\\test4\\"
    path_set = []
    for file_name in os.listdir(file_path):
        path_set.append(file_path+file_name)
    return path_set


# show the result of the map-reduce algorithm
def show_result(result_map):
    """

    :param result_map: the result map that will be shown to us
    :return: none
    """
    # result_map.sort()
    count = 0
    for i in sorted(result_map.keys()):
        if count != 0:
            print(i, result_map[i])
        count += 1
    print("Total Number of different words:", count)


# the main function of map operation
def Map_Operation():
    file = get_file_path()
    # print(file)
    for i in file:
        word_count(i)
    # print(count_dict)


# the main function of reduce operation
def Reduce_Operation():
    global count_dict
    # print(count_dict)
    # print(len(count_dict))
    result = {}
    # i is a dict now
    for i in count_dict:
        # print(i)
        for j in i.keys():
            # print(j)
            if str(j).isdigit() == 0 and str(j) != " ":
                if str(j) in result.keys():
                    # print(1)
                    result[str(j)] += int(i[j])
                else:
                    # print(0)
                    result[str(j)] = int(i[j])
    # print(result)
    show_result(result)


if __name__ == '__main__':
    # test the running time of the program
    start = time.time()
    Map_Operation()
    # print(count_dict)
    Reduce_Operation()
    end = time.time()
    print("The number of total words:", number_of_word)
    print("Running time:", end-start)
