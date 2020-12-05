# 성능 개선 이전의 prim 알고리즘

from collections import defaultdict
from heapq import *


# edges는 간선이 1번만 등록되어 있는 반쪽짜리 엣지 리스트
def prim(start_node, edges):

    # 최소 신장 트리를 만들 MST 리스트
    mst = list()

    # 비어 있는 리스트를 디폴트 값으로 가질 수 있는 간선 딕셔너리
    # 양방향 정보를 append 하기 위해서 사용
    total_edges = defaultdict(list)

    # 양방향 정보를 다 갖은 간선 딕셔너리를 만듦
    for weight, n1, n2 in edges:

        # defaultdict이므로 키를 미리 선언하지 않아도 키에 대한 리스트의 원소에 append가 가능
        total_edges[n1].append((weight, n1, n2))
        total_edges[n2].append((weight, n2, n1))

    # 사이클 체크를 위한 집합 선언
    connected_nodes = set(start_node)

    # 시작 노드의 인접 간선들을 후보 간선 리스트에 등록
    candidate_edge_list = total_edges[start_node]

    # 힙으로 만들어서 최소 간선을 쉽게 POP
    heapify(candidate_edge_list)

    # 후보 간선 리스트가 비어 있을 때까지 반복
    while candidate_edge_list:

        # 힙에서 간선과 노드 정보를 얻어옴
        weight, n1, n2 = heappop(candidate_edge_list)

        # 사이클 체크
        if n2 not in connected_nodes:

            # 연결 노드와 스패닝 트리에 추가
            connected_nodes.add(n2)
            mst.append((weight, n1, n2))

            # 다음 방문 노드에게서 새로운 간선을 얻어옴
            for edge in total_edges[n2]:

                # 성능 개선을 위해 추가(이미 연결 노드에 등록되어 있는 노드의 간선은 등록할 필요가 없음)
                if edge[2] not in connected_nodes:
                    heappush(candidate_edge_list, edge)

    return mst


if __name__ == "__main__":
    myedges = [
        (7, 'A', 'B'), (5, 'A', 'D'),
        (8, 'B', 'C'), (9, 'B', 'D'), (7, 'B', 'E'),
        (5, 'C', 'E'),
        (7, 'D', 'E'), (6, 'D', 'F'),
        (8, 'E', 'F'), (9, 'E', 'G'),
        (11, 'F', 'G')
    ]
    print(prim('A', myedges))
