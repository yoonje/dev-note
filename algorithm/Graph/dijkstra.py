# 출발 노드에서 각 노드들까지의 최단 거리 배열을 리턴하는 다익스트라 함수

import heapq

# 탐색할 그래프와 시작 정점을 인수로 전달받음
def dijkstra(graph, start):
    
    # 시작 정점에서 각 정점까지의 거리를 저장할 딕셔너리를 생성하고, 무한대(inf)로 초기화
    distances = {node: float('inf') for node in graph}
    
    # 그래프의 시작 정점의 거리는 0으로 초기화 해줌
    distances[start] = 0
    
    # 모든 정점이 저장될 큐를 생성
    queue = []
    
    # 그래프의 시작 정점과 시작 정점의 거리(0)을 최소힙에 넣어줌
    heapq.heappush(queue, [distances[start], start])
    
    while queue:

        # 큐에서 정점과 시작 정점 사이의 가중치를 업데이트
        current_distance, current_node = heapq.heappop(queue)
        
        # 현재 힙에서 가져온 현재 방문 정점와의 거리보다 기존에 저장되어 있던 경로 배열에 더 짧은 거리가 있다면 처음부터 무시
        if distances[current_node] < current_distance:
            continue
            
        for adjacent, weight in graph[current_node].items():
            
            # 현재 방문 정점와의 거리와 가중치를 더하여 후보가 되는 거리값 생성
            distance = current_distance + weight
            
            # 만약 시작 정점에서 인접 정점으로 바로 가는 것보다 현재 방문한 정점을 통해 가는 것이 더 가까울 경우
            if distance < distances[adjacent]:
                
                # 인접 정점 까지의 거리를 전체 거리 배열에 업데이트
                distances[adjacent] = distance
                
                # 큐에 인접 정점 까지의 거리와 인접 정점를 삽입
                heapq.heappush(queue, [distance, adjacent])
                
    return distances


if __name__ == "__main__":
    mygraph = {
        'A': {'B': 8, 'C': 1, 'D': 2},
        'B': {},
        'C': {'B': 5, 'D': 2},
        'D': {'E': 3, 'F': 5},
        'E': {'F': 1},
        'F': {'A': 5}
    }

    print(dijkstra(mygraph, 'A'))
