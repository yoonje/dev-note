def selection_sort(data_list):
    for stand in range(len(data_list) - 1):
        lowest = stand
        for index in range(stand + 1, len(data_list)):
            if data_list[lowest] > data_list[index]:
                lowest = index
        data_list[lowest], data_list[stand] = data_list[stand], data_list[lowest]
    return data_list