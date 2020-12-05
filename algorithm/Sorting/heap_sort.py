import heapq

def heap_sort(data_list):
  heap = []
  for num in data_list:
    heapq.heappush(heap, num)
  
  sorted_data_list = []
  while heap:
    sorted_data_list.append(heapq.heappop(heap))
  return sorted_data_list