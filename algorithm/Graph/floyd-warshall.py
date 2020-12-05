def floyd_warshall(graph):
    
    # 노드 개수와 노드의 문자열 노드의 인덱스 값을 바로 알기 위한 테이블
    vertex_count = len(graph)
    vertex_table = {vertex: i for i, vertex in enumerate(graph)}

    # 최단 경로의 값을 표기할 리스트를 값으로 값고 있는 딕셔너리로 이뤄진 행렬
    distances = {vertex: [float('inf')] * vertex_count for vertex in graph}

    # 경로 탐색을 위한 정점과 다음 정점 딕셔너리
    next_vertices = {vertex: [None] * vertex_count for vertex in graph}

    for i, vertex in enumerate(distances):
        distances[vertex][i] = 0

    # 기본 데이터 저장
    for vertex in graph:
        for vertex2, weight in graph[vertex].items():
            distances[vertex][vertex_table[vertex2]] = weight
            next_vertices[vertex][vertex_table[vertex2]] = vertex2

    for vertex in graph:
        for vertex2 in graph:
            for vertex3 in graph:

                # 현재 거리 행렬에 있는 값보다 더 작은 값이 존재 하는 경우
                if distances[vertex2][vertex_table[vertex3]] > distances[vertex2][vertex_table[vertex]] + distances[vertex][vertex_table[vertex3]]:

                    # 전체 거리 배열에 업데이트
                    distances[vertex2][vertex_table[vertex3]] = distances[vertex2][vertex_table[vertex]] + distances[vertex][vertex_table[vertex3]]

                    # 경로 트래킹을 위해 다음 정점 저장
                    next_vertices[vertex2][vertex_table[vertex3]] = next_vertices[vertex2][vertex_table[vertex]]

    # 전체 경로 정점 리스트
    path_out = []

    # 최단 경로 정점 리스트 추적
    for vertex in graph:
        for vertex2 in graph:
            if vertex != vertex2:

                # path 시작정점 등록
                path = [vertex]

                # path가 도착지가 저장될때까지 반복
                while path[-1] != vertex2:
                    path.append(next_vertices[path[-1]][vertex_table[vertex2]])

                # 결과 경로 점점 리스트에 최단 경로와 전체 경로 저장
                path_out.append((distances[vertex][vertex_table[vertex2]], path))
                
    return path_out


if __name__ == '__main__':
    mygraph = {
        'A': {'C': -2},
        'B': {'A': 3, 'C': 2},
        'C': {'D': 2},
        'D': {'B': -1},
    }

    print(floyd_warshall(mygraph))
