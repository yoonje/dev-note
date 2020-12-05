# 출발 노드와 도착 노드를 입력 받고 각 노드들까지의 최단 거리 배열과 도착 노드까지의 최단 경로를 리턴하는 다익스트라 함수

import heapq

# 탐색할 그래프와 시작 정점 그리고 도착 정점을 인수로 전달받음
def dijkstra(graph, start, end):

    # 시작 정점에서 각 정점까지의 거리를 저장할 딕셔너리를 생성하고, 거리는 무한대(inf)로 초기화하고 이전에 방문할 정점는 시작 정점으로
    distances = {vertex: [float('inf'), None] for vertex in graph}

    # 그래프의 시작 정점의 거리는 0으로 시작 정점 이전에 방문한 정점는 시작 정점으로 초기화 해줌
    distances[start] = [0, start]

    # 모든 정점이 저장될 큐를 생성
    queue = []

    # 그래프의 시작 정점과 시작 정점의 거리(0)을 최소힙에 넣어줌
    heapq.heappush(queue, [distances[start][0], start])

    while queue:
        
        # 큐에서 정점과 시작 정점 사이의 가중치를 업데이트
        current_distance, current_vertex = heapq.heappop(queue)
        
        # 현재 힙에서 가져온 현재 방문 정점과의 거리보다 기존에 저장되어 있던 경로 배열에 더 짧은 거리가 있다면 처음부터 무시
        if distances[current_vertex][0] < current_distance:
            continue
            
        for adjacent, weight in graph[current_vertex].items():
            
            # 현재 방문 정점과의 거리와 가중치를 더하여 후보가 되는 거리값 생성
            distance = current_distance + weight
            
            # 만약 시작 정점에서 인접 정점으로 바로 가는 것보다 현재 방문한 정점을 통해 가는 것이 더 최단일 경우
            if distance < distances[adjacent][0]:
                
                # 인접 정점 까지의 거리와 이전에 방문해야할 정점(현재 방문한 정점)를 전체 거리 배열에 업데이트
                distances[adjacent] = [distance, current_vertex]
                
                # 큐에 인접 정점 까지의 거리와 인접 정점를 삽입
                heapq.heappush(queue, [distance, adjacent])
    
    # 도착 정점 설정하여 도착 정점부터 추적에 이용
    path = end
    path_output = end + '<-'
    
    # 최단 경로를 위해 도착 정점을 가기 전 방문해야할 정점이 시작 정점이 아니면 반복
    while distances[path][1] != start:

        # 경로 결과에 현재 정점 이전에 방문해야할 정점을 더해줌
        path_output += distances[path][1] + '<-'
        
        # 현재 정점 이전에 방문해야할 정점으로 업데이트
        path = distances[path][1]
    
    # 경로 결과에 최종적으로 시작 정점을 더해줌
    path_output += start
    
    return distances, path_output


if __name__ == "__main__":
    mygraph = {
        'A': {'B': 8, 'C': 1, 'D': 2},
        'B': {},
        'C': {'B': 5, 'D': 2},
        'D': {'E': 3, 'F': 5},
        'E': {'F': 1},
        'F': {'A': 5}
    }

    print(dijkstra(mygraph, 'A', 'F'))