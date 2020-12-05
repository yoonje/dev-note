def bubble_sort(data_list):
    for index in range(len(data_list) - 1):
        swap = False
        for index2 in range(len(data_list) - index - 1):
            if data_list[index2] > data_list[index2 + 1]:
                data_list[index2], data_list[index2 + 1] = data_list[index2 + 1], data_list[index2]
                swap = True
        
        if swap == False:
            break
    return data_list