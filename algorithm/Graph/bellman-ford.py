# 출발 노드에서 각 노드들까지의 최단 거리 배열을 리턴하는 벨만 포드 함수

def bellman_ford(graph, start):
    
    # 시작 정점에서 각 정점까지의 거리를 저장할 딕셔너리를 생성하고, 무한대(inf)로 초기화
    distances = {vertex: float('inf') for vertex in graph}

    # 그래프의 시작 정점의 거리는 0으로 초기화
    distances[start] = 0

    # 그래프의 모든 정점 -1 번에 대해서 반복 + negative cycle 체크 => 정점의 개수만큼 반복
    for i in range(len(mygraph)):

        # 그래프에서 순서 상관없이 방문할 정점을 얻어옴
        for vertex in graph:

            # 현재 방문한 정점의 인접 정점들과의 엣지 정보를 가져옴
            for adjacent, weight in graph[vertex].items():

                # 현재 방문 정점과의 거리와 가중치를 더하여 후보가 되는 거리값 생성
                distance = distances[vertex] + weight

                # 만약 시작 정점에서 인접 정점으로 바로 가는 것보다 현재 방문한 정점을 통해 가는 것이 더 최단일 경우
                if distance < distances[adjacent]:

                    # 인접 정점 까지의 거리를 전체 거리 배열에 업데이트
                    distances[adjacent] = distance

                    # negative cycle하는 부분
                    if i == len(mygraph)-1:
                        return False

    return distances


if __name__ == "__main__":
    mygraph = {
        'A': {'B': -1, 'C': 4},
        'B': {'C': 3, 'D': 2, 'E': 2},
        'C': {},
        'D': {'C': 5, 'B': 1},
        'E': {'D': -3}
    }

    print(bellman_ford(mygraph, 'A'))
