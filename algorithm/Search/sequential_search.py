def sequential_search(data_list, search_data):
    for index in range(len(data_list)):
        if data_list[index] == search_data:
            return index
    return -1