# 출발 노드와 도착 노드를 입력 받고 각 노드들까지의 최단 거리 배열과 도착 노드까지의 최단 경로를 리턴하는 벨만 포드 함수

def bellman_ford(graph, start, end):
    
    # 시작 정점에서 각 정점까지의 거리를 저장할 딕셔너리를 생성하고, 무한대(inf)로 초기화
    distances = {vertex: [float('inf'), None] for vertex in graph}

    # 그래프의 시작 정점의 거리는 0으로 시작 정점 이전에 방문한 정점는 시작 정점으로 초기화 해줌
    distances[start] = [0, start]

    # 그래프의 모든 정점 -1 번에 대해서 반복 + negative cycle 체크 => 정점의 개수만큼 반복
    for i in range(len(mygraph)):

        # 그래프에서 순서 상관없이 방문할 정점을 얻어옴
        for vertex in graph:

            # 현재 방문한 정점의 인접 정점들과의 엣지 정보를 가져옴
            for adjacent, weight in graph[vertex].items():

                # 현재 방문 정점과의 거리와 가중치를 더하여 후보가 되는 거리값 생성
                distance = distances[vertex][0] + weight

                # 만약 시작 정점에서 인접 정점으로 바로 가는 것보다 현재 방문한 정점을 통해 가는 것이 더 최단일 경우
                if distance < distances[adjacent][0]:

                    # 인접 정점 까지의 거리와 이전에 방문해야할 정점(현재 방문한 정점)를 전체 거리 배열에 업데이트
                    distances[adjacent] = distance, vertex

                    # negative cycle하는 부분
                    if i == len(mygraph)-1:
                        return False

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
        'A': {'B': -1, 'C': 4},
        'B': {'C': 3, 'D': 2, 'E': 2},
        'C': {},
        'D': {'C': 5, 'B': 1},
        'E': {'D': -3}
    }

    print(bellman_ford(mygraph, 'A', 'D'))
