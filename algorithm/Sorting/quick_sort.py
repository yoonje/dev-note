def quick_sort(data_list):
    if len(data_list) <= 1:
        return data_list
    
    left, right = list(), list()
    pivot = data_list[0]
    
    for index in range(1, len(data_list)):
        if pivot > data_list[index]:
            left.append(data_list[index])
        else:
            right.append(data_list[index])
    
    return quick_sort(left) + [pivot] + quick_sort(right)