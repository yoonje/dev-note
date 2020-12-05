def insertion_sort(data_list):
    for index in range(len(data_list) - 1):
        for index2 in range(index + 1, 0, -1):
            if data_list[index2] < data_list[index2 - 1]:
                data_list[index2], data_list[index2 - 1] = data_list[index2 - 1], data_list[index2]
            else:
                break
    return data_list