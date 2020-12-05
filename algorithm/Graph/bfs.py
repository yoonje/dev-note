from collections import deque


def bfs(graph, start_node):
    visited = deque()
    need_visit = deque()

    need_visit.append(start_node)

    while need_visit:
        node = need_visit.popleft()
        if node not in visited:
            visited.append(node)
            need_visit.extend(graph[node])

    return visited


if __name__ == "__main__":
    graph = dict()
    graph['A'] = ['B', 'C']
    graph['B'] = ['A', 'D']
    graph['C'] = ['A', 'G', 'H', 'I']
    graph['D'] = ['B', 'E', 'F']
    graph['E'] = ['D']
    graph['F'] = ['D']
    graph['G'] = ['C']
    graph['H'] = ['C']
    graph['I'] = ['C', 'J']
    graph['J'] = ['I']
    # 시작 노드를 A라고 하고 BFS를 진행했을 때 방문되는 순서 리턴
    print(bfs(graph, 'A'))
